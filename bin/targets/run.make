
ifneq (,$(ON_RUN))
run:
	@$(ON_RUN)
else
run:
	$(info <b>Running application</b>)
	$(info <debug>$(DIST_DIR)/$(TARGET_NAME)$(EXE)</debug>)
	$(info )
	@$(DIST_DIR)/$(TARGET_NAME)$(EXE)
endif
