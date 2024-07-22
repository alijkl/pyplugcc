#include <gcc-plugin.h>
#include "cp/cp-tree.h"

GTY(()) tree cp_global_trees[CPTI_MAX] __attribute__((weak));
