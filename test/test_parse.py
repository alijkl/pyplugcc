import sys
import os
sys.path.append(os.path.abspath("../src/gen"))

from extern_parse import extern_parse, FunReturnType, FunParam

if __name__ == "__main__":

    m = [
        [None, "static inline void * * function_args_iter_init (function_args_iterator **i = NULL, const_tree fntype)"],
        [None, "extern tree build_fn_decl (const char *, tree);"],
        [None, "static inline source_range get_expr_source_range (tree expr)"],
        [None, "static inline int struct_ptr_eq (const void *a, const void *b)"],
        [None, "extern void set_decl_tls_model (tree, enum tls_model);"],
        [None, "extern bool valid_constant_size_p (const_tree, cst_size_error * = NULL);"]
    ]

    for e in m:
        # print(e[1])
        # logger.debug(e[1])
        if not e[1].startswith(('extern ', 'static inline ')):
            continue
        t, n, p = extern_parse(e[1])
        print("""
t: {}
n: {}
p: {}
""".format(t, n, p))

        rt = FunReturnType(t)
        print("return type: {}{}".format('*' * rt.is_ptr, rt.type))

        for np in p:
            fp = FunParam(np)
            print("""
param type: {}
param name: {}{}
param default: {}
""".

                  format(fp.type,
                         '*' * fp.is_ptr,
                         fp.name, fp.default
                         )
                  )
