
"""
read the output of cm2fun and try to generate c api code for extern functions
"""
import textwrap
import logging
import os
import argparse

logger = logging.getLogger(os.path.basename(__file__))
logging.basicConfig(
    format='%(asctime)s %(message)s', level=logging.ERROR
)


def extern_parse(s):
    s = s.strip()
    assert s[-1] in (';', ')', '}')
    if s.startswith("extern inline __attribute__"):
        return ['', '', '']
    att = s.find('ATTRIBUTE')
    if att > 0:
        tmp = s[0:att][::-1][1:]
    elif s.startswith('static inline '):
        tmp = s[::-1]
    else:
        tmp = s[::-1][1:]
    p1 = 0
    p1c = 0
    p2 = 0
    fname = ''
    for i in range(0, len(tmp)):
        if tmp[i] == ')':
            p1 = i if not p1 else p1
            p1c += 1
        elif tmp[i] == '(':
            p2 = i if p1c == 1 else p2
            p1c -= 1
        if p1c == 0:
            break
    end_cnt = 1 if tmp[0] == ')' else 0
    fname_tmp = tmp[p2 + end_cnt:][::-1].split()[-1]
    fname = fname_tmp[::-1][0:fname_tmp[::-1].find('*')][::-1] if \
        '*' in fname_tmp else fname_tmp
    # move enventual pointer keyword '*' into ftype
    fname_idx = s.find(fname)
    ftype_tmp = s[0:fname_idx].split()
    ftype = ftype_tmp[1:] if ftype_tmp[0] == 'extern' else ftype_tmp[2:]
    param = tmp[p1 + 1:p2][::-1].split(',') if end_cnt else []
    param = [n.strip() for n in param]
    # logger.debug("ftype: {}, fname: {}, param: {}".format(ftype, fname, param))
    # logger.info("{} {} {}".format(ftype, fname, param))
    return [ftype, fname, param]


def pval(t, catch_optional=True):
    result = []
    for i in t:
        tmp = i.split()
        if not tmp:
            return []
        tmp = [n.strip() for n in tmp]
        if '=' in ' '.join(tmp) and catch_optional:
            result += ['|']
        if tmp[0] == 'enum':
            result += ['i']
            continue
        if ' '.join(tmp) == 'int' or ' '.join(tmp) == 'int *':
            result += ['i']
            continue
        if ' '.join(tmp) == 'const char' or ' '.join(tmp) == 'const char *':
            result += ['s']
            continue
        if tmp[0] == 'bool' or 'bool' in tmp[0].split('='):
            result += ['i']
            continue
        result += ['O']
    return result


class BlockStr:
    def __init__(self, cs='/*', ce='*/'):
        self.cs = cs
        self.ce = ce
        self.head = ''
        self.note = ''
        self.body = ''
        self.disabled = False

    def str_head(self):
        if self.head:
            return self.cs + '\n' + self.head + '\n' + self.ce + '\n'
        else:
            return self.head + '\n'

    def str_note(self):
        if self.note:
            return self.cs + '\n' + self.note + '\n' + self.ce + '\n'
        else:
            return self.note + '\n'

    def str_body(self):
        if self.disabled:
            return self.cs + '\n' + self.body + '\n' + self.ce + '\n'
        else:
            return self.body + '\n'

    def str(self):
        return self.str_head() + self.str_note() + self.str_body() + '\n'


class FunParam:
    def __init__(self, s):
        if s:
            tmp, self.default = s.split('=') if '=' in s else [s, '']
            if len(tmp.replace('*', '').split()) == 1:
                self.type = tmp.split()[0]
                self.name = 'anonymous'
                self.is_ptr = tmp.count('*')
            else:
                self.type, self.name = tmp.rsplit(maxsplit=1) if \
                    ' ' in tmp else [tmp, 'anonymous']
                if self.type == 'enum':
                    self.type += ' ' + self.name
                    self.name = ''
                if self.name in ('CXX_MEM_STAT_INFO', 'HOST_WIDE_INT'):
                    self.type = self.type + ' ' + self.name
                    self.name = ''
                self.is_ptr = tmp.count('*')
                self.type = self.type.replace('*', '')
                self.name = self.name.replace('*', '')
                self.name = self.name if self.name else 'anonymous'
        else:
            self.name = 'anonymous'
            self.type = ''
            self.default = ''
            self.is_ptr = False


class FunReturnType:
    def __init__(self, s=None):
        if s:
            self.type = s[0] if isinstance(s, list) else s
            self.is_ptr = ''.join(s).count('*') if isinstance(s, list) \
                else s.count('*')
        else:
            self.type = ''
            self.is_ptr = False


    # def from_str(self, s):
    #     # self.type = [
    #     #     n.replace('*', '') for n in s
    #     #     if n.replace('*', '') not in ''
    #     # ]
    #     return self


def generate(m=[], file_cc=None, file_h=None, file_met=None, file_cfg=None,
             include_cc_header=False, only=None):
    processed = set()
    bs = BlockStr()
    only = only.strip() if only else None
    for e in m:
        # print(e[1])
        # logger.debug(e[1])
        if not e[1].startswith(('extern ', 'static inline ')):
            continue
        if only and not e[1].startswith(only + ' '):
            continue
        t, n, p = extern_parse(e[1])
        if file_cfg and not file_cfg.closed:
            file_cfg.seek(0)
            for ln in file_cfg:
                ln = ln.strip()
                if not ln or ln[0] == '#':
                    continue
                elif ln == "{} {} {}".format(t, n, p):
                    break
            else:
                continue
        logger.debug("{} | {} | {}".format(t, n, p))
        rt = FunReturnType(t)
        logger.debug(
            "function: {} {}".format(
                rt.type, n
            )
        )
        if "{}".format(n) in processed:
            continue
        if '...' in p:
            continue
        if any([i.find('<') > -1 for i in p]):
            continue
        if any([i.find('>') > -1 for i in t]):
            continue
        if any([i.find('&') > -1 for i in p]):
            continue

        bs.head = e[1]
        bs.body = ''

        f_name = n.replace('[', '_').replace(']', '')
        bs.body += "PyObject *Py_{0}".format(f_name)
        bs.body += "(PyObject *self, PyObject *args) {\n"
        i = 0
        va = []

        vdecl = True
        for pn in p:
            fp = FunParam(pn)
            logger.debug("fname: {} pn: {}".format(f_name, pn))

            param_n = fp.name
            default_v = "= {}".format(fp.default) if fp.default else ''
            vdecl = ''
            # tree
            if any([x in ('tree', 'const_tree', 'tree_node')
                    for x in fp.type.split()]):
                if default_v:
                    default_v = "= PyGccTree_New({})".format(fp.default.strip())
                vdecl = "PyObject *{}_{} {}".format(param_n, i, default_v)
            # void
            elif fp.type in 'void':
                continue
            # enum
            elif fp.type in 'enum':
                vdecl = "{} {}{}_{} {}".format(
                    fp.type, '*' * fp.is_ptr, fp.name, i, default_v
                )
                
            else:
                vdecl = "{} {}{}_{} {}".format(
                    fp.type, '*' * fp.is_ptr, param_n, i, default_v
                )
            vdecl = vdecl.replace('  ', ' ')
            if vdecl:
                bs.body += "  {};\n".format(vdecl.strip())

            va += ["{}_{}".format(param_n, i)]
            i += 1

        if (va and vdecl) and p and ' '.join(p) != 'void':
            pformat = pval(p)
            pformat_str = "".join(pformat) + ":" + n
            tmp1 = "if (!PyArg_ParseTuple (args,"
            tmp1 += '"{}", {})) return NULL;'.format(
                pformat_str, ', '.join(['&{}'.format(n) for n in va])
            )
            bs.body += textwrap.fill(
                text=tmp1, width=79,
                initial_indent='  ', subsequent_indent=' ' * 4
            )
            bs.body += '\n'

        fargs = []
        j = 0
        for i in va:
            if any([x in ('tree', 'const_tree', 'tree_node')
                    for x in p[j].split()]):
                if '*' in ' '.join(p[j]):
                    fargs += [
                        '({}*)Get_gccdata({})'.format(
                            [n for n in p[j].split() if n not in
                             ('const', '*')][0], i)
                    ]
                else:
                    fargs += [
                        '({})Get_gccdata({})'.format(
                            [n for n in p[j].split() if n not in
                             ('const', '*')][0], i)
                    ]
            else:
                fargs += [i]
            j += 1
        fargs = ', '.join(fargs)
        fargs = textwrap.fill(
            text=fargs, width=50,
            initial_indent='', subsequent_indent=' ' * 9
        )

        # result
        if 'void' in rt.type:
            if fargs and vdecl:
                bs.body += "  {}({});".format(n, fargs)
            # elif not vdecl:
            #     bs.body += "  {}();".format(n)
            else:
                bs.body += "  {}();".format(n)
               
        else:
            if fargs and vdecl:
                bs.body += "  {} {} = {}({});".format(
                    ' '.join(t), 't', n, fargs
                )
            elif fargs or not vdecl:
                bs.body += "  {} {} = {}();".format(
                    ' '.join(t), 't', n
                )
            else:
                bs.body += "  {} {} = {};".format(
                    ' '.join(t), 't', n
                )

        # return value
        bs.body += "\n"
        if 'bool' in t:
            bs.body += '  if (t) {\n'
            bs.body += '    Py_RETURN_TRUE;\n'
            bs.body += '  }else{\n'
            bs.body += '    Py_RETURN_FALSE;\n'
            bs.body += '  }'
        elif 'tree' in t or 'const_tree' in t:
            bs.body += '  PyObject *result = PyGccTree_New();\n'
            bs.body += '  Set_gccdata(result, (void*) t);\n'
            bs.body += '  return result;'
        elif 'int' in t or ' '.join(t).startswith('enum '):
            bs.body += '  PyObject *result = Py_BuildValue("i", t);\n'
            bs.body += '  return result;'
        elif 'size_t' in t:
            bs.body += '  PyObject *result = Py_BuildValue("n", t);\n'
            bs.body += '  return result;'
        elif 'const char' in ' '.join(t):
            bs.body += '  PyObject *result = Py_BuildValue("s", t);\n'
            bs.body += '  return result;'
        elif 'unsigned HOST_WIDE_INT' in ' '.join(t):
            bs.body += '  PyObject *result = Py_BuildValue("K", t);\n'
            bs.body += '  return result;'
        elif 'HOST_WIDE_INT' in t:
            bs.body += '  PyObject *result = Py_BuildValue("L", t);\n'
            bs.body += '  return result;'
        elif 'unsigned int' in ' '.join(t):
            bs.body += '  PyObject *result = Py_BuildValue("I", t);\n'
            bs.body += '  return result;'
        elif 'void' in t:
            bs.body += '  Py_RETURN_NONE;'
        else:
            bs.disabled = True

        bs.body += "\n}"

        include_headers = """
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <gcc-plugin.h>
#include "tree.h"
#include "pyplugcc-mgcc-tree.h"
"""
        # meth_def
        meth_def_str = """{0}  {{
{0}  .ml_name  = "{1}",
{0}  .ml_meth  = (PyCFunction){2},
{0}  .ml_flags = {3},
{0}  .ml_doc   = "{4}"
{0}  }},
""".format(' ' * 1,
           f_name,
           'Py_' + f_name,
           'METH_VARARGS' if fargs else 'METH_NOARGS',
           e[3].replace('/*', '').replace('*/', '').replace('"', '').strip())

        h_str = bs.body[:bs.body.find('{')] + ';'

        # file out
        if file_cc and not file_cc.closed:
            if include_cc_header:
                file_cc.write(include_headers + '\n')
            file_cc.write(bs.str())
        if bs.disabled:
            pass
        else:
            if file_h and not file_h.closed:
                file_h.write(h_str + '\n')
            if file_met and not file_met.closed:
                file_met.write(meth_def_str)

        processed.add("{}".format(n))
        bs.disabled = False


if __name__ == "__main__":
    # parser = argparse.ArgumentParser()
    # parser.add_argument(
    # )
    # args = parser.parse_args()
    from cm2fun import CmReader, plugin_dir
    cm = CmReader()
    cli = argparse.ArgumentParser()
    cli.add_argument(
        "--header", help="gcc header file to parse", default=cm.header_h
    )
    cli.add_argument(
        '--only', help="generate only 'extern', 'static inline'", default=''
    )
    args = cli.parse_args()
    if hasattr(args, 'header') and args.header:
        cm.header_h = args.header
    else:
        cm.header_h = os.path.join(plugin_dir(), 'include', 'tree.h')
        assert os.path.isfile(cm.header_h)

    if args.only:
        logging.basicConfig(
            format='# %(message)s', level=logging.INFO
        )
    else:
        logging.basicConfig(
            format='%(asctime)s %(message)s', level=logging.DEBUG
    )

    mbuf = cm.read_header()
    generate(mbuf, only=args.only)
