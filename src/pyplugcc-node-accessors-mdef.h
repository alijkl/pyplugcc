#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "pyplugcc-node-accessors.h"

static PyMethodDef Node_Accessors_Methods[] = {
  {
    .ml_name  = "TREE_CODE",
    .ml_meth  = (PyCFunction)Py_TREE_CODE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "The tree-code says what kind of node it is"
  },
  {
    .ml_name  = "TREE_CHAIN",
    .ml_meth  = (PyCFunction)Py_TREE_CHAIN,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "Nodes are chained together for many purposes"
  },
  {
    .ml_name  = "TREE_TYPE",
    .ml_meth  = (PyCFunction)Py_TREE_TYPE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "In all nodes that are expressions, this is the data type of the expression"
  },
  {
    .ml_name  = "IDENTIFIER_POINTER",
    .ml_meth  = (PyCFunction)Py_IDENTIFIER_POINTER,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "TREE_PURPOSE",
    .ml_meth  = (PyCFunction)Py_TREE_PURPOSE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "In a TREE_LIST node"
  },
  {
    .ml_name  = "TREE_VALUE",
    .ml_meth  = (PyCFunction)Py_TREE_VALUE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "TYPE_NAME",
    .ml_meth  = (PyCFunction)Py_TYPE_NAME,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "TYPE_VALUES",
    .ml_meth  = (PyCFunction)Py_TYPE_VALUES,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "DECL_CHAIN",
    .ml_meth  = (PyCFunction)Py_DECL_CHAIN,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "DECL_NAME",
    .ml_meth  = (PyCFunction)Py_DECL_NAME,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "This is the name of the object as written by the user"
  },
  {
    .ml_name  = "DECL_SOURCE_FILE",
    .ml_meth  = (PyCFunction)Py_DECL_SOURCE_FILE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "DECL_SOURCE_LINE",
    .ml_meth  = (PyCFunction)Py_DECL_SOURCE_LINE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "DECL_SOURCE_COLUMN",
    .ml_meth  = (PyCFunction)Py_DECL_SOURCE_COLUMN,
    .ml_flags = METH_VARARGS,
    .ml_doc   = ""
  },
  {
    .ml_name  = "DECL_INITIAL",
    .ml_meth  = (PyCFunction)Py_DECL_INITIAL,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "For a FUNCTION_DECL, holds the tree of BINDINGs"
  },
  {
    .ml_name  = "DECL_ASSEMBLER_NAME",
    .ml_meth  = (PyCFunction)Py_DECL_ASSEMBLER_NAME,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "The name of the object as the assembler will see it (but before any translations made by ASM_OUTPUT_LABELREF)"
  },
      {
        .ml_name  = "protected_set_expr_location",
        .ml_meth  = (PyCFunction)Py_protected_set_expr_location,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "protected_set_expr_location_if_unset",
        .ml_meth  = (PyCFunction)Py_protected_set_expr_location_if_unset,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "suppress_location_wrappers",
        .ml_meth  = (PyCFunction)Py_suppress_location_wrappers,
        .ml_flags = METH_NOARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "vector_element_bits",
        .ml_meth  = (PyCFunction)Py_vector_element_bits,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "vector_element_bits_tree",
        .ml_meth  = (PyCFunction)Py_vector_element_bits_tree,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_value_expr_lookup",
        .ml_meth  = (PyCFunction)Py_decl_value_expr_lookup,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_value_expr_insert",
        .ml_meth  = (PyCFunction)Py_decl_value_expr_insert,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_debug_expr_lookup",
        .ml_meth  = (PyCFunction)Py_decl_debug_expr_lookup,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_debug_expr_insert",
        .ml_meth  = (PyCFunction)Py_decl_debug_expr_insert,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_init_priority_insert",
        .ml_meth  = (PyCFunction)Py_decl_init_priority_insert,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_fini_priority_insert",
        .ml_meth  = (PyCFunction)Py_decl_fini_priority_insert,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_optimization_node",
        .ml_meth  = (PyCFunction)Py_build_optimization_node,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_target_option_node",
        .ml_meth  = (PyCFunction)Py_build_target_option_node,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "prepare_target_option_nodes_for_pch",
        .ml_meth  = (PyCFunction)Py_prepare_target_option_nodes_for_pch,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_assembler_name",
        .ml_meth  = (PyCFunction)Py_decl_assembler_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the number of elements encoded directly in a VECTOR_CST."
      },
      {
        .ml_name  = "overwrite_decl_assembler_name",
        .ml_meth  = (PyCFunction)Py_overwrite_decl_assembler_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_comdat_group",
        .ml_meth  = (PyCFunction)Py_decl_comdat_group,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_comdat_group_id",
        .ml_meth  = (PyCFunction)Py_decl_comdat_group_id,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_section_name",
        .ml_meth  = (PyCFunction)Py_decl_section_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "set_decl_section_name",
        .ml_meth  = (PyCFunction)Py_set_decl_section_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_tls_model",
        .ml_meth  = (PyCFunction)Py_decl_tls_model,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "set_decl_tls_model",
        .ml_meth  = (PyCFunction)Py_set_decl_tls_model,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_size",
        .ml_meth  = (PyCFunction)Py_tree_size,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Compute the number of bytes occupied by 'node'. This routine only looks at TREE_CODE and, if the code is TREE_VEC, TREE_VEC_LENGTH."
      },
      {
        .ml_name  = "tree_code_size",
        .ml_meth  = (PyCFunction)Py_tree_code_size,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Compute the number of bytes occupied by a tree with code CODE. This function cannot be used for TREE_VEC or INTEGER_CST nodes, which are of variable length."
      },
      {
        .ml_name  = "allocate_decl_uid",
        .ml_meth  = (PyCFunction)Py_allocate_decl_uid,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Allocate and return a new UID from the DECL_UID namespace."
      },
      {
        .ml_name  = "make_node",
        .ml_meth  = (PyCFunction)Py_make_node,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Lowest level primitive for allocating a node. The TREE_CODE is the only argument. Contents are initialized to zero except for a few of the common fields."
      },
      {
        .ml_name  = "free_node",
        .ml_meth  = (PyCFunction)Py_free_node,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Free tree node."
      },
      {
        .ml_name  = "copy_node",
        .ml_meth  = (PyCFunction)Py_copy_node,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a copy of a node, with all the same contents."
      },
      {
        .ml_name  = "copy_list",
        .ml_meth  = (PyCFunction)Py_copy_list,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a copy of a chain of TREE_LIST nodes."
      },
      {
        .ml_name  = "build_case_label",
        .ml_meth  = (PyCFunction)Py_build_case_label,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a CASE_LABEL_EXPR."
      },
      {
        .ml_name  = "make_tree_binfo",
        .ml_meth  = (PyCFunction)Py_make_tree_binfo,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a BINFO."
      },
      {
        .ml_name  = "make_int_cst",
        .ml_meth  = (PyCFunction)Py_make_int_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make an INTEGER_CST."
      },
      {
        .ml_name  = "make_tree_vec",
        .ml_meth  = (PyCFunction)Py_make_tree_vec,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a TREE_VEC."
      },
      {
        .ml_name  = "grow_tree_vec",
        .ml_meth  = (PyCFunction)Py_grow_tree_vec,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Grow a TREE_VEC."
      },
      {
        .ml_name  = "build0",
        .ml_meth  = (PyCFunction)Py_build0,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build1",
        .ml_meth  = (PyCFunction)Py_build1,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build2",
        .ml_meth  = (PyCFunction)Py_build2,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build3",
        .ml_meth  = (PyCFunction)Py_build3,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build4",
        .ml_meth  = (PyCFunction)Py_build4,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build5",
        .ml_meth  = (PyCFunction)Py_build5,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "double_int_to_tree",
        .ml_meth  = (PyCFunction)Py_double_int_to_tree,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Constructs double_int from tree CST."
      },
      {
        .ml_name  = "build_int_cst",
        .ml_meth  = (PyCFunction)Py_build_int_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "static inline"
      },
      {
        .ml_name  = "build_int_cstu",
        .ml_meth  = (PyCFunction)Py_build_int_cstu,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_int_cst_type",
        .ml_meth  = (PyCFunction)Py_build_int_cst_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "make_vector",
        .ml_meth  = (PyCFunction)Py_make_vector,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vector_from_val",
        .ml_meth  = (PyCFunction)Py_build_vector_from_val,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_uniform_cst",
        .ml_meth  = (PyCFunction)Py_build_uniform_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vec_series",
        .ml_meth  = (PyCFunction)Py_build_vec_series,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_index_vector",
        .ml_meth  = (PyCFunction)Py_build_index_vector,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vector_a_then_b",
        .ml_meth  = (PyCFunction)Py_build_vector_a_then_b,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "recompute_constructor_flags",
        .ml_meth  = (PyCFunction)Py_recompute_constructor_flags,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "verify_constructor_flags",
        .ml_meth  = (PyCFunction)Py_verify_constructor_flags,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_constructor_single",
        .ml_meth  = (PyCFunction)Py_build_constructor_single,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_constructor_from_list",
        .ml_meth  = (PyCFunction)Py_build_constructor_from_list,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_clobber",
        .ml_meth  = (PyCFunction)Py_build_clobber,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_real_from_int_cst",
        .ml_meth  = (PyCFunction)Py_build_real_from_int_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_complex",
        .ml_meth  = (PyCFunction)Py_build_complex,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_complex_inf",
        .ml_meth  = (PyCFunction)Py_build_complex_inf,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_each_one_cst",
        .ml_meth  = (PyCFunction)Py_build_each_one_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_one_cst",
        .ml_meth  = (PyCFunction)Py_build_one_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_minus_one_cst",
        .ml_meth  = (PyCFunction)Py_build_minus_one_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_all_ones_cst",
        .ml_meth  = (PyCFunction)Py_build_all_ones_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_zero_cst",
        .ml_meth  = (PyCFunction)Py_build_zero_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_string",
        .ml_meth  = (PyCFunction)Py_build_string,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_tree_list",
        .ml_meth  = (PyCFunction)Py_build_tree_list,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_decl",
        .ml_meth  = (PyCFunction)Py_build_decl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_fn_decl",
        .ml_meth  = (PyCFunction)Py_build_fn_decl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_translation_unit_decl",
        .ml_meth  = (PyCFunction)Py_build_translation_unit_decl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_block",
        .ml_meth  = (PyCFunction)Py_build_block,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_empty_stmt",
        .ml_meth  = (PyCFunction)Py_build_empty_stmt,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_omp_clause",
        .ml_meth  = (PyCFunction)Py_build_omp_clause,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vl_exp",
        .ml_meth  = (PyCFunction)Py_build_vl_exp,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_call_valist",
        .ml_meth  = (PyCFunction)Py_build_call_valist,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_call_array_loc",
        .ml_meth  = (PyCFunction)Py_build_call_array_loc,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_call_expr_loc_array",
        .ml_meth  = (PyCFunction)Py_build_call_expr_loc_array,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_call_expr_internal_loc_array",
        .ml_meth  = (PyCFunction)Py_build_call_expr_internal_loc_array,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_alloca_call_expr",
        .ml_meth  = (PyCFunction)Py_build_alloca_call_expr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_string_literal",
        .ml_meth  = (PyCFunction)Py_build_string_literal,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "signed_or_unsigned_type_for",
        .ml_meth  = (PyCFunction)Py_signed_or_unsigned_type_for,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Construct various nodes representing data types."
      },
      {
        .ml_name  = "signed_type_for",
        .ml_meth  = (PyCFunction)Py_signed_type_for,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "unsigned_type_for",
        .ml_meth  = (PyCFunction)Py_unsigned_type_for,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "truth_type_for",
        .ml_meth  = (PyCFunction)Py_truth_type_for,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_pointer_type_for_mode",
        .ml_meth  = (PyCFunction)Py_build_pointer_type_for_mode,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_pointer_type",
        .ml_meth  = (PyCFunction)Py_build_pointer_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_reference_type_for_mode",
        .ml_meth  = (PyCFunction)Py_build_reference_type_for_mode,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_reference_type",
        .ml_meth  = (PyCFunction)Py_build_reference_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vector_type_for_mode",
        .ml_meth  = (PyCFunction)Py_build_vector_type_for_mode,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_vector_type",
        .ml_meth  = (PyCFunction)Py_build_vector_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_truth_vector_type_for_mode",
        .ml_meth  = (PyCFunction)Py_build_truth_vector_type_for_mode,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_opaque_vector_type",
        .ml_meth  = (PyCFunction)Py_build_opaque_vector_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_index_type",
        .ml_meth  = (PyCFunction)Py_build_index_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_array_type",
        .ml_meth  = (PyCFunction)Py_build_array_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_nonshared_array_type",
        .ml_meth  = (PyCFunction)Py_build_nonshared_array_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_array_type_nelts",
        .ml_meth  = (PyCFunction)Py_build_array_type_nelts,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_function_type",
        .ml_meth  = (PyCFunction)Py_build_function_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_function_type_array",
        .ml_meth  = (PyCFunction)Py_build_function_type_array,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_varargs_function_type_array",
        .ml_meth  = (PyCFunction)Py_build_varargs_function_type_array,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_method_type_directly",
        .ml_meth  = (PyCFunction)Py_build_method_type_directly,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_method_type",
        .ml_meth  = (PyCFunction)Py_build_method_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_offset_type",
        .ml_meth  = (PyCFunction)Py_build_offset_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_complex_type",
        .ml_meth  = (PyCFunction)Py_build_complex_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "array_type_nelts",
        .ml_meth  = (PyCFunction)Py_array_type_nelts,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "value_member",
        .ml_meth  = (PyCFunction)Py_value_member,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "purpose_member",
        .ml_meth  = (PyCFunction)Py_purpose_member,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "chain_index",
        .ml_meth  = (PyCFunction)Py_chain_index,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_int_cst_equal",
        .ml_meth  = (PyCFunction)Py_tree_int_cst_equal,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Arguments may be null."
      },
      {
        .ml_name  = "tree_fits_shwi_p",
        .ml_meth  = (PyCFunction)Py_tree_fits_shwi_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "The following predicates are safe to call with a null argument."
      },
      {
        .ml_name  = "tree_fits_poly_int64_p",
        .ml_meth  = (PyCFunction)Py_tree_fits_poly_int64_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_fits_uhwi_p",
        .ml_meth  = (PyCFunction)Py_tree_fits_uhwi_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_fits_poly_uint64_p",
        .ml_meth  = (PyCFunction)Py_tree_fits_poly_uint64_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_to_shwi",
        .ml_meth  = (PyCFunction)Py_tree_to_shwi,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_to_uhwi",
        .ml_meth  = (PyCFunction)Py_tree_to_uhwi,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_int_cst_sgn",
        .ml_meth  = (PyCFunction)Py_tree_int_cst_sgn,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_int_cst_sign_bit",
        .ml_meth  = (PyCFunction)Py_tree_int_cst_sign_bit,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_int_cst_min_precision",
        .ml_meth  = (PyCFunction)Py_tree_int_cst_min_precision,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "strip_array_types",
        .ml_meth  = (PyCFunction)Py_strip_array_types,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "excess_precision_type",
        .ml_meth  = (PyCFunction)Py_excess_precision_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "valid_constant_size_p",
        .ml_meth  = (PyCFunction)Py_valid_constant_size_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Desription of the reason why the argument of valid_constant_size_p is not a valid size."
      },
      {
        .ml_name  = "max_object_size",
        .ml_meth  = (PyCFunction)Py_max_object_size,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "make_tree",
        .ml_meth  = (PyCFunction)Py_make_tree,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "From expmed.c. Since rtl.h is included after tree.h, we can't put the prototype here. Rtl.h does declare the prototype if tree.h had been included."
      },
      {
        .ml_name  = "check_lang_type",
        .ml_meth  = (PyCFunction)Py_check_lang_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns true iff CAND and BASE have equivalent language-specific qualifiers."
      },
      {
        .ml_name  = "check_base_type",
        .ml_meth  = (PyCFunction)Py_check_base_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns true iff unqualified CAND and BASE are equivalent."
      },
      {
        .ml_name  = "check_qualified_type",
        .ml_meth  = (PyCFunction)Py_check_qualified_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Check whether CAND is suitable to be returned from get_qualified_type (BASE, TYPE_QUALS)."
      },
      {
        .ml_name  = "get_qualified_type",
        .ml_meth  = (PyCFunction)Py_get_qualified_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a version of the TYPE, qualified as indicated by the TYPE_QUALS, if one exists. If no qualified version exists yet, return NULL_TREE."
      },
      {
        .ml_name  = "build_qualified_type",
        .ml_meth  = (PyCFunction)Py_build_qualified_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Like get_qualified_type, but creates the type if it does not exist. This function never returns NULL_TREE."
      },
      {
        .ml_name  = "build_aligned_type",
        .ml_meth  = (PyCFunction)Py_build_aligned_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Create a variant of type T with alignment ALIGN."
      },
      {
        .ml_name  = "build_distinct_type_copy",
        .ml_meth  = (PyCFunction)Py_build_distinct_type_copy,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a copy of a type node."
      },
      {
        .ml_name  = "build_variant_type_copy",
        .ml_meth  = (PyCFunction)Py_build_variant_type_copy,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "type_hash_canon",
        .ml_meth  = (PyCFunction)Py_type_hash_canon,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "convert",
        .ml_meth  = (PyCFunction)Py_convert,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "size_in_bytes_loc",
        .ml_meth  = (PyCFunction)Py_size_in_bytes_loc,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "int_size_in_bytes",
        .ml_meth  = (PyCFunction)Py_int_size_in_bytes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "max_int_size_in_bytes",
        .ml_meth  = (PyCFunction)Py_max_int_size_in_bytes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "bit_position",
        .ml_meth  = (PyCFunction)Py_bit_position,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "byte_position",
        .ml_meth  = (PyCFunction)Py_byte_position,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "int_byte_position",
        .ml_meth  = (PyCFunction)Py_int_byte_position,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "chainon",
        .ml_meth  = (PyCFunction)Py_chainon,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Concatenate two lists (chains of TREE_LIST nodes) X and Y by making the last node in X point to Y. Returns X, except if X is 0 returns Y."
      },
      {
        .ml_name  = "tree_cons",
        .ml_meth  = (PyCFunction)Py_tree_cons,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Make a new TREE_LIST node from specified PURPOSE, VALUE and CHAIN."
      },
      {
        .ml_name  = "tree_last",
        .ml_meth  = (PyCFunction)Py_tree_last,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the last tree node in a chain."
      },
      {
        .ml_name  = "nreverse",
        .ml_meth  = (PyCFunction)Py_nreverse,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Reverse the order of elements in a chain, and return the new head."
      },
      {
        .ml_name  = "list_length",
        .ml_meth  = (PyCFunction)Py_list_length,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns the length of a chain of nodes (number of chain pointers to follow before reaching a null pointer)."
      },
      {
        .ml_name  = "first_field",
        .ml_meth  = (PyCFunction)Py_first_field,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns the first/last FIELD_DECL in a RECORD_TYPE."
      },
      {
        .ml_name  = "last_field",
        .ml_meth  = (PyCFunction)Py_last_field,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "initializer_zerop",
        .ml_meth  = (PyCFunction)Py_initializer_zerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Given an initializer INIT, return TRUE if INIT is zero or some aggregate of zeros. Otherwise return FALSE. If NONZERO is not null, set *NONZERO if and only if INIT is known not to be all zeros. The combination of return value of false and *NONZERO false implies that INIT may but need not be all zeros. Other combinations indicate definitive answers."
      },
      {
        .ml_name  = "initializer_each_zero_or_onep",
        .ml_meth  = (PyCFunction)Py_initializer_each_zero_or_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "vector_cst_elt",
        .ml_meth  = (PyCFunction)Py_vector_cst_elt,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "uniform_vector_p",
        .ml_meth  = (PyCFunction)Py_uniform_vector_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Given a vector VEC, return its first element if all elements are the same. Otherwise return NULL_TREE."
      },
      {
        .ml_name  = "uniform_integer_cst_p",
        .ml_meth  = (PyCFunction)Py_uniform_integer_cst_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "If the argument is INTEGER_CST, return it. If the argument is vector with all elements the same INTEGER_CST, return that INTEGER_CST. Otherwise return NULL_TREE."
      },
      {
        .ml_name  = "single_nonzero_element",
        .ml_meth  = (PyCFunction)Py_single_nonzero_element,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "zerop",
        .ml_meth  = (PyCFunction)Py_zerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "zerop (tree x) is nonzero if X is a constant of value 0."
      },
      {
        .ml_name  = "integer_zerop",
        .ml_meth  = (PyCFunction)Py_integer_zerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_zerop (tree x) is nonzero if X is an integer constant of value 0."
      },
      {
        .ml_name  = "integer_onep",
        .ml_meth  = (PyCFunction)Py_integer_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_onep (tree x) is nonzero if X is an integer constant of value 1."
      },
      {
        .ml_name  = "integer_each_onep",
        .ml_meth  = (PyCFunction)Py_integer_each_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_onep (tree x) is nonzero if X is an integer constant of value 1, or a vector or complex where each part is 1."
      },
      {
        .ml_name  = "integer_all_onesp",
        .ml_meth  = (PyCFunction)Py_integer_all_onesp,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_all_onesp (tree x) is nonzero if X is an integer constant all of whose significant bits are 1."
      },
      {
        .ml_name  = "integer_minus_onep",
        .ml_meth  = (PyCFunction)Py_integer_minus_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_minus_onep (tree x) is nonzero if X is an integer constant of value -1."
      },
      {
        .ml_name  = "integer_pow2p",
        .ml_meth  = (PyCFunction)Py_integer_pow2p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_pow2p (tree x) is nonzero is X is an integer constant with exactly one bit 1."
      },
      {
        .ml_name  = "integer_nonzerop",
        .ml_meth  = (PyCFunction)Py_integer_nonzerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_nonzerop (tree x) is nonzero if X is an integer constant with a nonzero value."
      },
      {
        .ml_name  = "integer_truep",
        .ml_meth  = (PyCFunction)Py_integer_truep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "integer_truep (tree x) is nonzero if X is an integer constant of value 1 or a vector where each element is an integer constant of value -1."
      },
      {
        .ml_name  = "cst_and_fits_in_hwi",
        .ml_meth  = (PyCFunction)Py_cst_and_fits_in_hwi,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "num_ending_zeros",
        .ml_meth  = (PyCFunction)Py_num_ending_zeros,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "fixed_zerop",
        .ml_meth  = (PyCFunction)Py_fixed_zerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "fixed_zerop (tree x) is nonzero if X is a fixed-point constant of value 0."
      },
      {
        .ml_name  = "staticp",
        .ml_meth  = (PyCFunction)Py_staticp,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "staticp (tree x) is nonzero if X is a reference to data allocated at a fixed address in memory. Returns the outermost data."
      },
      {
        .ml_name  = "save_expr",
        .ml_meth  = (PyCFunction)Py_save_expr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "save_expr (EXP) returns an expression equivalent to EXP but it can be used multiple times within context CTX and only evaluate EXP once."
      },
      {
        .ml_name  = "tree_invariant_p",
        .ml_meth  = (PyCFunction)Py_tree_invariant_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return true if T is function-invariant."
      },
      {
        .ml_name  = "skip_simple_arithmetic",
        .ml_meth  = (PyCFunction)Py_skip_simple_arithmetic,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Look inside EXPR into any simple arithmetic operations. Return the outermost non-arithmetic or non-invariant node."
      },
      {
        .ml_name  = "skip_simple_constant_arithmetic",
        .ml_meth  = (PyCFunction)Py_skip_simple_constant_arithmetic,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Look inside EXPR into simple arithmetic operations involving constants. Return the outermost non-arithmetic or non-constant node."
      },
      {
        .ml_name  = "contains_placeholder_p",
        .ml_meth  = (PyCFunction)Py_contains_placeholder_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return true if EXP contains a PLACEHOLDER_EXPR, i.e. if it represents a size or offset that depends on a field within a record."
      },
      {
        .ml_name  = "type_contains_placeholder_p",
        .ml_meth  = (PyCFunction)Py_type_contains_placeholder_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return true if any part of the structure of TYPE involves a PLACEHOLDER_EXPR directly. This includes size, bounds, qualifiers (for QUAL_UNION_TYPE) and field positions."
      },
      {
        .ml_name  = "substitute_in_expr",
        .ml_meth  = (PyCFunction)Py_substitute_in_expr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Given a tree EXP, a FIELD_DECL F, and a replacement value R, return a tree with all occurrences of references to F in a PLACEHOLDER_EXPR replaced by R. Also handle VAR_DECLs and CONST_DECLs. Note that we assume here that EXP contains only arithmetic expressions or CALL_EXPRs with PLACEHOLDER_EXPRs occurring only in their argument list."
      },
      {
        .ml_name  = "substitute_placeholder_in_expr",
        .ml_meth  = (PyCFunction)Py_substitute_placeholder_in_expr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Similar, but look for a PLACEHOLDER_EXPR in EXP and find a replacement for it within OBJ, a tree that is an object or a chain of references."
      },
      {
        .ml_name  = "stabilize_reference",
        .ml_meth  = (PyCFunction)Py_stabilize_reference,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "stabilize_reference (EXP) returns a reference equivalent to EXP but it can be used multiple times and only evaluate the subexpressions once."
      },
      {
        .ml_name  = "get_unwidened",
        .ml_meth  = (PyCFunction)Py_get_unwidened,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return EXP, stripped of any conversions to wider types in such a way that the result of converting to type FOR_TYPE is the same as if EXP were converted to FOR_TYPE. If FOR_TYPE is 0, it signifies EXP's type."
      },
      {
        .ml_name  = "get_narrower",
        .ml_meth  = (PyCFunction)Py_get_narrower,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return OP or a simpler expression for a narrower value which can be sign-extended or zero-extended to give back OP. Store in *UNSIGNEDP_PTR either 1 if the value should be zero-extended or 0 if the value should be sign-extended."
      },
      {
        .ml_name  = "get_containing_scope",
        .ml_meth  = (PyCFunction)Py_get_containing_scope,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Given a DECL or TYPE, return the scope in which it was declared, or NUL_TREE if there is no containing scope."
      },
      {
        .ml_name  = "get_ultimate_context",
        .ml_meth  = (PyCFunction)Py_get_ultimate_context,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns the ultimate TRANSLATION_UNIT_DECL context of DECL or NULL."
      },
      {
        .ml_name  = "decl_function_context",
        .ml_meth  = (PyCFunction)Py_decl_function_context,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the FUNCTION_DECL which provides this _DECL with its context, or zero if none."
      },
      {
        .ml_name  = "decl_type_context",
        .ml_meth  = (PyCFunction)Py_decl_type_context,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the RECORD_TYPE, UNION_TYPE, or QUAL_UNION_TYPE which provides this _DECL with its context, or zero if none."
      },
      {
        .ml_name  = "real_zerop",
        .ml_meth  = (PyCFunction)Py_real_zerop,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return true if EXPR is the real constant zero."
      },
      {
        .ml_name  = "clean_symbol_name",
        .ml_meth  = (PyCFunction)Py_clean_symbol_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_file_function_name",
        .ml_meth  = (PyCFunction)Py_get_file_function_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_callee_fndecl",
        .ml_meth  = (PyCFunction)Py_get_callee_fndecl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "type_num_arguments",
        .ml_meth  = (PyCFunction)Py_type_num_arguments,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "type_argument_type",
        .ml_meth  = (PyCFunction)Py_type_argument_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "associative_tree_code",
        .ml_meth  = (PyCFunction)Py_associative_tree_code,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "commutative_tree_code",
        .ml_meth  = (PyCFunction)Py_commutative_tree_code,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "commutative_ternary_tree_code",
        .ml_meth  = (PyCFunction)Py_commutative_ternary_tree_code,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "operation_can_overflow",
        .ml_meth  = (PyCFunction)Py_operation_can_overflow,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "operation_no_trapping_overflow",
        .ml_meth  = (PyCFunction)Py_operation_no_trapping_overflow,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "upper_bound_in_type",
        .ml_meth  = (PyCFunction)Py_upper_bound_in_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "lower_bound_in_type",
        .ml_meth  = (PyCFunction)Py_lower_bound_in_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "operand_equal_for_phi_arg_p",
        .ml_meth  = (PyCFunction)Py_operand_equal_for_phi_arg_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "create_artificial_label",
        .ml_meth  = (PyCFunction)Py_create_artificial_label,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_name",
        .ml_meth  = (PyCFunction)Py_get_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "stdarg_p",
        .ml_meth  = (PyCFunction)Py_stdarg_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "prototype_p",
        .ml_meth  = (PyCFunction)Py_prototype_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "is_typedef_decl",
        .ml_meth  = (PyCFunction)Py_is_typedef_decl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "typedef_variant_p",
        .ml_meth  = (PyCFunction)Py_typedef_variant_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "auto_var_p",
        .ml_meth  = (PyCFunction)Py_auto_var_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "auto_var_in_fn_p",
        .ml_meth  = (PyCFunction)Py_auto_var_in_fn_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_low_bits_mask",
        .ml_meth  = (PyCFunction)Py_build_low_bits_mask,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_nop_conversion_p",
        .ml_meth  = (PyCFunction)Py_tree_nop_conversion_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_strip_nop_conversions",
        .ml_meth  = (PyCFunction)Py_tree_strip_nop_conversions,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_strip_sign_nop_conversions",
        .ml_meth  = (PyCFunction)Py_tree_strip_sign_nop_conversions,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "strip_invariant_refs",
        .ml_meth  = (PyCFunction)Py_strip_invariant_refs,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "lhd_gcc_personality",
        .ml_meth  = (PyCFunction)Py_lhd_gcc_personality,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "assign_assembler_name_if_needed",
        .ml_meth  = (PyCFunction)Py_assign_assembler_name_if_needed,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "warn_deprecated_use",
        .ml_meth  = (PyCFunction)Py_warn_deprecated_use,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "cache_integer_cst",
        .ml_meth  = (PyCFunction)Py_cache_integer_cst,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "combined_fn_name",
        .ml_meth  = (PyCFunction)Py_combined_fn_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "strip_float_extensions",
        .ml_meth  = (PyCFunction)Py_strip_float_extensions,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the starting bit offset of BIT_FIELD_REF T, in cases where it is known to be a poly_uint64. (This is always true at the gimple level.)"
      },
      {
        .ml_name  = "really_constant_p",
        .ml_meth  = (PyCFunction)Py_really_constant_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "ptrdiff_tree_p",
        .ml_meth  = (PyCFunction)Py_ptrdiff_tree_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_address_invariant_p",
        .ml_meth  = (PyCFunction)Py_decl_address_invariant_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "decl_address_ip_invariant_p",
        .ml_meth  = (PyCFunction)Py_decl_address_ip_invariant_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "int_fits_type_p",
        .ml_meth  = (PyCFunction)Py_int_fits_type_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_type_static_bounds",
        .ml_meth  = (PyCFunction)Py_get_type_static_bounds,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "variably_modified_type_p",
        .ml_meth  = (PyCFunction)Py_variably_modified_type_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_log2",
        .ml_meth  = (PyCFunction)Py_tree_log2,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_floor_log2",
        .ml_meth  = (PyCFunction)Py_tree_floor_log2,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_ctz",
        .ml_meth  = (PyCFunction)Py_tree_ctz,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "simple_cst_equal",
        .ml_meth  = (PyCFunction)Py_simple_cst_equal,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "compare_tree_int",
        .ml_meth  = (PyCFunction)Py_compare_tree_int,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Compat version until all callers are converted. Return hash for TREE with SEED."
      },
      {
        .ml_name  = "type_list_equal",
        .ml_meth  = (PyCFunction)Py_type_list_equal,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "chain_member",
        .ml_meth  = (PyCFunction)Py_chain_member,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "dump_tree_statistics",
        .ml_meth  = (PyCFunction)Py_dump_tree_statistics,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "recompute_tree_invariant_for_addr_expr",
        .ml_meth  = (PyCFunction)Py_recompute_tree_invariant_for_addr_expr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "needs_to_live_in_memory",
        .ml_meth  = (PyCFunction)Py_needs_to_live_in_memory,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "reconstruct_complex_type",
        .ml_meth  = (PyCFunction)Py_reconstruct_complex_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "real_onep",
        .ml_meth  = (PyCFunction)Py_real_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "real_minus_onep",
        .ml_meth  = (PyCFunction)Py_real_minus_onep,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "init_ttree",
        .ml_meth  = (PyCFunction)Py_init_ttree,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_common_tree_nodes",
        .ml_meth  = (PyCFunction)Py_build_common_tree_nodes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_common_builtin_nodes",
        .ml_meth  = (PyCFunction)Py_build_common_builtin_nodes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_nonstandard_integer_type",
        .ml_meth  = (PyCFunction)Py_build_nonstandard_integer_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_nonstandard_boolean_type",
        .ml_meth  = (PyCFunction)Py_build_nonstandard_boolean_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_range_type",
        .ml_meth  = (PyCFunction)Py_build_range_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_nonshared_range_type",
        .ml_meth  = (PyCFunction)Py_build_nonshared_range_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "subrange_type_for_debug_p",
        .ml_meth  = (PyCFunction)Py_subrange_type_for_debug_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "int_cst_value",
        .ml_meth  = (PyCFunction)Py_int_cst_value,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_block",
        .ml_meth  = (PyCFunction)Py_tree_block,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_set_block",
        .ml_meth  = (PyCFunction)Py_tree_set_block,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "block_ultimate_origin",
        .ml_meth  = (PyCFunction)Py_block_ultimate_origin,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_binfo_at_offset",
        .ml_meth  = (PyCFunction)Py_get_binfo_at_offset,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "virtual_method_call_p",
        .ml_meth  = (PyCFunction)Py_virtual_method_call_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "obj_type_ref_class",
        .ml_meth  = (PyCFunction)Py_obj_type_ref_class,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "types_same_for_odr",
        .ml_meth  = (PyCFunction)Py_types_same_for_odr,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "contains_bitfld_component_ref_p",
        .ml_meth  = (PyCFunction)Py_contains_bitfld_component_ref_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "block_may_fallthru",
        .ml_meth  = (PyCFunction)Py_block_may_fallthru,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "using_eh_for_cleanups",
        .ml_meth  = (PyCFunction)Py_using_eh_for_cleanups,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "using_eh_for_cleanups_p",
        .ml_meth  = (PyCFunction)Py_using_eh_for_cleanups_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_tree_code_name",
        .ml_meth  = (PyCFunction)Py_get_tree_code_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "set_call_expr_flags",
        .ml_meth  = (PyCFunction)Py_set_call_expr_flags,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "walk_tree_without_duplicates_1",
        .ml_meth  = (PyCFunction)Py_walk_tree_without_duplicates_1,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "drop_tree_overflow",
        .ml_meth  = (PyCFunction)Py_drop_tree_overflow,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_base_address",
        .ml_meth  = (PyCFunction)Py_get_base_address,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Given a memory reference expression T, return its base address. The base address of a memory reference expression is the main object being referenced."
      },
      {
        .ml_name  = "array_ref_element_size",
        .ml_meth  = (PyCFunction)Py_array_ref_element_size,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a tree of sizetype representing the size, in bytes, of the element of EXP, an ARRAY_REF or an ARRAY_RANGE_REF."
      },
      {
        .ml_name  = "get_typenode_from_name",
        .ml_meth  = (PyCFunction)Py_get_typenode_from_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a typenode for the standard C type with a given name."
      },
      {
        .ml_name  = "array_ref_up_bound",
        .ml_meth  = (PyCFunction)Py_array_ref_up_bound,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a tree representing the upper bound of the array mentioned in EXP, an ARRAY_REF or an ARRAY_RANGE_REF."
      },
      {
        .ml_name  = "array_ref_low_bound",
        .ml_meth  = (PyCFunction)Py_array_ref_low_bound,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a tree representing the lower bound of the array mentioned in EXP, an ARRAY_REF or an ARRAY_RANGE_REF."
      },
      {
        .ml_name  = "array_at_struct_end_p",
        .ml_meth  = (PyCFunction)Py_array_at_struct_end_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Returns true if REF is an array reference or a component reference to an array at the end of a structure. If this is the case, the array may be allocated larger than its upper bound implies."
      },
      {
        .ml_name  = "component_ref_field_offset",
        .ml_meth  = (PyCFunction)Py_component_ref_field_offset,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return a tree representing the offset, in bytes, of the field referenced by EXP. This does not include any offset in DECL_FIELD_BIT_OFFSET."
      },
      {
        .ml_name  = "component_ref_size",
        .ml_meth  = (PyCFunction)Py_component_ref_size,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Return the size of the member referenced by the COMPONENT_REF, using its initializer expression if necessary in order to determine the size of an initialized flexible array member. The size might be zero for an object with an uninitialized flexible array member or null if it cannot be determined."
      },
      {
        .ml_name  = "tree_map_base_eq",
        .ml_meth  = (PyCFunction)Py_tree_map_base_eq,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_map_base_hash",
        .ml_meth  = (PyCFunction)Py_tree_map_base_hash,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_map_base_marked_p",
        .ml_meth  = (PyCFunction)Py_tree_map_base_marked_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "verify_type",
        .ml_meth  = (PyCFunction)Py_verify_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "gimple_canonical_types_compatible_p",
        .ml_meth  = (PyCFunction)Py_gimple_canonical_types_compatible_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "type_with_interoperable_signedness",
        .ml_meth  = (PyCFunction)Py_type_with_interoperable_signedness,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_range_pos_neg",
        .ml_meth  = (PyCFunction)Py_get_range_pos_neg,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "valid_new_delete_pair_p",
        .ml_meth  = (PyCFunction)Py_valid_new_delete_pair_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_map_hash",
        .ml_meth  = (PyCFunction)Py_tree_map_hash,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "tree_decl_map_hash",
        .ml_meth  = (PyCFunction)Py_tree_decl_map_hash,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "make_anon_name",
        .ml_meth  = (PyCFunction)Py_make_anon_name,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "For anonymous aggregate types, we need some sort of name to hold on to. In practice, this should not appear, but it should not be harmful if it does. Identifiers returned will be IDENTIFIER_ANON_P."
      },
      {
        .ml_name  = "set_decl_rtl",
        .ml_meth  = (PyCFunction)Py_set_decl_rtl,
        .ml_flags = METH_VARARGS,
        .ml_doc   = "Assign the RTX to declaration."
      },
      {
        .ml_name  = "complete_ctor_at_level_p",
        .ml_meth  = (PyCFunction)Py_complete_ctor_at_level_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "get_inner_reference",
        .ml_meth  = (PyCFunction)Py_get_inner_reference,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "build_personality_function",
        .ml_meth  = (PyCFunction)Py_build_personality_function,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "nonnull_arg_p",
        .ml_meth  = (PyCFunction)Py_nonnull_arg_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "is_empty_type",
        .ml_meth  = (PyCFunction)Py_is_empty_type,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "default_is_empty_record",
        .ml_meth  = (PyCFunction)Py_default_is_empty_record,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "flexible_array_type_p",
        .ml_meth  = (PyCFunction)Py_flexible_array_type_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "arg_int_size_in_bytes",
        .ml_meth  = (PyCFunction)Py_arg_int_size_in_bytes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "arg_size_in_bytes",
        .ml_meth  = (PyCFunction)Py_arg_size_in_bytes,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
      {
        .ml_name  = "expr_type_first_operand_type_p",
        .ml_meth  = (PyCFunction)Py_expr_type_first_operand_type_p,
        .ml_flags = METH_VARARGS,
        .ml_doc   = ""
      },
  {
    .ml_name  = "IS_NULL_TREE",
    .ml_meth  = (PyCFunction)Py_IS_NULL_TREE,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "return True if is NULL_TREE"
  },
  {
    .ml_name  = "tree_real_cst_to_float",
    .ml_meth  = (PyCFunction)Py_tree_real_cst_to_float,
    .ml_flags = METH_VARARGS,
    .ml_doc   = "Render a REAL_TYPE constant as a Python float"
  },
  { /* Sentinel */
    .ml_name  = NULL,
    .ml_meth  = NULL,
    .ml_flags = 0,
    .ml_doc   = NULL
  }
};
