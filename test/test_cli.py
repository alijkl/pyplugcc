from pyplugcc_cli import PyPlugGccCli
import os
import json
import logging
import subprocess
import time

logger = logging.getLogger(os.path.basename(__file__))


class Expected_Error(Exception):
    pass


class TestCli_Error(Exception):
    pass


class TestCli (PyPlugGccCli):
    def __init__(self):
        super().__init__()
        self.parser.add_argument(
            '-t', '--test_config', help='test config file', default=''
        )
        self.parser.add_argument(
            '-v', '--verbose', help='verbose', default=None,
            action='store_true'
        )
        self.parser.add_argument(
            '-i', '--test_indexes', help='run only test numbers',
            nargs='*', type=int
        )
        self.parser.add_argument(
            '-e', '--exit_on_error', help='exit at first error',
            default=None, action='store_true'
        )

    @property
    def config_path(self):
        if 'test_config' in cli.args:
            return cli.args.test_config


class TestRunOne:
    def __init__(self, cmd=None):
        self.cmd = cmd
        self.script = ''
        self.units = []
        self.stdout = ''
        self.stderr = ''
        # self.env = os.environ


class TestRun:
    def __init__(self):
        self.config = None
        self.blocks = None
        self.cmd = None

    def load(self, config):
        if isinstance(config, TestCli):
            self.config = config
        with open(self.config.config_path, 'r') as f:
            self.blocks = json.load(f)

    def check_output(self, proc_output, expected=[]):
        result = [True]
        for e in expected:
            idx = proc_output.find(e)
            logger.debug("lookup: {} -> {}".format(e, idx))
            result.append(idx >= 0)
        return all(result)

    def run(self, verbose=False, test_indexes=[], exit_on_error=False):
        tidx = 0
        ttot = len(self.blocks['blocks'])
        os.chdir(os.path.dirname(self.config.config_path))

        for blk in self.blocks['blocks']:
            tidx += 1
            if test_indexes and tidx not in test_indexes:
                continue
            script = blk['script']
            units = blk['units']
            options = blk['options']
            rstdoutc = blk['result_stdout_contains']
            rstderrc = blk['result_stderr_contains']
            self.config.c.plugin_script = script
            run_cmd = "{} {} {}".format(
                self.config.cmd, options, " ".join(units)
            ).split()
            logger.info(" ".join(run_cmd[:]))
            c = subprocess.Popen(
                args=run_cmd, stdin=subprocess.PIPE,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE
            )
            try:
                outs, errs = c.communicate(timeout=None)
                for i in range(1, 360):
                    if c.returncode is not None:
                        break
                    time.sleep(1)
                result = c.returncode == 0
                if not result:
                    raise TestCli_Error(errs.decode())
                tmp_o = self.check_output(outs.decode(), rstdoutc)
                tmp_e = self.check_output(errs.decode(), rstderrc)
                result = tmp_o and tmp_e
                if not result or verbose:
                    logger.info(outs.decode())
                    if not result:
                        raise TestCli_Error
            except subprocess.CalledProcessError as e:
                raise
            except Expected_Error as e:
                pass
            except TestCli_Error as e:
                if exit_on_error:
                    if e.args:
                        logger.error("\n".join(e.args))
                    return
                else:
                    pass
            except Exception as e:
                raise
            finally:
                test_name = "{} ({})".format(
                    script, os.path.basename(" ".join(units))
                )
                result_str = 'OK' if result else 'ERROR'
                pad = (89 - len(test_name) - len(result_str)) * '-'
                print("| {:>3}/{:<3} {} {} {} |".format(
                    tidx, ttot, test_name, pad, result_str))


if __name__ == "__main__":
    cli = TestCli()
    cli.parse_argument()
    verbose = cli.args.verbose
    test_indexes = cli.args.test_indexes if cli.args.test_indexes else []
    test_indexes.sort()
    exit_on_error = cli.args.exit_on_error
    logging_level = logging.DEBUG if verbose else logging.ERROR
    logging.basicConfig(
        format='%(asctime)s %(message)s', level=logging_level
    )
    logger.debug(cli.cmd)
    logger.debug(cli.config_path)
    t = TestRun()
    t.load(cli)
    t.run(
        verbose=verbose,
        test_indexes=test_indexes,
        exit_on_error=exit_on_error
    )
