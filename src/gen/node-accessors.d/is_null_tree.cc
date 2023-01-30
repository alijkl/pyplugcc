

/* return True if is NULL_TREE */

PyObject *Py_IS_NULL_TREE(PyObject *self, PyObject *args) {
  PyObject *NODE;
  if (!PyArg_ParseTuple (args, "O:Py_IS_NULL_TREE", &NODE)) return NULL;
  long r = (tree) Get_gccdata(NODE) == NULL_TREE;
  PyObject *result = PyBool_FromLong(r);
  return result;
}
