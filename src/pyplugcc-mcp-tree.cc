#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <gcc-plugin.h>

#include "logging.h"
#include "pyplugcc-cp-tree-mdef.h"

char * cp_tree_doc = NULL;

static struct PyModuleDef node_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "gcc.cp_tree",   /* name of module */
  .m_doc = cp_tree_doc,      /* module documentation, may be NULL */
  .m_size = -1,              /* size of per-interpreter state of the module,
                                or -1 if the module keeps state in global variables. */
  .m_methods =  Cp_Tree_Methods,
  .m_slots = NULL,
  .m_traverse = NULL,
  .m_clear = NULL,
  .m_free = NULL
};

PyMODINIT_FUNC
PyInit_cp_tree(void)
{
  return PyModule_Create(&node_module);
}

