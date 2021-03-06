##############################################################################
# Copyright (c) 2000-2020 Ericsson Telecom AB
# All rights reserved. This program and the accompanying materials
# are made available under the terms of the Eclipse Public License v2.0
# which accompanies this distribution, and is available at
# https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
#
# Contributors:
#   Balasko, Jeno
#   Beres, Szabolcs
#   Raduly, Csaba
#   Szabados, Kristof
#   Szabo, Bence Janos
#
##############################################################################
TOPDIR := ../../../
include   $(TOPDIR)/Makefile.regression

MAKE_PROG := $(MAKE)

TTCN_FILE := structured.ttcn
CFG := structured.cfg

FILES := $(TTCN_FILE) $(CFG) 
RUNNABLE := $(TTCN_FILE:.ttcn=)

DIR_SINGLE := dir_single_mode
DIR_PARALLEL := dir_parallel_mode
GENERATED_DIRS := $(DIR_SINGLE) $(DIR_PARALLEL) 

COVERAGE_FLAG := 
ifeq ($(COVERAGE), yes)
  COVERAGE_FLAG += -C
endif

ifdef DYN
ifeq ($(PLATFORM), WIN32)
  export PATH:=$(PATH):$(TTCN3_DIR)/lib:$(ABS_SRC)/$(DIR_SINGLE):$(ABS_SRC)/$(DIR_PARALLEL):
else
  export LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):$(ABS_SRC)/$(DIR_SINGLE):$(ABS_SRC)/$(DIR_PARALLEL):
endif 
endif

# List of fake targets:
.PHONY: all clean run run_single run_parallel runall

all: $(GENERATED_DIRS)

$(DIR_SINGLE):
	mkdir $@
	cd $@ && for file in $(FILES); do ln -s ../$$file || exit; done
	cd $@ && $(TTCN3_DIR)/bin/ttcn3_makefilegen $(COVERAGE_FLAG) $(SPLIT_FLAG) $(RT2_FLAG) -s ./* && $(MAKE_PROG) 'CXXFLAGS=$(CXXFLAGS)' 'LDFLAGS=$(LDFLAGS)'
	
$(DIR_PARALLEL):
	mkdir $@
	cd $@ && for file in $(FILES); do ln -s ../$$file || exit; done
	cd $@ && $(TTCN3_DIR)/bin/ttcn3_makefilegen $(COVERAGE_FLAG) $(SPLIT_FLAG) $(RT2_FLAG) ./* && $(MAKE_PROG) 'CXXFLAGS=$(CXXFLAGS)' 'LDFLAGS=$(LDFLAGS)'

run: $(GENERATED_DIRS)
	cd $(DIR_SINGLE) && ./$(RUNNABLE) $(CFG) 
	cd $(DIR_PARALLEL) && $(TTCN3_DIR)/bin/ttcn3_start $(RUNNABLE) $(CFG) 

# To run all tests, possibly in parallel
run_single: $(DIR_SINGLE) 
	cd $(DIR_SINGLE) && ./$(RUNNABLE) $(CFG) 
run_parallel: $(DIR_PARALLEL) 
	cd $(DIR_PARALLEL) && $(TTCN3_DIR)/bin/ttcn3_start $(RUNNABLE) $(CFG) 
runall: run_single run_parallel 

clean distclean:
	rm -rf $(GENERATED_DIRS)


