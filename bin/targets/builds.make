
rebuild: clean-all

build: sources

all: sources

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

$(DIST_DIR)/target$(EXE): $(SOURCES_OBJ_FILES)
	$(CC_LINK) $@ $^
