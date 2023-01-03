HOST_GCC=g++
TARGET_GCC=gcc
PYTHON_VERSION= $(shell python3 -c \
  "import sys; print('.'.join(sys.version.partition(' ')[0].rsplit('.')[0:-1]))")
PYTHON_CONFIG ?= python$(PYTHON_VERSION)-config
PLUGIN_SOURCE_FILES= gcc-plugin-python.cc
GCCPLUGINS_DIR:= $(shell $(TARGET_GCC) -print-file-name=plugin)
CXXFLAGS+= -I$(GCCPLUGINS_DIR)/include -fPIC -fno-rtti -O2
PYTHON_INCLUDE = $(shell $(PYTHON_CONFIG) --includes)
plugin-python$(PYTHON_VERSION).so: $(PLUGIN_SOURCE_FILES)
	$(HOST_GCC) -shared $(PYTHON_INCLUDE) $(CXXFLAGS) $^ -o $@

clean::
	$(RM) plugin-python$(PYTHON_VERSION).so
	$(RM) *.o *~

