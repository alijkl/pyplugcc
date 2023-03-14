TEST_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

ifeq ($(V),)
ECHOING := @
else
EXIT_ON_ERROR := -e
VERBOSE := -v
endif

ifneq ($(T),)
TEST_IDX = -i $(T)
endif

main:: test

include $(TEST_DIR)../src/Makefile

$(TEST_DIR)gccpy.sh:
	@echo -e \#\!/bin/sh \\nscript=$$\1\; \
          shift \1 \\n$(TARGET_GCC) -Wall -Werror \
          \\\\\\n \
          -fplugin=$(PLUGIN_LIB_PATH) \
          \\\\\\n \
          -fplugin-arg-$(PLUGIN_NAME)-script=\$${script} \$$* > $@
	chmod +x $@

$(TEST_DIR)pyplugcc.conf: $(PLUGIN_LIB_PATH)
	$(CONF_MSG) $(PYTHON) $(TEST_DIR)pyplugcc_cli.py -c $@ \
          --gcc $(TARGET_GCC) \
          --plugin_path $(PLUGIN_LIB_PATH) \
          --config_dump

base_test:$(PLUGIN_LIB_PATH) $(TEST_DIR)pyplugcc.conf \
          $(TEST_DIR)test_cli.py $(TEST_DIR)base-test.json
	$(ECHOING)$(PYTHON) $(TEST_DIR)test_cli.py \
          -c $(TEST_DIR)pyplugcc.conf \
          -t $(TEST_DIR)base-test.json \
          $(TEST_IDX) \
          $(VERBOSE) $(EXIT_ON_ERROR)

test: base_test

clean::
	$(RM) $(TEST_DIR)gccpy.sh $(TEST_DIR)pyplugcc.conf
	$(RM) -r $(TEST_DIR)__pycache__/

.phony: test base_test

help:
	@echo "example: make T=\"8 1 2\" V=1"
	@echo " run test 1, 2 and 8 only in verbose mode"
	@echo " default run all the test in quite mode"
