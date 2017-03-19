#
# Autoconfig makefile
# Copyright by Piotr Styczyński (2017)
# MIT License
#

ECHO := @

include ./bin/default.config
include ./build.config
include ./bin/paths.make

ifeq (true,$(DEBUG))
ECHO=(echo __DEBUG_NOTIFICATOR__ > /dev/null) &
endif

PRM_FLAG_INPUT_SYM=%
PRM_FLAG_OUTPUT_SYM=-

CC_ := $(CC)
CC := $(ECHO)$(CC_) $(CC_FLAGS)
CC_LINK := $(ECHO)$(CC_) $(CC_LINKER_FLAGS) $(LIBS)
CC_SEL:=

ifeq (,$(filter clean distclean help build watch all test rebuildauto run $(CUSTOM_COMMANDS),$(MAKECMDGOALS)))
ifneq (,$(MAKECMDGOALS))
$(info <error>Unknown build command was used: $(MAKECMDGOALS)</error>)
$(error )
endif
endif

include ./bin/targets/*
