#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <gcc-plugin.h>

#include "logging.h"
#include "pyplugcc-c-common-mdef.h"

char * c_common_doc = NULL;

static struct PyModuleDef node_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "gcc.c_common",   /* name of module */
  .m_doc = c_common_doc,      /* module documentation, may be NULL */
  .m_size = -1,               /* size of per-interpreter state of the module,
                                 or -1 if the module keeps state in global variables. */
  .m_methods =  C_Common_Methods,
  .m_slots = NULL,
  .m_traverse = NULL,
  .m_clear = NULL,
  .m_free = NULL
};

PyMODINIT_FUNC
PyInit_c_common(void)
{
  return PyModule_Create(&node_module);
}

