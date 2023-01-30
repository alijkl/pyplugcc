SRC_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

HOST_GCC ?= g++
TARGET_GCC ?= gcc
PYTHON ?= python3
PYTHON_VERSION= $(shell $(PYTHON) -c \
  "import sys; print('.'.join(sys.version.partition(' ')[0].rsplit('.')[0:-1]))")
PYTHON_CONFIG ?= python$(PYTHON_VERSION)-config

PLUGIN_SOURCE_FILES := \
                       $(SRC_DIR)logging.cc \
                       $(SRC_DIR)pyplugcc.cc \
                       $(SRC_DIR)pyplugcc-mgcc.cc \
                       $(SRC_DIR)pyplugcc-mgcc-tree.cc \
                       $(SRC_DIR)pyplugcc-mgcc-tree-code.cc \
                       $(SRC_DIR)node-accessors.cc \
                       $(SRC_DIR)pyplugcc-mgcc-mnode.cc \


GCCPLUGINS_DIR:= $(shell $(TARGET_GCC) -print-file-name=plugin)
GCC_MAJOR := $(shell \
               $(HOST_GCC) --version | head -n1 | cut -d' ' -f3 | cut -d'.' -f1)
ifeq ($(shell test $(GCC_MAJOR) -gt 9; echo $$?),0)
  GCC_STD ?= -std=c++20
endif
ifneq ($(filter $(GCC_MAJOR),8 9),)
  GCC_STD ?= -std=c++2a
endif
GCC_OPT ?=
GCC_OPT_FLAGS+=$(GCC_STD) $(GCC_OPT)
CXXFLAGS+= -fPIC -fno-rtti -O2 -Wall $(GCC_OPT_FLAGS)

CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include
PYTHON_INCLUDE = $(shell $(PYTHON_CONFIG) --includes)
LD_FLAGS+= $(shell $(PYTHON_CONFIG) --ldflags)
LD_FLAGS+= -lpython$(PYTHON_VERSION)

PLUGIN_LIB_PATH=$(SRC_DIR)pyplugcc$(GCC_MAJOR).so
PLUGIN_NAME=$(shell basename $(PLUGIN_LIB_PATH) .so)

$(PLUGIN_LIB_PATH): $(PLUGIN_SOURCE_FILES)
	$(HOST_GCC) -shared $(CXXFLAGS) $(PYTHON_INCLUDE) $(LD_FLAGS) $^ -o $@

$(SRC_DIR)node-accessors.cc $(SRC_DIR)node-accessors.h: \
  $(SRC_DIR)gen/node-accessors.cf $(SRC_DIR)gen/accessor2fun.py \
  $(wildcard $(SRC_DIR)gen/node-accessors.d/*.cc)
	$(PYTHON) $(SRC_DIR)gen/accessor2fun.py

clean::
	$(RM) $(PLUGIN_LIB_PATH)
	$(RM) $(SRC_DIR)*.o $(SRC_DIR)*~
	$(RM) -r $(SRC_DIR)gen/__pycache__/

distclean: clean
	$(RM) $(SRC_DIR)node-accessors*.{cc,h}
