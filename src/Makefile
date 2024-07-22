SRC_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

DEBUG?=
HOST_GCC ?= g++
TARGET_GCC ?= gcc
PYTHON ?= python3
PYTHON_VERSION= $(shell $(PYTHON) -c \
  "import sys; print('.'.join(sys.version.partition(' ')[0].rsplit('.')[0:-1]))")
PYTHON_CONFIG ?= python$(PYTHON_VERSION)-config

PLUGIN_GENERATED_SOURCE_FILES := \
                       $(SRC_DIR)pyplugcc-node-accessors.cc \
                       $(SRC_DIR)pyplugcc-print-tree.cc \
                       $(SRC_DIR)pyplugcc-c-common.cc \
                       $(SRC_DIR)pyplugcc-c-tree.cc \
                       $(SRC_DIR)pyplugcc-cp-tree.cc \

PLUGIN_SOURCE_FILES := \
                       $(SRC_DIR)logging.cc \
                       $(SRC_DIR)pyplugcc.cc \
                       $(SRC_DIR)pyplugcc-mgcc.cc \
                       $(SRC_DIR)pyplugcc-mgcc-tree.cc \
                       $(SRC_DIR)pyplugcc-mgcc-tree-code.cc \
                       $(SRC_DIR)pyplugcc-mgcc-mnode.cc \
                       $(SRC_DIR)pyplugcc-mprint-tree.cc \
                       $(SRC_DIR)pyplugcc-mc-common.cc \
                       $(SRC_DIR)pyplugcc-mc-tree.cc \
                       $(SRC_DIR)pyplugcc-mcp-tree.cc \
                       $(SRC_DIR)pyplugcc-cp-weak.cc \

PLUGIN_SOURCE_FILES += $(PLUGIN_GENERATED_SOURCE_FILES)

PLUGIN_GENERATED_SOURCE_NAME := $(patsubst pyplugcc-%.cc,%,$(filter %,$(notdir $(PLUGIN_GENERATED_SOURCE_FILES))))

GCCPLUGINS_DIR:= $(shell $(TARGET_GCC) -print-file-name=plugin)
GCC_MAJOR := $(shell \
               $(HOST_GCC) --version | head -n1 | cut -d' ' -f3 | cut -d'.' -f1)
ifeq ($(shell test $(GCC_MAJOR) -gt 9; echo $$?),0)
  GCC_STD ?= -std=c++20
endif
ifneq ($(filter $(GCC_MAJOR),8 9),)
  GCC_STD ?= -std=c++2a
endif

hardening_flags=-D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS \
                -fasynchronous-unwind-tables -fexceptions -fpic -shared \
                -fstack-clash-protection -fstack-protector-strong \
                -grecord-gcc-switches -fcf-protection -pipe \
                -Werror=format-security -Wl,-z,now -Wl,-z,relro

GCC_OPT ?=
ifeq ($(DEBUG),)
  GCC_OPT+=-O2 $(hardening_flags)
  CONF_MSG = @echo CONFIG: $@ &&
  GEN_MSG = @echo Generate: $(notdir $*{.cc,.h,-mdef.h}) &&
  COMPILE_MSG = @echo Compile: $< &&
  LINK_MSG = @echo Link: $@ &&
else
  GCC_OPT+=-O0 -g3
endif
GCC_OPT_FLAGS+=$(GCC_STD) $(GCC_OPT)

CXXFLAGS+= -fPIC -fno-rtti -Wall $(GCC_OPT_FLAGS)
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include

PYTHON_INCLUDE = $(shell $(PYTHON_CONFIG) --includes)

# LD_FLAGS+= -L$(GCCPLUGINS_DIR) -lcp1plugin
LD_FLAGS+= $(shell $(PYTHON_CONFIG) --ldflags)
LD_FLAGS+= -lpython$(PYTHON_VERSION)

PLUGIN_LIB_PATH=$(SRC_DIR)pyplugcc$(GCC_MAJOR).so
PLUGIN_NAME=$(shell basename $(PLUGIN_LIB_PATH) .so)

%.o: %.cc $(PLUGIN_GENERATED_SOURCE_FILES)
	$(COMPILE_MSG) $(HOST_GCC) $(CXXFLAGS) $(PYTHON_INCLUDE) -c $< -o $@

$(PLUGIN_LIB_PATH): $(PLUGIN_SOURCE_FILES:.cc=.o)
	$(LINK_MSG) $(HOST_GCC) -shared $(CXXFLAGS) $(PYTHON_INCLUDE) $(LD_FLAGS) $^ -o $@

$(SRC_DIR)pyplugcc-node-accessors.cc \
$(SRC_DIR)pyplugcc-node-accessors.h \
$(SRC_DIR)pyplugcc-node-accessors-mdef.h: \
  $(SRC_DIR)gen/node-accessors.cfg $(SRC_DIR)gen/h2pyfun.py \
  $(wildcard $(SRC_DIR)gen/node-accessors.d/*.cc)
	$(GEN_MSG) $(PYTHON) $(SRC_DIR)gen/h2pyfun.py \
         -c $(SRC_DIR)gen/node-accessors.cfg \
         --header $(GCCPLUGINS_DIR)/include/tree.h \
         > /dev/null

$(SRC_DIR)pyplugcc-print-tree.cc \
$(SRC_DIR)pyplugcc-pyplugcc-print-tree.h \
$(SRC_DIR)pyplugcc-pyplugcc-print-tree-mdef.h: \
   $(SRC_DIR)gen/print-tree.cfg $(SRC_DIR)gen/h2pyfun.py \
   $(wildcard $(SRC_DIR)gen/print-tree.d/*.cc)
	$(GEN_MSG) $(PYTHON) $(SRC_DIR)gen/h2pyfun.py \
         -c $(SRC_DIR)gen/print-tree.cfg \
         --header $(GCCPLUGINS_DIR)/include/print-tree.h \
         > /dev/null

$(SRC_DIR)pyplugcc-c-common.cc \
$(SRC_DIR)pyplugcc-pyplugcc-c-common.h \
$(SRC_DIR)pyplugcc-pyplugcc-c-common-mdef.h: \
   $(SRC_DIR)gen/c-common.cfg $(SRC_DIR)gen/h2pyfun.py \
   $(wildcard $(SRC_DIR)gen/c-common.d/*.cc)
	$(GEN_MSG) $(PYTHON) $(SRC_DIR)gen/h2pyfun.py \
         -c $(SRC_DIR)gen/c-common.cfg \
         --header $(GCCPLUGINS_DIR)/include/c-family/c-common.h \
         > /dev/null

$(SRC_DIR)pyplugcc-c-tree.cc \
$(SRC_DIR)pyplugcc-pyplugcc-c-tree.h \
$(SRC_DIR)pyplugcc-pyplugcc-c-tree-mdef.h: \
   $(SRC_DIR)gen/c-tree.cfg $(SRC_DIR)gen/h2pyfun.py \
   $(wildcard $(SRC_DIR)gen/c-tree.d/*.cc)
	$(GEN_MSG) $(PYTHON) $(SRC_DIR)gen/h2pyfun.py \
          -c $(SRC_DIR)gen/c-tree.cfg \
          --header $(GCCPLUGINS_DIR)/include/c-tree.h \
          > /dev/null

$(SRC_DIR)pyplugcc-cp-tree.cc \
$(SRC_DIR)pyplugcc-pyplugcc-cp-tree.h \
$(SRC_DIR)pyplugcc-pyplugcc-cp-tree-mdef.h: \
   $(SRC_DIR)gen/cp-tree.cfg $(SRC_DIR)gen/h2pyfun.py \
   $(wildcard $(SRC_DIR)gen/cp-tree.d/*.cc)
	$(GEN_MSG) $(PYTHON) $(SRC_DIR)gen/h2pyfun.py \
          -c $(SRC_DIR)gen/cp-tree.cfg \
          --header $(GCCPLUGINS_DIR)/include/cp/cp-tree.h \
          > /dev/null

clean::
	$(RM) $(PLUGIN_LIB_PATH)
	$(RM) $(PLUGIN_SOURCE_FILES:.cc=.o)
	$(RM) $(SRC_DIR)*~
	$(RM) -r $(SRC_DIR)gen/__pycache__/

distclean: clean
	$(RM) $(PLUGIN_GENERATED_SOURCE_FILES:.cc=.h)
	$(RM) $(PLUGIN_GENERATED_SOURCE_FILES:.cc=-mdef.h)
	$(RM) $(PLUGIN_GENERATED_SOURCE_FILES)
