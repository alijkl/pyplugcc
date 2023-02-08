import gcc
from gcc.event import *
from print_tree import debug_tree, node_as_string, node_brief_as_string


def plugin_finish_type(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    print(node_as_string(t, 'finish_type:'))
    print()


def plugin_finish_decl(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    print(node_as_string(t, 'finish_decl:'))
    print()


def plugin_finish_parse_function(t):
    if gcc.errorcount() or gcc.sorrycount():
        return
    print(node_as_string(t, 'finish_parse_function:'))
    print()

gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_PARSE_FUNCTION,
    plugin_finish_parse_function, None
)

# Dummy call for now
gcc.register_callback(
    gcc.plugin_name, PLUGIN_REGISTER_GGC_ROOTS, None, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_INFO, None, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_PASS_MANAGER_SETUP, None, None
)
