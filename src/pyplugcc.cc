#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdexcept>
#include "pyplugcc.h"
#include "logging.h"
#include <plugin-version.h>
#include "pyplugcc-mgcc.h"

#if PY_VERSION_HEX < 0x03090000
#error this GCC plugin is for Python >=3.9
#endif


void
plugin_finish (void *gcc_data, void *user_data)
{
  Py_Finalize();
}

bool
py_run_file (const std::string path) {
  FILE* fp = fopen(path.c_str(), "r");
  int re;
  char buffer[200];
  if (fp) {
    re = PyRun_SimpleFile(fp, path.c_str());
    fclose(fp);
    if (re != EXIT_SUCCESS) {
      sprintf (buffer, "py_run_file: %s failed to run '%s'\n",
	       err_str.c_str(), path.c_str());
      LOG(buffer);
    }
  } else {
    sprintf (buffer, "py_run_file: %s failed to open '%s'\n",
	     err_str.c_str(), path.c_str());
    LOG(buffer);
  }
  return re == EXIT_SUCCESS;
}

int
plugin_init (struct plugin_name_args *plugin_info,
             struct plugin_gcc_version *version)
{
  if (!plugin_default_version_check (version, &gcc_version))
    throw std::runtime_error("version error");

  char  buffer[200];

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
  struct plugin_info py_plug_info = {
    .version = "0.1",
    .help = "python plugin script"
  };


  const int argc = plugin_info->argc;
  const struct plugin_argument * const argv = plugin_info->argv;

  int i;
  std::string script_path;
  for (i = 0; i < argc; ++i) {
    if (!(strcmp(argv[i].key, "script"))) {
      script_path = argv[i].value;
      continue;
    }
    fprintf
      (stderr, "%s: unknown option: '-fplugin-arg-%s-%s'\n",
       plugin_name, plugin_name, argv[i].key);
    return EXIT_FAILURE;
  }

  register_callback (plugin_name, PLUGIN_INFO, NULL, &py_plug_info);

  register_callback (plugin_name, PLUGIN_FINISH, plugin_finish, NULL);

  Py_UnbufferedStdioFlag = 1;

  /* Add a built-in module, before Py_Initialize */
  if (PyImport_AppendInittab("gcc", PyInit_gcc) == -1) {
    sprintf
      (
       buffer,
       "%s adding %s module to the existing table of built-in modules\n",
       err_str.c_str(), "gcc"
       );
    LOG(buffer);
    return EXIT_FAILURE;
  }

  Py_Initialize();

  if (! init_gcc_module (plugin_name)) {
    Py_Finalize();
    return EXIT_FAILURE;
  };

  if (! py_run_file (script_path)) {
    Py_Finalize();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
