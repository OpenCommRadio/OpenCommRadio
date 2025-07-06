EXEC_TARGETS  += $(BUILD_DIR)/k5prog
CLEAN_TARGETS += k5prog-clean

$(BUILD_DIR)/k5prog: platforms/uv-k5/k5prog/k5prog
	mkdir -p $(dir $@)
	make -C platforms/uv-k5/k5prog
	cp $< $@

k5prog-clean:
	make -C platforms/uv-k5/k5prog clean
