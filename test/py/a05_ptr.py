import gcc
# from gcc.event import PLUGIN_FINISH_TYPE
from gcc.event import PLUGIN_FINISH_DECL
from node import TREE_CODE, TREE_TYPE, IS_NULL_TREE
from node import get_tree_code_name
from node import IDENTIFIER_POINTER, DECL_ASSEMBLER_NAME, DECL_INITIAL
from node import DECL_SOURCE_FILE, DECL_SOURCE_LINE, DECL_SOURCE_COLUMN
from node import tree_to_shwi, tree_fits_shwi_p, tree_real_cst_to_float
from node import TYPE_STRING_FLAG, TREE_STRING_POINTER
from node import TREE_OPERAND, TREE_OPERAND_LENGTH, TREE_CHAIN, TREE_VALUE
from gcc.tree_code_base import BOOLEAN_TYPE, INTEGER_TYPE, REAL_TYPE, VAR_DECL
from print_tree import node_as_string
from gcc.tree_code_base import POINTER_TYPE
from c_common import strip_pointer_operator, strip_pointer_or_array_types
from node import decl_value_expr_lookup
from node import TYPE_DOMAIN, TYPE_VALUES, TYPE_POINTER_TO, TYPE_REFERENCE_TO
from node import TYPE_MAX_VALUE, TYPE_MIN_VALUE
from node import TREE_PURPOSE, TREE_STRING_LENGTH

def ptr_type_dump(t):
    print(
        "\n# {} {}:{}".format
        (
            DECL_SOURCE_FILE(t),
            DECL_SOURCE_LINE(t),
            DECL_SOURCE_COLUMN(t)
        )
    )
    tt = TREE_TYPE(t)
    id = IDENTIFIER_POINTER(DECL_ASSEMBLER_NAME(t))
    tc = TREE_CODE(tt)
    print(
        "{}: tree_code {} {}".format
        (
            id, tc, get_tree_code_name(tc)
        )
    )
    if tc == POINTER_TYPE:
        tc = TREE_CODE(TREE_TYPE(tt))
        print(
            "{} -> tree_code {} {}".format
            (
                id, tc, get_tree_code_name(tc)
            )
        )
        if tc == INTEGER_TYPE:
            print("string flag {}".format(bool(TYPE_STRING_FLAG(TREE_TYPE(tt)))))
            if TYPE_STRING_FLAG(TREE_TYPE(tt)):
                print(
                    "{} {} tree_operand_length {}".format(
                        TREE_CODE(DECL_INITIAL(t)),
                        get_tree_code_name(TREE_CODE(DECL_INITIAL(t))),
                        TREE_OPERAND_LENGTH(DECL_INITIAL(t)))
                )
                argt = TREE_TYPE(TREE_TYPE(TREE_OPERAND(DECL_INITIAL(t))))
                # print(node_as_string(DECL_INITIAL(t)))
                # print("---")
                # print(node_as_string(argt))
                # print("---")
                # print()
                # print(node_as_string(TREE_TYPE(argt)))

                tc = TREE_CODE(argt)
                print(
                    "{} -> tree_code {} {}".format
                    (
                        id, tc, get_tree_code_name(tc)
                    )
                )
                if tc == 16:
                    print("{}".format(node_as_string(argt)))
                    print()
                    print("array bound: min {} max {}".format(
                        tree_to_shwi(TYPE_MIN_VALUE(TYPE_DOMAIN(argt))),
                        tree_to_shwi(TYPE_MAX_VALUE(TYPE_DOMAIN(argt)))))
                st = TREE_OPERAND(TREE_OPERAND(DECL_INITIAL(t)))
                stc = TREE_CODE(st)
                print("{} {} {}".format(id, stc, get_tree_code_name(stc)))
                if stc == 32:
                    print("TREE_STRING_LENGTH: {}".format(
                        TREE_STRING_LENGTH(st)
                    ))
                    print("TREE_STRING_POINTER: {}".format(
                        TREE_STRING_POINTER(st)
                    ))


def plugin_finish_type(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    if IS_NULL_TREE(TREE_TYPE(t)):
        return
    if TREE_CODE(t) == VAR_DECL:
        ptr_type_dump(t)


def plugin_finish_decl(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    if IS_NULL_TREE(TREE_TYPE(t)):
        return
    if TREE_CODE(t) == VAR_DECL:
        ptr_type_dump(t)


# gcc.register_callback(
#     gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
# )
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
