#
# Display help
#
# @Piotr Styczyński 2017
#


HELP_ITEM_WATCH=warn
HELP_ITEM_TEST=warn
HELP_ITEM_DEBUG=warn

ifneq (true,$(SUPPORT_DEBUG_SYM))
	HELP_ITEM_DEBUG=debug
endif
ifneq (true,$(SUPPORT_WATCH))
	HELP_ITEM_WATCH=debug
endif
ifeq (,$(SUPPORT_TESTS))
	HELP_ITEM_TEST=debug
endif
ifeq (none,$(SUPPORT_TESTS))
	HELP_ITEM_TEST=debug
endif


help:
	$(info )
	$(info )
	$(info  <b>$(PROJECT_DESCR)</b>)
	$(info )
	$(info  <b>Autoconf makefile by Piotr Styczynski <MIT></b>)
	$(info )
	$(info |  <warn>'make all'</warn> - Alias for 'make build')
	$(info |  <warn>'make build'</warn> - Builds application )
	$(info |  <warn>'make rebuild'</warn> - Rebuilds application totally )
	$(info |  <warn>'make clean'</warn> - Cleans compilation cache )
	$(info |  <warn>'make distclean'</warn> - Cleans all directories - that is compilation cache and dist folder )
	$(info |  <warn>'make help'</warn> - Displays this help )
	$(info |  <$(HELP_ITEM_WATCH)>'make watch'</$(HELP_ITEM_WATCH)> - Starts smart autobuilds (only release code without debug) )
	$(info |  <$(HELP_ITEM_TEST)>'make test'</$(HELP_ITEM_TEST)> - Runs all available tests )
	$(info |  <warn>'make run'</warn> - Runs app )
	$(info |  <$(HELP_ITEM_DEBUG)>'make debug'</$(HELP_ITEM_DEBUG)> - Generate release and debug symbols )
	$(info )
	$(info )
