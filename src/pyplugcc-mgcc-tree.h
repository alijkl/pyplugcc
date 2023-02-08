#define PY_SSIZE_T_CLEAN
#include <Python.h>

bool
init_module_gcc_tree (PyObject *gcc_module);

PyObject *PyGccTree_New(void* gccdata = NULL);

bool Set_gccdata(PyObject* self, void* gccdata);
void* Get_gccdata(PyObject* self);
