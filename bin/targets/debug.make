#
# Debug symbols generating commands
#
# @Piotr Styczyński 2017
#


ifeq (false,$(REBUILD_AUTO_MODE))
ifeq (true,$(SUPPORT_DEBUG_SYM))
debug: $(TEMP_DIR) $(DIST_DIR) $(DIST_DIR)/$(TARGET_NAME)$(DBG) sources_noecho
	$(info <debug>Generated debug symbols.</debug>)

$(TEMP_DIR)/%$(DBG)$(OBJ): $(SRC_DIR)/%.c
	$(info <debug>Compiling file with debug symbols $@ </debug>)
	$(CC_DBG) $@ $<

$(DIST_DIR)/$(TARGET_NAME)$(DBG): $(SOURCES_OBJ_DBG_FILES)
	$(CC_DBG_LINK) $@ $^
else
debug:
	$(info <error>Debug symbol generation is not supported by this project.</error>)
	$(error Debug symbol generation is not supported by this project.)
endif
endif
