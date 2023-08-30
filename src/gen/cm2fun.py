import os
import argparse
import subprocess

"""
Simple tree.h parser to get accessor macros

Parse a header file
(plugin_dir/include/tree.h or any file passed as '--header') and
return an array
[(location in the header, macro or extern, ftell location in file, doc)]
macro, extern definition and doc are unsplited as a single line first.

note: doesn't work if the macro has some comment embeded.
"""


"""
source comment as a single line
"""


def single_line_header_doc(m, h):
    lines = []
    with open(h, 'r') as f:
        if len(m) <= 1:
            pass
        elif len(m) > 1:
            prev = m[-2][2]
            curr = m[-1][2]
            f.seek(curr)
            f.seek(prev)
            while True:
                if f.tell() >= curr:
                    break
                lines.append(f.readline().strip())
            beg_idx = 0
            end_idx = 0
            i = 0
            for ln in lines[-2::-1]:
                i += 1
                if ln.endswith('*/'):
                    end_idx = i - 1
                if ln.startswith('/*'):
                    beg_idx = i
                    break
            doc_line = " ".join(lines[-2::-1][end_idx:beg_idx][::-1])
            doc_line = doc_line.replace('\t', ' ')
            m[-1][3] = doc_line.replace('  ', ' ')


"""
defined macro as a single line
(location in the header, macro, location in file, doc)
"""


def single_line_header_macro(h):
    mbuf = []
    idx = 0
    continue_reading = False
    defined = False
    line_count = 0
    lookup = None
    with open(h, 'r') as f:
        while True:
            line = f.readline()
            line_count = line_count + 1
            if line == '':
                break
            line = line.strip()
            line = line.replace('\t', ' ')
            for i in reversed(range(1, 6)):
                line = line.replace(' ' * i, ' ')
            if lookup == 'define':
                continue_reading = line.endswith('\\')
            elif lookup == 'static_inline':
                continue_reading = '{' not in line
            else:
                continue_reading = not line.endswith(';')

            if defined and continue_reading:
                if lookup == 'define':
                    mbuf[idx][1] = mbuf[idx][1] + (line[:-1]).strip()
                elif lookup == 'static_inline':
                    mbuf[idx][1] = mbuf[idx][1] + line.strip()
                else:
                    mbuf[idx][1] = mbuf[idx][1] + line.strip() + ' '
            elif defined:
                if lookup not in 'static_inline':
                    mbuf[idx][1] = mbuf[idx][1] + line
                else:
                    mbuf[idx][1] = mbuf[idx][1]
                idx = idx + 1
                defined = False
                continue
            elif line.startswith(('#define ', 'extern ', 'static inline ')):
                pos = f.tell()
                if line.startswith('#define '):
                    continue_reading = line.endswith('\\')
                    lookup = 'define'
                elif line.startswith('extern '):
                    continue_reading = not line.endswith(';')
                    lookup = 'extern'
                elif line.startswith('static inline '):
                    continue_reading = '{' not in line
                    lookup = 'static_inline'
                if continue_reading:
                    defined = True
                    if lookup == 'define':
                        mbuf.append(
                            list(
                                (str(line_count),
                                 line[:-1].strip() + ' ',
                                 pos, ''
                                 )
                            )
                        )
                        single_line_header_doc(mbuf, h)
                    elif lookup == 'extern':
                        mbuf.append(
                            list(
                                (str(line_count), line.strip() + ' ', pos, '')
                            )
                        )
                    elif lookup == 'static_inline':
                        mbuf.append(
                            list(
                                (str(line_count), line.strip() + ' ', pos, '')
                            )
                        )
                        single_line_header_doc(mbuf, h)
                else:
                    mbuf.append(
                        list(
                            (str(line_count), line, pos, '')
                        )
                    )
                    single_line_header_doc(mbuf, h)
                    idx = len(mbuf)
                    defined = False
    return mbuf


def plugin_dir():
    result = subprocess.run(
        ['gcc', '-print-file-name=plugin'], capture_output=True, check=True
    )
    return result.stdout.decode().strip()


class CmReader:
    def __init__(self):
        self.plugin_dir = plugin_dir()    
        self.header_h = None

    def read_header(self):
        return single_line_header_macro(self.header_h)


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

    mbuf = cm.read_header()
    for m in mbuf:
        print("{}".format(m))
