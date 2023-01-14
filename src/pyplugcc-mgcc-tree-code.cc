#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "logging.h"

#include <gcc-plugin.h>
#include "tree.h"

bool add_tree_code_macro_core (PyObject *tree_code_m) {
  int ri = 1;
  char buffer[200];
#define DEFTREECODE(NAME,A,B,C)				\
  ri = PyModule_AddIntMacro(tree_code_m, NAME);
  if (ri < 0) {
    sprintf (buffer, "%s %i PyModule_AddIntMacro\n",
	     err_str.c_str(), ri);
    LOG(buffer);
    Py_DECREF(tree_code_m);
    return false;
  }
#include "tree.def"
#undef DEFTREECODE
  return true;
};

bool add_tree_code_macro_lang_c (PyObject *tree_code_m) {
  int ri = 1;
  char buffer[200];
#define DEFTREECODE(NAME,A,B,C)				\
  ri = PyModule_AddIntMacro(tree_code_m, NAME);
  if (ri < 0) {
    sprintf (buffer, "%s %i PyModule_AddIntMacro\n",
	     err_str.c_str(), ri);
    LOG(buffer);
    Py_DECREF(tree_code_m);
    return false;
  }
#include "c-family/c-common.def"
#undef DEFTREECODE
  return true;
};

bool
add_tree_code_global (PyObject *gcc_module,
		      const std::string name)
{
  int ri;
  bool res_m = true;
  char buffer[200];
  PyObject *tree_code_m = PyModule_New(("gcc." + name).c_str());
  PyObject *moduleDict = PyImport_GetModuleDict();
  PyDict_SetItemString(moduleDict, ("gcc." + name).c_str(), tree_code_m);

  if (name == "tree_code_base") {
    if (! add_tree_code_macro_core(tree_code_m)) res_m = false;
  }else if (name == "tree_code_lang_c") {
    if (! add_tree_code_macro_lang_c(tree_code_m)) res_m = false;
  }else{
    sprintf (buffer, "%s add_tree_code_global not implemented %s\n",
	     err_str.c_str(), name.c_str());
    res_m = false;
  };

  Py_INCREF(tree_code_m);
  ri = PyModule_AddObject(gcc_module, name.c_str(), tree_code_m);
  if (ri < 0 or not res_m) {
    sprintf
      (
       buffer,
       "%s %i %i PyModule_AddObject %s\n",
       err_str.c_str(), ri, res_m, name.c_str());
    LOG(buffer);
    Py_DECREF(gcc_module);
    Py_DECREF(tree_code_m);
    return false;
  }
  return true;
};

bool
init_module_gcc_tree_code (PyObject *gcc_module)
{

  if (! add_tree_code_global (gcc_module, "tree_code_base")) return false;
  if (! add_tree_code_global (gcc_module, "tree_code_lang_c")) return false;

  return true;
}
