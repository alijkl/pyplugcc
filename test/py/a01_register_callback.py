import gcc
from gcc.event import *

def gen_call(t):
    if t: print (t)

def plugin_finish_type(t):
    gen_call("CB plugin_finish_type")

def plugin_finish_decl(t):
    gen_call("CB plugin_finish_decl")

def plugin_pass_execution(t):
    gen_call("CB plugin_pass_execution")

gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
gcc.register_callback(
    gcc.plugin_name, PLUGIN_PASS_EXECUTION, plugin_pass_execution, None
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
