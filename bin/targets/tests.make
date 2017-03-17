

$(TEMP_DIR)/autotest.cache: $(DIST_DIR)/target$(EXE)
	@bash ./bin/test.sh "$(DIST_DIR)/target$(EXE)" "$(TEST_DIR)" --tm --terr "$(TEST_RESULTS_DIR)/err" --tout "$(TEST_RESULTS_DIR)/out" --tterm-format $(subst $(PRM_FLAG_INPUT_SYM),$(PRM_FLAG_OUTPUT_SYM),$(filter-out $@,$(MAKECMDGOALS)))
	@echo "UPDATED" > $(TEMP_DIR)/autotest.cache
	@touch $(TEMP_DIR)/autotest.cache


ifeq (filein,$(SUPPORT_TESTS))
run-test:
	@bash ./bin/test.sh "$(DIST_DIR)/target$(EXE)" "$(TEST_DIR)"  --terr "$(TEST_RESULTS_DIR)/err" --tout "$(TEST_RESULTS_DIR)/out" --tterm-format $(subst $(PRM_FLAG_INPUT_SYM),$(PRM_FLAG_OUTPUT_SYM),$(filter-out $@,$(MAKECMDGOALS)))
else
ifeq (command,$(SUPPORT_TESTS))
run-test:
	@$(TEST_COMMAND)
else
run-test:
	$(info <error>Testing is not supported by this project.</error>)
	$(error Testing is not supported by this project.)
endif
endif
