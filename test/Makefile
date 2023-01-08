TEST_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

include $(TEST_DIR)../src/Makefile

$(TEST_DIR)gccpy.sh:
	@echo -e \#\!/bin/sh \\nscript=$$\1\; shift \1 \\n$(TARGET_GCC) -Wall -Werror \\\\\\n -fplugin=$(PLUGIN_LIB_PATH) \\\\\\n -fplugin-arg-$(PLUGIN_NAME)-script=\$${script} \$$* > $@
	chmod +x $@

test01: $(PLUGIN_LIB_PATH) $(TEST_DIR)gccpy.sh
	$(TEST_DIR)gccpy.sh $(TEST_DIR)py/a01_hello.py -c $(TEST_DIR)c/a01.c -o /dev/null
# $(TEST_DIR)gccpy.sh $(TEST_DIR)py/a01_hello.py -c $(TEST_DIR)c++/a01.cc -o /dev/null -l stdc++


test:test01

clean::
	$(RM) $(TEST_DIR)gccpy.sh

.phony: test01 test
