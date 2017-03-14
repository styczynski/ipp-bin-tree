#
# Autoconfig makefile
# Copyright by Piotr Styczyński (2017)
# MIT License
#

ECHO := @
CC_SEL:=

include ./bin/config.make

help:
	$(info )
	$(info )
	$(info <b>$(PROJECT_DESCR)</b>)
	$(info )
	$(info <b>Autoconf makefile by Piotr Styczynski <MIT></b>)
	$(info )
	$(info <warn>'make all'</warn> )
	$(info <warn>'make clean'</warn> )
	$(info )
	$(info )
	$(info )
	$(info )

rebuild: clean-all

clean: clean-temp
	$(info <b>Project cleaned. Done</b>)

distclean: clean-all
	$(info <b>Project cleaned. Done</b>)

clean-temp: clean-obj

clean-all: clean-dist

all: sources

sources: $(TEMP_DIR) $(DIST_DIR) $(SOURCES_OBJ_FILES) $(SOURCES_EXE_FILES)
	$(info <b>Sources build. Done</b>)

clean-obj:
	$(info <debug>Cleaning build</debug>)
	$(ECHO)rm -f $(SOURCES_BUILT_FILES)

clean-dist:
	$(info <debug>Cleaning dist</debug>)
	$(ECHO)rm -f -d -r $(TEMP_DIR)
	$(ECHO)rm -f -d -r $(DIST_DIR)

$(TEMP_DIR):
	@mkdir $(TEMP_DIR)

$(DIST_DIR):
	@mkdir $(DIST_DIR)

$(TEMP_DIR)/%$(OBJ): $(SRC_DIR)/%.c
	$(info <debug>Compiling file $< </debug>)
	$(CC) $@ $<

$(DIST_DIR)/target$(EXE): $(SOURCES_OBJ_FILES)
	$(CC_LINK) $@ $^
