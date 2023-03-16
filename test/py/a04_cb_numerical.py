import gcc
from gcc.event import PLUGIN_FINISH_TYPE, PLUGIN_FINISH_DECL
from node import TREE_CODE, TREE_TYPE, IS_NULL_TREE
from node import IDENTIFIER_POINTER, DECL_ASSEMBLER_NAME, DECL_INITIAL
from node import DECL_SOURCE_FILE, DECL_SOURCE_LINE, DECL_SOURCE_COLUMN
from node import tree_to_shwi, tree_fits_shwi_p, tree_real_cst_to_float
from gcc.tree_code_base import BOOLEAN_TYPE, INTEGER_TYPE, REAL_TYPE, VAR_DECL
from print_tree import node_as_string


def numerical_type_dump(t):
    print(
        "\n# {} {}:{}".format
        (
            DECL_SOURCE_FILE(t),
            DECL_SOURCE_LINE(t),
            DECL_SOURCE_COLUMN(t)
        )
    )
    id = IDENTIFIER_POINTER(DECL_ASSEMBLER_NAME(t))
    tc = TREE_CODE(TREE_TYPE(t))
    if tc == BOOLEAN_TYPE:
        print("{} {}".format(id, node_as_string(DECL_INITIAL(t))))
        print("{} {}".format(id, bool(tree_to_shwi(DECL_INITIAL(t)))))
    elif tc == INTEGER_TYPE:
        print("{} {}".format(id, node_as_string(DECL_INITIAL(t))))
        if tree_fits_shwi_p(DECL_INITIAL(t)):
            print("{} {}".format(id, tree_to_shwi(DECL_INITIAL(t))))
        else:
            print("don't fits shwi\n {}".format(node_as_string(t)))
    elif tc == REAL_TYPE:
        print("{} {}".format(id, node_as_string(DECL_INITIAL(t))))
        print("{} {}".format(id, tree_real_cst_to_float(DECL_INITIAL(t))))
    else:
        print("not implemented: tree_code {}".format(tc))


def plugin_finish_type(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    if IS_NULL_TREE(TREE_TYPE(t)):
        return
    if TREE_CODE(t) == VAR_DECL:
        numerical_type_dump(t)


def plugin_finish_decl(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    if IS_NULL_TREE(TREE_TYPE(t)):
        return
    if TREE_CODE(t) == VAR_DECL:
        numerical_type_dump(t)


gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
