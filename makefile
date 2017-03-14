FORCE:
	@bash ./bin/build.sh help

%:
	@bash ./bin/build.sh $*

.PHONY:
	@bash ./bin/build.sh help
