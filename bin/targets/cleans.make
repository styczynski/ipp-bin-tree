
clean: clean-temp
	$(info <b>Project cleaned. Done</b>)

distclean: clean-all
	$(info <b>Project cleaned. Done</b>)

clean-temp: clean-obj

clean-all: clean-dist


clean-obj:
	$(info <debug>Cleaning build</debug>)
	$(ECHO)rm -f $(SOURCES_BUILT_FILES)

clean-dist:
	$(info <debug>Cleaning dist</debug>)
	$(ECHO)rm -f -d -r $(TEMP_DIR)
	$(ECHO)rm -f -d -r $(DIST_DIR)
