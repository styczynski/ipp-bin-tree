
SOURCES_FILES := $(wildcard $(SRC_DIR)/*.c)
SOURCES_FILES_LIST := $(addprefix ,$(notdir $(SOURCES_FILES:.c=)))
SOURCES_OBJ_FILES := $(addprefix $(TEMP_DIR)/,$(notdir $(SOURCES_FILES:.c=$(OBJ))))
SOURCES_EXE_FILES := $(DIST_DIR)/$(TARGET_NAME)$(EXE)
SOURCES_BUILT_FILES := $(addprefix $(TEMP_DIR)/,$(notdir $(wildcard $(TEMP_DIR)/*)))
DIST_BUILT_FILES := $(wildcard $(DIST_DIR)/*)
SOURCES_NUMBER := $(words $(SOURCES_FILES))
SOURCES_MADE_NUMBER := %
