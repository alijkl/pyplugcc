/*
#define TREE_OPERAND(NODE, I) TREE_OPERAND_CHECK (NODE, I)
*/
PyObject *Py_TREE_OPERAND(PyObject *self, PyObject *args) {
  PyObject *NODE;
  int I = 0;
  if (!PyArg_ParseTuple (args, "O|i:TREE_OPERAND", &NODE, &I)) return NULL;
  void *t = TREE_OPERAND((tree) Get_gccdata(NODE), I);
  PyObject *result = PyGccTree_New();
  Set_gccdata(result, (void*) t);
  return result;
}
