/*
  Render a REAL_TYPE constant as a Python float
 */
PyObject *Py_tree_real_cst_to_float(PyObject *self, PyObject *args) {
  PyObject *NODE;
  PyObject *tmp;
  PyObject *result;
  size_t digits = 0;
  int crop_trailing_zeros = 1;
  char str[256];
  if (!PyArg_ParseTuple (args, "O:Py_TREE_REAL_CST", &NODE)) return NULL;
  const real_value *r = TREE_REAL_CST_PTR((tree) Get_gccdata(NODE));
  if (real_isnan(r)) {
    tmp = Py_BuildValue("s", "nan", 2);
  }else{
    real_to_decimal (str, r, sizeof (str) - 1, digits, crop_trailing_zeros);
    tmp = Py_BuildValue("s", str, sizeof(str));
  }
  result = PyFloat_FromString (tmp);
  Py_DECREF(tmp);
  return result;
}
