
"""
read the output of cm2fun and try to generate c api code for exern functions
"""
import textwrap
import logging
import os

logger = logging.getLogger(os.path.basename(__file__))


def extern_parse(s):
    assert s[-1] == ';'
    if s.startswith("extern inline __attribute__"):
        return ['', '', '']
    att = s.find('ATTRIBUTE')
    if att > 0:
        tmp = s[0:att][::-1][1:]
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
    fname = tmp[p2 + end_cnt:][::-1].split()[-1]
    fname = fname.split('*')[-1]
    fname_idx = s.find(fname)
    ftype = s[0:fname_idx].split()[1:]
    param = tmp[p1 + 1:p2][::-1].split(',') if end_cnt else []
    param = [n.strip() for n in param]
    logger.debug("ftype: {}, fname: {}, param: {}".format(ftype, fname, param))
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


def generate(m=[], file_cc=None, file_h=None, file_met=None, file_cfg=None,
             include_cc_header=False):
    processed = set()
    bs = BlockStr()
    for e in m:
        print(e[1])
        logger.debug(e[1])
        if not e[1].startswith('extern '):
            continue
        t, n, p = extern_parse(e[1])
        if file_cfg and not file_cfg.closed:
            file_cfg.seek(0)
            for ln in file_cfg:
                ln = ln.strip()
                # print("{} @ {}".format(ln, "{} {} {}".format(t, n, p)))
                if not ln or ln[0] == '#':
                    continue
                elif ln == "{} {} {}".format(t, n, p):
                    break
            else:
                continue

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
        for pn in p:
            default_v = pn.split('=')
            if len(default_v) > 1:
                default_v = default_v[-1]
                pn = pn.split('=')[0]
            else:
                default_v = ''
            for k in pn.split()[::-1]:
                if k == '*' or k == 'const':
                    continue
                param_n = k
                break
            param_n = param_n.replace('*', '').lower()
            default_v = "= {}".format(default_v) if default_v else ''

            # tree
            if any([x in ('tree', 'const_tree', 'tree_node')
                    for x in p[i].split()]):
                if default_v:
                    default_v = "= PyGccTree_New({})".format(
                        default_v.split('=')[-1].strip()
                    )
                vdecl = "PyObject *{}_{} {}".format(param_n, i, default_v)
            # bool
            elif pn and pn.split()[0] == 'bool' and default_v:
                if '*' in p[i].split():
                    vdecl = "{} *{}_{} {}".format(
                        pn.split()[0], param_n, i, default_v
                    )
                else:
                    vdecl = "{} {}_{} {}".format(
                        pn.split()[0], param_n, i, default_v
                    )
            # struct
            elif pn and pn.split()[0] == 'struct' and len(pn.split()) == 3:
                vdecl = "{}_{} {}".format(
                    pn, i, default_v
                )
            # void
            elif pn and ''.join(pn) == 'void':
                vdecl = ''
            # int
            elif pn and pn.split()[0] == 'int':
                if '*' in pn.split():
                    vdecl = "int *{}_{} {}".format(param_n, i, default_v)
                else:
                    vdecl = "int {}_{} {}".format(param_n, i, default_v)
            # no param
            elif not pn:
                vdecl = ''
            else:
                vdecl = "{} {}_{} {}".format(
                    pn.replace('const ', ''), param_n, i, default_v
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
        if 'void' in t:
            if fargs and vdecl:
                bs.body += "  {}({});".format(n, fargs)
            elif fargs:
                bs.body += "  {}();".format(n)
            else:
                bs.body += "  {};".format(n)
        else:
            if fargs and vdecl:
                bs.body += "  {} {} = {}({});".format(
                    ' '.join(t), 't', n, fargs
                )
            elif fargs:
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
{0}    .ml_name  = "{1}",
{0}    .ml_meth  = (PyCFunction){2},
{0}    .ml_flags = {3},
{0}    .ml_doc   = "{4}"
{0}  }},
""".format(' ' * 4,
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

    logging.basicConfig(
        format='%(asctime)s %(message)s', level=logging.DEBUG
    )

    import cm2fun
    mbuf = cm2fun.read_header()
    generate(mbuf)
