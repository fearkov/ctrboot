# $(call PROGRAM,name) links name from its sources and, for the functions
# without source yet, the bytes of your image (see mk/link.awk). check-name
# compares the result with the image; the bytes name.unmatched lists (cmp -l
# output) may differ. A program can use another toolchain with name_ARMCC_DIR.
# Sources reach data in the image, or anywhere else, as DAT_<address>.
define PROGRAM
$(1)_ARMCC_DIR ?= $$(ARMCC_DIR)
$(1)_TOOLS = $$(WIBO) $$($(1)_ARMCC_DIR)/bin
$(1)_OUT := $$(BUILD_DIR)/$(1)
$(1)_IMAGE := $(1)/image/$(1).bin
$(1)_LISTS := $(1)/$(1).layout $(1)/$(1).functions
$(1)_PARTS := $$(shell sed -n 's/^\([a-z0-9_][a-z0-9_]*\) .*/\1/p' $(1)/$(1).layout)
$(1)_SRCS := $$(shell find $(1)/src -name '*.cpp' -o -name '*.s' 2>/dev/null)
$(1)_HEADERS := $$(shell find $(1)/include -name '*.h' 2>/dev/null)
$(1)_OBJS := $$(patsubst $(1)/%,$$($(1)_OUT)/%.o,$$(basename $$($(1)_SRCS)))

$(1): $$($(1)_OUT)/$(1).bin

$$($(1)_OUT)/src/%.o: $(1)/src/%.cpp
	@mkdir -p $$(@D)
	$$($(1)_TOOLS)/armcc.exe -c $$(ARMCC_FLAGS) $$($(1)_FLAGS) $$(if $$(wildcard $(1)/include),-I$(1)/include) -o $$@ $$<

$$($(1)_OUT)/src/%.o: $(1)/src/%.s
	@mkdir -p $$(@D)
	$$($(1)_TOOLS)/armasm.exe $$($(1)_ASFLAGS) -o $$@ $$<

$$($(1)_IMAGE):
	@echo "$$@ is missing: put your dumps in place first: tools/images.py, see BUILDING.md"; exit 1

$$($(1)_OUT)/gaps.o: $$($(1)_LISTS) $$($(1)_IMAGE) mk/link.awk
	@rm -rf $$($(1)_OUT)/gaps; mkdir -p $$($(1)_OUT)/gaps
	@awk -v out=gaps -f mk/link.awk $$($(1)_LISTS) | while read at offset size; do \
		tail -c +$$$$((offset + 1)) $$($(1)_IMAGE) | head -c $$$$size > $$($(1)_OUT)/gaps/$$$$at.bin; \
		printf '    AREA |gap.%s|, DATA, READONLY, ALIGN=0\n    INCBIN %s/gaps/%s.bin\n' $$$$at $$($(1)_OUT) $$$$at; \
	done > $$($(1)_OUT)/gaps.s; echo '    END' >> $$($(1)_OUT)/gaps.s
	$$($(1)_TOOLS)/armasm.exe -o $$@ $$($(1)_OUT)/gaps.s

# with a region for each section of RAM variables the sources define
$$($(1)_OUT)/$(1).scat: $$($(1)_LISTS) mk/link.awk $$($(1)_SRCS)
	@mkdir -p $$(@D)
	{ awk -v out=scatter -f mk/link.awk $$($(1)_LISTS); \
	awk -v out=sections -f mk/link.awk /dev/null $$($(1)_SRCS); } > $$@

# the functions without source, and every DAT_<address> the sources name
$$($(1)_OUT)/$(1).sym: $$($(1)_LISTS) mk/link.awk $$($(1)_SRCS) $$($(1)_HEADERS)
	@mkdir -p $$(@D)
	{ awk -v out=symdefs -f mk/link.awk $$($(1)_LISTS); \
	cat /dev/null $$($(1)_SRCS) $$($(1)_HEADERS) | grep -o 'DAT_[0-9A-F]\{8\}' | sort -u | sed 's/^DAT_\(.*\)/0x\1 D DAT_\1/'; } > $$@

$$($(1)_OUT)/$(1).axf: $$($(1)_OBJS) $$($(1)_OUT)/gaps.o $$($(1)_OUT)/$(1).scat $$($(1)_OUT)/$(1).sym
	$$($(1)_TOOLS)/armlink.exe --scatter=$$($(1)_OUT)/$(1).scat $$(ARMLINK_FLAGS) \
		--map --list=$$($(1)_OUT)/$(1).map -o $$@ $$($(1)_OBJS) $$($(1)_OUT)/gaps.o $$($(1)_OUT)/$(1).sym
	@awk -v out=placement -f mk/link.awk $$($(1)_LISTS) $$($(1)_OUT)/$(1).map > $$($(1)_OUT)/misplaced || \
		{ echo "$(1): functions that did not land at their address:"; cat $$($(1)_OUT)/misplaced; exit 1; }

$$($(1)_OUT)/$(1).bin: $$($(1)_OUT)/$(1).axf
	@rm -rf $$($(1)_OUT)/parts
	$$($(1)_TOOLS)/fromelf.exe --bin --output=$$($(1)_OUT)/parts $$<
	@# one load region with contents makes a file, more make a directory
	@if [ -d $$($(1)_OUT)/parts ]; then cat $$(addprefix $$($(1)_OUT)/parts/,$$($(1)_PARTS)); \
	else cat $$($(1)_OUT)/parts; fi > $$@
	@if [ -e $$($(1)_OUT)/parts/unplaced ]; then \
		echo "$(1): some sections are not in $(1).functions, so they were linked outside the image (see $$($(1)_OUT)/$(1).map)"; \
	fi

check-$(1): $$($(1)_OUT)/$(1).bin
	@cmp -l $$($(1)_IMAGE) $$< > $$($(1)_OUT)/differing 2> /dev/null; \
	if [ $$$$? -gt 1 ] || [ $$$$(wc -c < $$<) -ne $$$$(wc -c < $$($(1)_IMAGE)) ]; then \
		echo "$(1): the build is not the size of the image"; exit 1; \
	fi; \
	if [ -f $(1)/$(1).unmatched ]; then expected=$(1)/$(1).unmatched; else expected=/dev/null; fi; \
	if tr -s ' ' < $$($(1)_OUT)/differing | sed 's/^ //' | cmp -s - $$$$expected; then \
		echo "$(1): OK"; \
	else \
		echo "$(1): differs from the image at"; \
		awk -v out=where -f mk/link.awk $$($(1)_LISTS) $$($(1)_OUT)/differing; exit 1; \
	fi
endef
