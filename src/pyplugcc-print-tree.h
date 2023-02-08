#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyObject *Py_debug_tree(PyObject *self, PyObject *args) ;
PyObject *Py_debug_raw(PyObject *self, PyObject *args) ;
PyObject *Py_debug(PyObject *self, PyObject *args) ;
PyObject *Py_debug_head(PyObject *self, PyObject *args) ;
PyObject *Py_debug_body(PyObject *self, PyObject *args) ;
PyObject *Py_print_decl_identifier(PyObject *self, PyObject *args) ;
PyObject *Py_node_as_string(PyObject *self, PyObject *args);
PyObject *Py_node_brief_as_string(PyObject *self, PyObject *args);
