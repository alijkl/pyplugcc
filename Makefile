ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

DATE := $(shell date "+%s")
GIT_BR := $(shell cd $(ROOT_DIR) && git rev-parse --abbrev-ref HEAD 2> /dev/null)

ifeq ($(GIT_BR),)
 ARCHIVE_CMD := @echo "not implemented" ; exit 1
else
 ARCHIVE_CMD := cd $(ROOT_DIR) && git archive \
  --format tar.gz \
  --prefix $(shell basename $(ROOT_DIR))/ \
  --output \
    $(ROOT_DIR)../$(shell basename $(ROOT_DIR))-$(DATE)-$(GIT_BR).tar.gz \
  --verbose HEAD
endif

include $(ROOT_DIR)src/Makefile

.PHONY: src test

src: $(PLUGIN_GENERATED_SOURCE_FILES)

test:
	$(MAKE) -C $(ROOT_DIR)test

archive:clean src
	$(ARCHIVE_CMD)

help:
	@echo "plugin:"
	@echo " make $(PLUGIN_LIB_PATH)"
	@echo " make $(PLUGIN_LIB_PATH) DEBUG=1"
	@echo "test:"
	@echo " make test"
	@echo " make test V=1 T=9"
	@echo "generated src:"
	@echo " make src"
