
include ./build.config

PRM_FLAG_INPUT_SYM=%
PRM_FLAG_OUTPUT_SYM=-

CC_ := $(CC)
CC := $(ECHO)$(CC_) $(CC_FLAGS)
CC_LINK := $(ECHO)$(CC_) $(CC_LINKER_FLAGS) $(LIBS)

SOURCES_FILES := $(wildcard $(SRC_DIR)/*.c)
SOURCES_FILES_LIST := $(addprefix ,$(notdir $(SOURCES_FILES:.c=)))
SOURCES_OBJ_FILES := $(addprefix $(TEMP_DIR)/,$(notdir $(SOURCES_FILES:.c=$(OBJ))))
SOURCES_EXE_FILES := $(DIST_DIR)/target$(EXE)
SOURCES_BUILT_FILES := $(addprefix $(TEMP_DIR)/,$(notdir $(wildcard $(TEMP_DIR)/*)))
DIST_BUILT_FILES := $(wildcard $(DIST_DIR)/*)
SOURCES_NUMBER := $(words $(SOURCES_FILES))
SOURCES_MADE_NUMBER := %

ifneq (,$(filter distclean,$(MAKECMDGOALS)))
ifeq (,$(SOURCES_BUILT_FILES)$(DIST_BUILT_FILES))
$(info <error>Directory is clean</error>)
$(error )
endif
endif

ifneq (,$(filter clean,$(MAKECMDGOALS)))
ifeq (,$(SOURCES_BUILT_FILES))
$(info <error>Directory is clean</error>)
$(error )
endif
endif

REBUILD_AUTO_MODE=false
ifneq (,$(filter rebuildauto,$(MAKECMDGOALS)))
REBUILD_AUTO_MODE=true
endif
