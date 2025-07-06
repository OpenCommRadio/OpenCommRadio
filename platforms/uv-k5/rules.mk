#CC := arm-none-eabi-gcc

EXEC_TARGETS  += $(BUILD_DIR)/k5prog
CLEAN_TARGETS += k5prog-clean

K5PROG_DIR := platforms/uv-k5/k5prog

$(BUILD_DIR)/k5prog: $(K5PROG_DIR)/k5prog
	mkdir -p $(dir $@)
	$(call make_native,$(K5PROG_DIR),k5prog)
	cp $< $@

k5prog-clean:
	$(call make_native,$(K5PROG_DIR),clean)
