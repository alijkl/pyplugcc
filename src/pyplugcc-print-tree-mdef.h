#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "pyplugcc-print-tree.h"

static PyMethodDef Print_Tree_Methods[] = {
      {
        .ml_name  = "debug_tree",
        .ml_meth  = (PyCFunction)Py_debug_tree,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "debug_raw",
        .ml_meth  = (PyCFunction)Py_debug_raw,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "debug",
        .ml_meth  = (PyCFunction)Py_debug,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "debug_head",
        .ml_meth  = (PyCFunction)Py_debug_head,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "debug_body",
        .ml_meth  = (PyCFunction)Py_debug_body,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "print_decl_identifier",
        .ml_meth  = (PyCFunction)Py_print_decl_identifier,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
  {
    .ml_name  = "node_as_string",
    .ml_meth  = (PyCFunction)Py_node_as_string,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "return a full string ouput of the tree (tree, const char prefix = '', int indent = 0, bool brief_for_visited = true)"
  },
  {
    .ml_name  = "node_brief_as_string",
    .ml_meth  = (PyCFunction)Py_node_brief_as_string,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "return a brief string ouput of the tree (tree, const char prefix = '', int indent = 0, bool brief_for_visited = true)"
  },
  { /* Sentinel */
    .ml_name  = NULL,
    .ml_meth  = NULL,
    .ml_flags = 0,
    .ml_doc   = NULL
  }
};
