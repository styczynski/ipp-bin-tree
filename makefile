#
# Autoconfig makefile
# Copyright by Piotr Styczyński (2017)
# MIT License
#
# Use:
#  Create build.config file / file by default should look like this:
#
#  PROJECT_DESCR  := Some compilable project in C/C++
#  PEFFERED_CC  := GCPP
#  SUPPORT_GCC   := null
#  SUPPORT_GCPP  := -std=c++11 -O3 -w -I./include
#  SUPPORT_CLANG := null
#
# For null keys compiler is marked as non-supporting project builds.
# For the rest SUPPORT_* flags are applied to the compiler autoconfigured path
#
# If you want to manipulate specific compile functions you can decalre
# also:
#
# CC_SEL_GEN_O := $$(CC) -c -o $$@ $$<
# CC_SEL_GEN_EXE := $$(CC) -o $$@ $$<
#
# The make file creates _autoconf_.config file with the autoconfigured flags and compiler path
# If this config don't work dor you, just edit _autoconf_ file.
#
#

ECHO := @
CC_SEL:=

include bin/config.make

help:
	$(info )
	$(info )
	$(info $(PROJECT_DESCR))
	$(info )
	$(info Autoconf makefile by Piotr Styczynski <MIT>)
	$(info )
	$(info To compile all examples use 'make all' or 'make examples' command)
	$(info To get list of all available examples use 'make run-example' command)
	$(info To run the specified example use 'make run-example-NAME' e.g. 'make run-example-demo')
	$(info To clean project use 'make clean' command)
	$(info )
	$(info )
	$(info )
	$(info )

rebuild: clean-all

clean: clean-temp
	$(info Project cleaned. Done)

distclean: clean-all
	$(info Project cleaned. Done)

clean-temp: clean-obj

clean-all: clean-dist

all: sources

sources: $(SOURCES_OBJ_FILES) $(SOURCES_EXE_FILES)
	$(info Sources build. Done)

clean-obj:
	$(info Cleaning build)
	$(ECHO)rm -f $(SOURCES_BUILT_FILES)

clean-dist:
	$(info Cleaning dist)
	$(ECHO)rm -f $(SOURCES_BUILT_FILES)
	$(ECHO)rm -f $(DIST_BUILT_FILES)

./temp/%$(OBJ): ./src/%.c
	$(info Compiling file $<)
	$(CC) $@ $<

./dist/target$(EXE): $(SOURCES_OBJ_FILES)
	$(CC_LINK) $@ $^
