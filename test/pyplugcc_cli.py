#!/usr/bin/python3

import os
import argparse
import json

class Config:
    def __init__(self, gcc='', plugin_path='', plugin_script='', gcc_options=''):
        self.gcc = gcc
        self.plugin_path = plugin_path
        self.plugin_script = plugin_script
        self.gcc_options = gcc_options
        self.plugin_name = os.path.basename (plugin_path)
        if self.plugin_name[-3:] == '.so':
            self.plugin_name = self.plugin_name[:-3]
        elif self.plugin_name[-4:] == '.dll':
            self.plugin_name = self.plugin_name[:-4]

    def dump(self):
        return json.dumps(self.__dict__, indent=4)

    def load(self, config_file):
        if os.path.isfile (config_file):
            with open(config_file, 'r') as f:
                self.__dict__ = json.load (f)

    def drv_cmd (self, positional_parameters):
        positional_parameters = " ".join(positional_parameters)
        return "{} -fplugin={} -fplugin-arg-{}-script={} {} {}".format(
            self.gcc, self.plugin_path, self.plugin_name, self.plugin_script,
            self.gcc_options, positional_parameters)

class PyPlugGccCli:
    def __init__(self):
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument(
            '-c', '--config', help='GCC drv config file',
            default='pyplugcc.conf',
        )
        self.parser.add_argument(
            '--config_dump', help='dump cli option into config',
            default=None, action='store_true'
        )
        self.parser.add_argument(
            '-g', '--gcc', help='GCC', default='gcc'
        )
        self.parser.add_argument(
            '-pp', '--plugin_path', help='plugin lib path'
        )
        self.parser.add_argument(
            '-ps', '--plugin_script', help='plugin python script'
        )
        self.parser.add_argument(
            '-go', '--gcc_options',
            help='gcc options in the form -go="-opt1 -opt2"', default=''
        )
        self.parser.add_argument(
            'positional_parameters', nargs='*'
        )
    def parse_argument(self):
        self.args = self.parser.parse_args()
        if self.args.config and self.args.config_dump:
            self.c = Config(
                self.args.gcc, self.args.plugin_path,
                self.args.plugin_script, self.args.gcc_options)
            with open (self.args.config, 'w') as f:
                print (self.c.dump(), file=f)
        elif self.args.config:
            self.c = Config()
            self.c.load (self.args.config)
            if self.args.plugin_script:
                self.c.plugin_script = self.args.plugin_script
            if self.args.gcc_options:
                self.c.gcc_options = self.args.gcc_options
    @property
    def cmd(self):
        if hasattr(self, 'c'):
            return self.c.drv_cmd(self.args.positional_parameters)
        else:
            self.parser.print_help()

if __name__ == "__main__":
    d = PyPlugGccCli()
    d.parse_argument()
