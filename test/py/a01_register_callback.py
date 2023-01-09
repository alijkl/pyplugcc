import gcc

def gen_call(*args,**kwargs):
    if args: print (args)

def plugin_finish_type():
    gen_call("CB plugin_finish_type")

def plugin_finish_decl():
    gen_call("CB plugin_finish_decl")

def plugin_pass_execution():
    gen_call("CB plugin_pass_execution")

gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_FINISH_TYPE, plugin_finish_type, None
)
gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_FINISH_DECL, plugin_finish_decl, None
)
gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_PASS_EXECUTION, plugin_pass_execution, None
)

# Dummy call for now
gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_REGISTER_GGC_ROOTS, None, None
)
gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_INFO, None, None
)
gcc.register_callback(
    gcc.plugin_name, gcc.PLUGIN_PASS_MANAGER_SETUP, None, None
)
