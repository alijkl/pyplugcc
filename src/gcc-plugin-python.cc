#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdexcept>

#include "gcc-plugin-python.h"
#include <plugin-version.h>


void
plugin_finish (void *gcc_data, void *user_data)
{
  Py_Finalize();
}

int
plugin_init (struct plugin_name_args *plugin_info,
             struct plugin_gcc_version *version)
{
  if (!plugin_default_version_check (version, &gcc_version))
    throw std::runtime_error("version error");

  /*
    https://gcc.gnu.org/onlinedocs/gccint/Plugin-API.html#Plugin-API

    The prototype for a plugin callback function.
    gcc_data  - event-specific data provided by GCC
    user_data - plugin-specific data provided by the plug-in.  
    typedef void (*plugin_callback_func)(void *gcc_data, void *user_data);
     
    To register a callback, 
    the plugin calls register_callback with the arguments:

    char *name: Plugin name.
    int event: The event code.
    plugin_callback_func callback: The function that handles event.
    void *user_data: Pointer to plugin-specific data.
  */
  
  /* Information about the plugin. */
  const char *plugin_name = plugin_info->base_name;
  struct plugin_info py_plug_info = {"0.1", "python plugin script"};
  register_callback (plugin_name, PLUGIN_INFO, NULL, &py_plug_info);

  register_callback (plugin_name, PLUGIN_FINISH, plugin_finish, NULL);
  
  
  Py_UnbufferedStdioFlag = 1;
  Py_Initialize();
  
  return 0;
}
