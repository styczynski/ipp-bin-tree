#
# Building commands
#
# @Piotr Styczyński 2017
#

REBUILD_AUTO_MODE=false
ifneq (,$(filter rebuildauto,$(MAKECMDGOALS)))
REBUILD_AUTO_MODE=true
endif

rebuild: clean-all $(TEMP_DIR) $(DIST_DIR)

build: $(TEMP_DIR) $(DIST_DIR) sources

all: $(TEMP_DIR) $(DIST_DIR) sources

rebuildauto: sources_noecho $(TEMP_DIR)/autotest.cache
	@true

sources_base: $(TEMP_DIR) $(DIST_DIR) $(SOURCES_OBJ_FILES) $(SOURCES_EXE_FILES)
	@true

sources: $(TEMP_DIR) $(DIST_DIR) $(SOURCES_OBJ_FILES) $(SOURCES_EXE_FILES)
	$(info <b>Sources build. Done</b>)

sources_noecho: sources_base
	@true

$(TEMP_DIR)/%$(OBJ): $(SRC_DIR)/%.c
	$(info <debug>Compiling file $< </debug>)
	$(CC) $@ $<

$(DIST_DIR)/$(TARGET_NAME)$(EXE): $(SOURCES_OBJ_FILES)
	$(CC_LINK) $@ $^
