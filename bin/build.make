#
# Autoconfig makefile
# Copyright by Piotr Styczyński (2017)
# MIT License
#

include ./bin/config.make

ifeq (,$(filter clean distclean help build watch all run-test rebuildauto $(CUSTOM_COMMANDS),$(MAKECMDGOALS)))
ifneq (,$(MAKECMDGOALS))
$(info <error>Unknown build command was used: $(MAKECMDGOALS)</error>)
$(error )
endif
endif

ECHO := @
CC_SEL:=

include ./bin/targets/*
