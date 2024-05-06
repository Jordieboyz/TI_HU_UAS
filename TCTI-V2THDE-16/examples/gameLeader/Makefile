#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################


INCLUDE_PATH := ../../include/
SEARCH_PATH := ../../src/

SOURCES := $(shell find $(SEARCH_PATH) -type f -name "*.cpp")
HEADERS := $(shell find $(INCLUDE_PATH) -type f -name "*.hpp")

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../../
include $(RELATIVE)/Makefile.due
