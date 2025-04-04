#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := UART/UART.cc ringbuff.c esp8266-driver/esp8266.cc

# header files in this project
HEADERS := esp8266-driver/esp8266.h 

# other places to look for files for this project
SEARCH  := ../src

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
