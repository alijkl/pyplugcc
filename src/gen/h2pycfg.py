import argparse
from cm2fun import CmReader
import os
import re


def extern_parse(s):
    s = s.strip()
    if s.startswith('#'):
        return ['', '', '']
    assert s[-1] in (';', ')','}')
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
    return [ftype, fname, param]

if __name__ == "__main__":
    cm = CmReader()
    cli = argparse.ArgumentParser()
    cli.add_argument(
        "--header", help="gcc header file to parse", default=cm.header_h
    )
    args = cli.parse_args()
    if hasattr(args, 'header') and args.header:
        cm.header_h = args.header
    else:
        cm.header_h = os.path.join(plugin_dir(), 'include', 'tree.h')
        assert os.path.isfile(cm.header_h)

    m = cm.read_header()
    os.chdir(os.path.dirname(__file__))
    macro_set = set()
    for b in m:
        r = re.match(r'^#define\s+((\w+)\s*\(\s*(\w+)\s*\))', b[1])
        if not r: continue
        f_name = r[2].strip()
        p_name = r[3].strip()
        if p_name in ('DECL', 'EXP', 'EXPR', 'ID', 'NODE', 'TYPE'):
            macro_set.add ("# {}({})".format(f_name, p_name))

    # extern function
    function_set = set()
    for b in m:
        f = extern_parse(b[1])
        function_set.add ("# {} {} {}".format(f[0], f[1], f[2]))

    print ("""# single parameter NODE gcc accessor list
# MACRO(NODE) ⏎ c type, py type
# (https://docs.python.org/3/c-api/arg.html#building-values)
#""")

    for i in sorted(macro_set):
        print (i)

    for i in sorted(function_set):
        print (i)
