import gcc
from gcc.event import *
from gcc.tree_code_base import *
from gcc.tree_code_lang_c import *
from gcc import GccTree

def at_execution_call(t):
    assert isinstance(t, GccTree)

gcc.register_callback(
    gcc.plugin_name, PLUGIN_PASS_EXECUTION, at_execution_call, None
)

g = GccTree()
assert isinstance(g, GccTree)

print ("{}".format(g))
print ("{}".format(type (g)))
print ("{}".format(dir(g)))
