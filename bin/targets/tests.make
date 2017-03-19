TEST_OUT_DIR_T=$(TEST_OUT_DIR)
TEST_IN_DIR_T=$(TEST_IN_DIR)
TEST_IN_DIR=$(TEST_DIR)
TEST_OUT_DIR=$(TEST_DIR)
ifeq (,$(TEST_IN_DIR))
TEST_IN_DIR=$(TEST_IN_DIR_T)
endif
ifeq (,$(TEST_OUT_DIR))
TEST_OUT_DIR=$(TEST_OUT_DIR_T)
endif


ifneq (,$(filter rebuildauto,$(MAKECMDGOALS)))
ifeq (false,$(WATCH_WITH_TEST))
$(TEMP_DIR)/autotest.cache: $(DIST_DIR)/$(TARGET_NAME)$(EXE)
	@true
else
$(TEMP_DIR)/autotest.cache: $(DIST_DIR)/$(TARGET_NAME)$(EXE)
	$(ECHO)bash ./bin/shell/test.sh "$(DIST_DIR)/$(TARGET_NAME)$(EXE)" "$(TEST_IN_DIR)" --tgout "$(TEST_OUT_DIR)" --tm --terr "$(TEST_RESULTS_DIR)/err" --tout "$(TEST_RESULTS_DIR)/out" --tterm-format $(subst $(PRM_FLAG_INPUT_SYM),$(PRM_FLAG_OUTPUT_SYM),$(filter-out $@,$(MAKECMDGOALS)))
	$(ECHO)echo "UPDATED" > $(TEMP_DIR)/autotest.cache
	$(ECHO)touch $(TEMP_DIR)/autotest.cache
endif
else
$(TEMP_DIR)/autotest.cache: $(DIST_DIR)/$(TARGET_NAME)$(EXE)
	$(ECHO)bash ./bin/shell/test.sh "$(DIST_DIR)/$(TARGET_NAME)$(EXE)" "$(TEST_IN_DIR)" --tgout "$(TEST_OUT_DIR)" --tm --terr "$(TEST_RESULTS_DIR)/err" --tout "$(TEST_RESULTS_DIR)/out" --tterm-format $(subst $(PRM_FLAG_INPUT_SYM),$(PRM_FLAG_OUTPUT_SYM),$(filter-out $@,$(MAKECMDGOALS)))
	$(ECHO)echo "UPDATED" > $(TEMP_DIR)/autotest.cache
	$(ECHO)touch $(TEMP_DIR)/autotest.cache
endif

ifeq (filein,$(SUPPORT_TESTS))
test: all
	$(ECHO)bash ./bin/shell/test.sh "$(DIST_DIR)/$(TARGET_NAME)$(EXE)" "$(TEST_IN_DIR)" --tgout "$(TEST_OUT_DIR)" --terr "$(TEST_RESULTS_DIR)/err" --tout "$(TEST_RESULTS_DIR)/out" --tterm-format $(subst $(PRM_FLAG_INPUT_SYM),$(PRM_FLAG_OUTPUT_SYM),$(filter-out $@,$(MAKECMDGOALS)))
else
ifeq (command,$(SUPPORT_TESTS))
test: all
	$(ECHO)$(TEST_COMMAND)
else
test:
	$(info <error>Testing is not supported by this project.</error>)
	$(error Testing is not supported by this project.)
endif
endif
