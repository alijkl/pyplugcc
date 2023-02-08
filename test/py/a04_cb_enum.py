import sys
import gcc
from gcc.event import *
from gcc.tree_code_base import *
from gcc.tree_code_lang_c import *
from gcc import GccTree
from node import *
from print_tree import debug_tree, node_as_string, node_brief_as_string


def enumeral_type_dump (t, n):
    # debug_tree(t)
    # print(file=sys.stderr)
    print (node_brief_as_string(t, 'brief:'))
    print (node_as_string(t, 'full:'))
    
    enum_name = IDENTIFIER_POINTER(n)
    print ("{}".format(enum_name))
    v = TYPE_VALUES(t)
    while (not IS_NULL_TREE(v)):
        tval = TREE_VALUE(v)
        print(
            "{} = {}".format(
                IDENTIFIER_POINTER(TREE_PURPOSE(v)), tree_to_shwi(tval)
            )
        )
        v = TREE_CHAIN(v)
    print ()

def plugin_finish_type(t):
    if gcc.errorcount() or gcc.sorrycount(): return
    if TREE_CODE(t) != ENUMERAL_TYPE: return
    if IS_NULL_TREE (TYPE_NAME(t)): return
    enumeral_type_dump (t, TYPE_NAME(t))

def plugin_finish_decl(t):
    if gcc.errorcount() or gcc.sorrycount(): return
    if TREE_CODE(t) != TYPE_DECL: return
    if TREE_CODE (TREE_TYPE(t)) != ENUMERAL_TYPE: return
    enumeral_type_dump (t, DECL_NAME (t))

gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
