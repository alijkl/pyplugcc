#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyMODINIT_FUNC
PyInit_gcc(void);

bool
init_gcc_module (const char * plugin_name);

