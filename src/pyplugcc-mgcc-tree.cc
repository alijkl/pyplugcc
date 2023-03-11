#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "logging.h"

/*
  GccTree is a Python Class Object
  GccTree->gccdata is a cursor pointing to the data provided by Gcc
 */

struct GccTree {
  void *gccdata = NULL;
};


typedef PyTypeObject _PyGccTreeType;
_PyGccTreeType *PyGccTreeType;

Py_ssize_t PyInstanceMethod_basicsize() {
  return PyLong_AsSsize_t
    (
     PyObject_GetAttrString(
			    (PyObject*)&PyInstanceMethod_Type,
			    "__basicsize__")
     );
}

bool
Set_gccdata(PyObject* self, void* gccdata)
{
  GccTree* p_data = (GccTree*)((uintptr_t)(self) + PyInstanceMethod_basicsize());
  if (p_data) {
    p_data->gccdata = gccdata;
    return true;
  }
  return false;
}

void* Get_gccdata(PyObject* self)
{
  GccTree* p_data = (GccTree*)((uintptr_t)(self) + PyInstanceMethod_basicsize());
  return p_data->gccdata;
}

PyObject *PyGccTree_New(void* gccdata = NULL){
   PyObject *t = _PyObject_New((PyTypeObject*)PyGccTreeType);
   if (Set_gccdata(t, gccdata)) {
     Py_INCREF(t);
     return t;
   }else{
     Py_XDECREF(t);
     Py_RETURN_NONE;
   }
}

bool
init_module_gcc_tree (PyObject *gcc_module)
{
  char buffer[200];
  // printf ("sizeof(GccTree) %li", sizeof(GccTree));
  static PyType_Slot GccTree_Type_slots[] = {
    {0, 0},
  };

  PyType_Spec spec = {
    .name = "GccTree",
    .basicsize = static_cast<int>(PyInstanceMethod_basicsize() +
				  sizeof(GccTree)),
    .itemsize = 0,
    .flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HEAPTYPE,
    .slots = GccTree_Type_slots
  };

  PyGccTreeType = (PyTypeObject*) PyType_FromModuleAndSpec
    (gcc_module, &spec, NULL);

  if (! PyGccTreeType) {
    sprintf (buffer,
	     "%s create PyGccTreeType\n",
	     err_str.c_str());
    LOG(buffer);
    Py_DECREF(gcc_module);
    return false;
  }

  int res = PyModule_AddObject(gcc_module, "GccTree", (PyObject*)PyGccTreeType);
  if (res < 0) {
    sprintf (buffer,
	     "%s %i PyModule_AddObject(gcc_module, 'PyGccTreeType', ...)\n",
	     err_str.c_str(), res);
    LOG(buffer);
    Py_XDECREF(PyGccTreeType);
    return false;
  }

  return true;

}
