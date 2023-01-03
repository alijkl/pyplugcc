SRC_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

HOST_GCC=g++
TARGET_GCC=gcc
PYTHON ?= python3
PYTHON_VERSION= $(shell $(PYTHON) -c \
  "import sys; print('.'.join(sys.version.partition(' ')[0].rsplit('.')[0:-1]))")
PYTHON_CONFIG ?= python$(PYTHON_VERSION)-config
PLUGIN_SOURCE_FILES= $(SRC_DIR)gcc-plugin-python.cc
GCCPLUGINS_DIR:= $(shell $(TARGET_GCC) -print-file-name=plugin)
CXXFLAGS+=  -fPIC -fno-rtti -O2 -Wall -Werror
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include
PYTHON_INCLUDE = $(shell $(PYTHON_CONFIG) --includes)
LD_FLAGS+= $(shell $(PYTHON_CONFIG) --ldflags)
LD_FLAGS+= -lpython$(PYTHON_VERSION)

$(SRC_DIR)pyplug$(PYTHON_VERSION).so: $(PLUGIN_SOURCE_FILES)
	$(HOST_GCC) -shared $(CXXFLAGS) $(PYTHON_INCLUDE) $(LD_FLAGS) $^ -o $@

clean::
	$(RM) $(SRC_DIR)pyplug$(PYTHON_VERSION).so
	$(RM) $(SRC_DIR)*.o $(SRC_DIR)*~

