#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <gcc-plugin.h>
// #include <vector>

#include "logging.h"
#include "tree.h"
#include "node-accessors-mdef.h"

char * node_doc = NULL;

static struct PyModuleDef node_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "gcc.node",   /* name of module */
  .m_doc = node_doc,  /* module documentation, may be NULL */
  .m_size = -1,      /* size of per-interpreter state of the module,
		        or -1 if the module keeps state in global variables. */
  .m_methods =  Node_Methods,
  .m_slots = NULL,
  .m_traverse = NULL,
  .m_clear = NULL,
  .m_free = NULL
};

PyMODINIT_FUNC
PyInit_node(void)
{
  return PyModule_Create(&node_module);
}

