# import sys
import gcc
from gcc.event import PLUGIN_FINISH_TYPE, PLUGIN_FINISH_DECL
from gcc.tree_code_base import TYPE_DECL, ENUMERAL_TYPE
# from gcc.tree_code_lang_c import *
# from gcc import GccTree
from node import TREE_CODE, TREE_TYPE, IS_NULL_TREE, TYPE_NAME
from node import IDENTIFIER_POINTER, DECL_CHAIN
from node import DECL_SOURCE_FILE, DECL_SOURCE_LINE, DECL_SOURCE_COLUMN
from node import TYPE_VALUES, TREE_VALUE, TREE_PURPOSE, TREE_CHAIN
from node import DECL_INITIAL, tree_fits_shwi_p, tree_to_shwi
from print_tree import debug_tree, node_as_string, node_brief_as_string


def enumeral_type_dump(t, n):
    # print(node_as_string(t, 'full:'))

    enum_name = IDENTIFIER_POINTER(n)
    field = DECL_CHAIN(t)
    print(
        "\n# {} {}:{}".format
        (
            DECL_SOURCE_FILE(field),
            DECL_SOURCE_LINE(field),
            DECL_SOURCE_COLUMN(field)
        )
    )
    print("{}".format(enum_name))
    v = TYPE_VALUES(t)

    while (not IS_NULL_TREE(v)):
        tval = TREE_VALUE(v)
        if tree_fits_shwi_p (DECL_INITIAL(tval)):
            print(
                "{} = {}".format(
                    IDENTIFIER_POINTER(TREE_PURPOSE(v)), tree_to_shwi(DECL_INITIAL(tval))
                )
            )
        v = TREE_CHAIN(v)
    print()


def plugin_finish_type(t):
    if gcc.errorcount() or gcc.sorrycount(): return
    if IS_NULL_TREE(t): return
    if TREE_CODE(t) != ENUMERAL_TYPE: return
    if IS_NULL_TREE(TYPE_NAME(t)): return
    enumeral_type_dump(t, TYPE_NAME(t))


def plugin_finish_decl(t):
    if gcc.errorcount() or gcc.sorrycount(): return
    if TREE_CODE(t) != TYPE_DECL: return
    if TREE_CODE(TREE_TYPE(t)) != ENUMERAL_TYPE: return
    enumeral_type_dump(t, DECL_NAME(t))


gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
