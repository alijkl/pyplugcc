/*
extern GTY(()) tree cp_global_trees[CPTI_MAX];
*/

PyObject *Py_cp_global_trees_CPTI_MAX(PyObject *self, PyObject *args) {
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Warray-bounds"
  GTY(()) tree t = cp_global_trees[CPTI_MAX];
  #pragma GCC diagnostic pop
  PyObject *result = PyGccTree_New();
  Set_gccdata(result, (void*) t);
  return result;
}

