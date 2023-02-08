/*
return a brief string ouput of the tree (tree, const char prefix = '', int indent = 0, bool brief_for_visited = true)
*/

PyObject *Py_node_brief_as_string(PyObject *self, PyObject *args) {
  FILE * file_0;
  char * char_1 = (char *)"";
  PyObject *tree_2;
  int int_3 = 0;
  char *ptr;
  size_t size;
  file_0 = open_memstream(&ptr, &size);
  if (file_0 == NULL) return  PyErr_SetFromErrno(PyExc_RuntimeError);
  if (!PyArg_ParseTuple (args,"O|si:print_node", &tree_2, &char_1,
    &int_3)) return NULL;
  print_node_brief(file_0, char_1, (tree)Get_gccdata(tree_2), int_3);
  fclose(file_0);
  PyObject *result = Py_BuildValue("s#", ptr, size);
  free(ptr);
  return result;
}
