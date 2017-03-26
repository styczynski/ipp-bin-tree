#
# General purpose awesome makefile
# This is wrapper for build.sh script
# Usage: type 'make help' to see help.
#
#
# @Piotr Styczyński 2017
#
include build.config

ifeq (,$(DEFAULT_TARGET))
DEFAULT_BEHAVIOUR=help
endif

#
# Override default behaviour
#
default:
	@bash ./bin/shell/build.sh $(DEFAULT_TARGET)
	@exit 0

FORCE:
	@true;

ifneq (,$(MAKECMDGOALS))
%: CALL
	@true;
endif

CALL:
	@bash ./bin/shell/build.sh $(MAKECMDGOALS)

.PHONY: default
