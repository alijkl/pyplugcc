#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <gcc-plugin.h>
#include <vector>

#include "logging.h"
#include "pyplugcc-mgcc-tree.h"
#include "pyplugcc-mgcc-tree-code.h"
#include "tree.h"
#include "diagnostic.h"

static const char* py_repr(PyObject *obj) {
  PyObject* repr = PyObject_Repr(obj);
  PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
  char const *bytes = PyBytes_AS_STRING(str);
  Py_XDECREF(repr);
  Py_XDECREF(str);
  return bytes;
}

struct py_callback_struct
{
  PyObject *callback_func = NULL;
  PyObject *kwargs = NULL;
};

static void py_gcc_call (void *gcc_data, void *user_data) {
  char buffer[200];
  PyGILState_STATE pgs;
  struct py_callback_struct *cb = (struct py_callback_struct *)user_data;
  PyObject *args = NULL;
  PyObject *result;
  PyObject *pytree = PyGccTree_New(gcc_data);
  // printf ("pytree o: %p\n", Get_gccdata (pytree));
  args = Py_BuildValue("O",pytree);

  if (PyCallable_Check(cb->callback_func)) {
    pgs = PyGILState_Ensure();
    result = PyObject_CallFunctionObjArgs(cb->callback_func, args, NULL);
    PyGILState_Release(pgs);
    if (! result) {
      PyErr_Print();
      exit(EXIT_FAILURE);
    }
  }else{
    sprintf(buffer, "warning skip %s non callable", py_repr(cb->callback_func));
    LOG(buffer);
  }
  //  PyMem_Free (cb);
}

bool
is_event_without_callback (int event) {
  std::vector<int> nocallback{
    PLUGIN_PASS_MANAGER_SETUP, PLUGIN_INFO, PLUGIN_REGISTER_GGC_ROOTS
  };
  return  std::binary_search(nocallback.begin(), nocallback.end(), event);
}

static PyObject *
Py_register_callback(PyObject *self, PyObject *args)
{
  char buffer[200];
  char *plugin_name;
  int event;
  PyObject *callback_func;
  PyObject *user_data;

  if (!PyArg_ParseTuple
      (
       args, "siO|O:py_register_callback",
       &plugin_name, &event, &callback_func, &user_data
       )
      ) return NULL;

  if (! is_event_without_callback(event)) {
    if (!PyCallable_Check(callback_func)) {
      PyErr_SetString(PyExc_TypeError, "parameter 3 must be callable");
      return NULL;
    }

    py_callback_struct *cb = PyMem_New(py_callback_struct, 1);
    if (! cb) {
      sprintf (buffer, "%s PyMem_New(py_callback_struct, 1)\n", err_str.c_str());
      LOG(buffer);
      return NULL;
    }

    cb->callback_func = callback_func;
    Py_INCREF(callback_func);

    register_callback(plugin_name, event, &py_gcc_call, cb);
    // sprintf (buffer, "register_callback(%s, %i, %s, %p)\n",
    // 	     plugin_name, event, py_repr(cb->callback_func), cb);
    // LOG(buffer);
  }else{
    // FIXME register_callback(plugin_name, event, NULL, specific_user_data);
  }
  Py_INCREF(Py_None);
  return Py_None;
}

/* The number of errors that have been issued so far. */
PyObject *Py_errorcount(PyObject *self, PyObject *args) {
  PyObject *result = Py_BuildValue("i", errorcount);
  return result;
}

/* Similarly, but for sorrys.  */
PyObject *Py_sorrycount(PyObject *self, PyObject *args) {
  PyObject *result = Py_BuildValue("i", sorrycount);
  return result;
}

char * gcc_doc = NULL;

static PyMethodDef Gcc_Methods[] = {
  {
    "register_callback",  (PyCFunction)Py_register_callback, METH_VARARGS,
    "gcc callback command."
  },
  {
    "errorcount",  (PyCFunction)Py_errorcount, METH_NOARGS,
    "The number of errors that have been issued so far."
  },
  {
    "sorrycount",  (PyCFunction)Py_sorrycount, METH_NOARGS,
    "The number of sorrys that have been issued so far."
  },
  {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef gcc_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "gcc",   /* name of module */
  .m_doc = gcc_doc,  /* module documentation, may be NULL */
  .m_size = -1,      /* size of per-interpreter state of the module,
		        or -1 if the module keeps state in global variables. */
  .m_methods =  Gcc_Methods,
  .m_slots = NULL,
  .m_traverse = NULL,
  .m_clear = NULL,
  .m_free = NULL
};

PyMODINIT_FUNC
PyInit_gcc(void)
{
  return PyModule_Create(&gcc_module);
}

bool
init_gcc_module (const char * plugin_name)
{
  int res;
  PyObject *gcc_module;
  char buffer[200];

  gcc_module = PyImport_ImportModule("gcc");
  if (! gcc_module) {
    sprintf (buffer, "%s failed to import module %s\n",
	     err_str.c_str(), "gcc");
    LOG (buffer);
    return false;
  }

  res = PyModule_AddStringMacro(gcc_module, plugin_name);
  if (res < 0) {
    sprintf (buffer, "%s PyModule_AddStringMacro(gcc_module, plugin_name)\n",
	     err_str.c_str());
    LOG(buffer);
    Py_DECREF(gcc_module);
    return false;
  }

  PyObject *event = PyModule_New("gcc.event");
  PyObject *moduleDict = PyImport_GetModuleDict();
  PyDict_SetItemString(moduleDict, "gcc.event", event);

#define DEFEVENT(NAME) \
  res = PyModule_AddIntMacro(event, NAME);
  if (res < 0) {
    sprintf (buffer, "%s PyModule_AddIntMacro(event, NAME)\n",
	     err_str.c_str());
    LOG(buffer);
    Py_DECREF(gcc_module);
    Py_DECREF(event);
    return false;
  }
#include "plugin.def"
#undef DEFEVENT

  Py_INCREF(event);
  res = PyModule_AddObject(gcc_module, "event", event);
  if (res < 0) {
    sprintf (buffer, "%s %i PyModule_AddObject(gcc_module, 'event', event)\n",
	     err_str.c_str(), res);
    LOG(buffer);
    Py_DECREF(gcc_module);
    Py_DECREF(event);
    return false;
  }
  res = init_module_gcc_tree (gcc_module);
  res = init_module_gcc_tree_code (gcc_module);
  return res;
}
