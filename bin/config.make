
include ./bin/envir.config

CC_ := $(CC)
CC := $(ECHO)$(CC_) $(CC_FLAGS)
CC_LINK := $(ECHO)$(CC_) $(CC_LINKER_FLAGS) $(LIBS)

SOURCES_FILES := $(wildcard ./src/*.c)
SOURCES_FILES_LIST := $(addprefix ,$(notdir $(SOURCES_FILES:.c=)))
SOURCES_OBJ_FILES := $(addprefix ./temp/,$(notdir $(SOURCES_FILES:.c=$(OBJ))))
SOURCES_EXE_FILES := ./dist/target$(EXE)
SOURCES_BUILT_FILES := $(addprefix ./temp/,$(notdir $(wildcard ./temp/*)))
DIST_BUILT_FILES := $(wildcard ./dist/*)
SOURCES_NUMBER := $(words $(SOURCES_FILES))
SOURCES_MADE_NUMBER := %

ifneq (,$(filter distclean,$(MAKECMDGOALS)))
ifeq (,$(SOURCES_BUILT_FILES)$(DIST_BUILT_FILES))
$(error Directory is clean)
endif
endif

ifneq (,$(filter clean,$(MAKECMDGOALS)))
ifeq (,$(SOURCES_BUILT_FILES))
$(error Directory is clean)
endif
endif
