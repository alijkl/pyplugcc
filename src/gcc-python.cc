#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
#include <gcc-plugin.h>
#include "logging.h"
#include "tree.h"

static const char* py_repr(PyObject *obj) {
  PyObject* repr = PyObject_Repr(obj);
  PyObject* str = PyUnicode_AsEncodedString(repr, "utf-8", "~E~");
  char const *bytes = PyBytes_AS_STRING(str);
  Py_XDECREF(repr);
  // Py_XDECREF(str);
  // printf ("byte: %s\n", bytes);
  return bytes;
}

struct py_callback_struct
{
  PyObject *callback_func;
  PyObject *kwargs;
};

static void py_gcc_call (void *gcc_data, void *user_data) {
  PyGILState_STATE pgs;
  // tree t = (tree) gcc_data;
  struct py_callback_struct *cb = (struct py_callback_struct *)user_data;
  PyObject *args = NULL;

  pgs = PyGILState_Ensure();
  PyObject_CallFunctionObjArgs(cb->callback_func, args, cb->kwargs);
  PyGILState_Release(pgs);
  pgs = PyGILState_Ensure();

  // PyMem_Free (user_data);
}

static PyObject *
py_register_callback(PyObject *self, PyObject *args)
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

  if (!PyCallable_Check(callback_func)) {
    PyErr_SetString(PyExc_TypeError, "parameter must be callable");
    return NULL;
  }

  py_callback_struct *cb = PyMem_New(py_callback_struct, 1);
  if (! cb) {
    sprintf (buffer, "%s PyMem_New(py_callback_struct, 1)\n", err_str.c_str());
    LOG(buffer);
    return NULL;
  }

  cb->callback_func = callback_func;
  // cb->args = args;
  Py_INCREF(callback_func);

  register_callback(plugin_name, event, &py_gcc_call, cb);
  sprintf (buffer, "register_callback(%s, %i, %s, %p)\n",
	   plugin_name, event, py_repr(cb->callback_func), cb);
  LOG(buffer);

  Py_INCREF(Py_None);
  return Py_None;
}


char * gcc_doc = NULL;

static PyMethodDef Gcc_Methods[] = {
  {
    "register_callback",  (PyCFunction)py_register_callback, METH_VARARGS,
    "gcc callback command."
  },

  {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef gcc_module = {
  .m_base = PyModuleDef_HEAD_INIT,
  .m_name = "gcc",   /* name of module */
  .m_doc = gcc_doc, /* module documentation, may be NULL */
  .m_size = -1,     /* size of per-interpreter state of the module,
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
  if (res != EXIT_SUCCESS) {
    sprintf (buffer, "%s PyModule_AddStringMacro(gcc_module, plugin_name)\n",
	     err_str.c_str());
    LOG(buffer);
    return res == EXIT_SUCCESS;
  }
#define DEFEVENT(NAME)				\
  res = PyModule_AddIntMacro(gcc_module, NAME);
  if (res != EXIT_SUCCESS) {
    sprintf (buffer, "%s PyModule_AddIntMacro(gcc_module, NAME)\n",
	     err_str.c_str());
    LOG(buffer);
    return res == EXIT_SUCCESS;
  }
# include "plugin.def"
# undef DEFEVENT

  return res == EXIT_SUCCESS;

}
