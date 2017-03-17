FORCE:
	@true;

%: CALL
	@true;

CALL:
	@bash ./bin/build.sh $(MAKECMDGOALS)

.PHONY: default

default:
	@bash ./bin/build.sh help
