##############################################################################
# Copyright (c) 2000-2020 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#
# Contributors:
#   Szabo, Bence Janos
#
##############################################################################
TOPDIR := ..
include $(TOPDIR)/Makefile.regression

.SUFFIXES: .ttcn .hh
.PHONY: all clean dep run

TTCN3_LIB = ttcn3$(RT2_SUFFIX)-parallel$(DYNAMIC_SUFFIX)

TTCN3_MODULES = Hostid.ttcn

GENERATED_SOURCES = $(TTCN3_MODULES:.ttcn=.cc)
GENERATED_HEADERS = $(GENERATED_SOURCES:.cc=.hh)
ifdef CODE_SPLIT
GENERATED_SOURCES := $(foreach file, $(GENERATED_SOURCES:.cc=), $(addprefix $(file), .cc _seq.cc _set.cc  _seqof.cc _setof.cc _union.cc))
else ifdef SPLIT_TO_SLICES
POSTFIXES := $(foreach file, $(SPLIT_TO_SLICES), $(addsuffix $(file), _part_))
POSTFIXES := $(foreach file, $(POSTFIXES), $(addprefix $(file), .cc))
GENERATED_SOURCES2 := $(foreach file, $(GENERATED_SOURCES:.cc=), $(addprefix $(file), $(POSTFIXES)))
GENERATED_SOURCES += $(GENERATED_SOURCES2)
endif

USER_SOURCES =

OBJECTS = $(GENERATED_SOURCES:.cc=.o) $(USER_SOURCES:.cc=.o)

TARGET = Hostid$(EXESUFFIX)

CONFIG = config.cfg
ifeq ($(findstring SOLARIS, $(PLATFORM)), SOLARIS)
CONFIG = config_solaris.cfg
endif

all: $(TARGET)

$(TARGET): $(GENERATED_SOURCES) $(USER_SOURCES)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ -L$(TTCN3_DIR)/lib -l$(TTCN3_LIB) -L$(OPENSSL_DIR)/lib -lcrypto $($(PLATFORM)_LIBS)

$(GENERATED_SOURCES) $(GENERATED_HEADERS): compile
	@if [ ! -f $@ ]; then $(RM) compile; $(MAKE) compile; fi

compile: $(TTCN3_MODULES) $(ASN1_MODULES)
	$(filter-out -Nold -E, $(TTCN3_COMPILER)) $(COMPILER_FLAGS) $^ 
	touch compile
	
clean distclean:
	-rm -f $(TARGET) $(OBJECTS) $(GENERATED_HEADERS) \
	$(GENERATED_SOURCES) *.log Makefile.bak compile

dep: $(GENERATED_SOURCES)
	makedepend $(CPPFLAGS) $(GENERATED_SOURCES)

run: $(TARGET)
	$(TTCN3_DIR)/bin/ttcn3_start $^ $(CONFIG)


