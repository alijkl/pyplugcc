#if GCCPLUGIN_VERSION >= 4007
#error this GCC plugin is for GCC >=4.7
#endif

#include <gcc-plugin.h>

#ifdef _WIN32
__declspec(dllexport)
#endif
int plugin_is_GPL_compatible;

#ifdef _WIN32
__declspec(dllexport)
#endif


int
plugin_init (struct plugin_name_args *plugin_info,
             struct plugin_gcc_version *version);

