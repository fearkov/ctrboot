include mk/toolchain.mk
include mk/program.mk

BUILD_DIR := build
PROGRAMS := boot9 boot11

.DELETE_ON_ERROR:
.PHONY: all check clean $(PROGRAMS) $(addprefix check-,$(PROGRAMS))

all: $(PROGRAMS)

check: $(addprefix check-,$(PROGRAMS))

clean:
	rm -rf $(BUILD_DIR)

include $(foreach p,$(PROGRAMS),$(p)/$(p).mk)
$(foreach p,$(PROGRAMS),$(eval $(call PROGRAM,$(p))))

# for the tools: make print-<variable> prints its value
print-%:
	@echo '$($*)'
