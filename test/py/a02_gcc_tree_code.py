import gcc
from gcc.event import *
from gcc.tree_code_base import *
from gcc.tree_code_lang_c import *
from gcc import GccTree


print ("gcc globals")
print ("{}\n".format(dir(gcc)))
print ("gcc.tree_code_base")
print ("{}\n".format(dir(gcc.tree_code_base)))
print ("gcc.tree_code_lang_c")
print (dir(gcc.tree_code_lang_c))
print ()
assert isinstance(ERROR_MARK, int)
# Base
assert isinstance(ABSU_EXPR, int)
assert isinstance(NULLPTR_TYPE, int)
assert isinstance(SAD_EXPR, int)
assert isinstance(WITH_SIZE_EXPR, int)
# Lang C
assert isinstance(BREAK_STMT, int)
assert isinstance(DO_STMT, int)
assert isinstance(WHILE_STMT, int)
