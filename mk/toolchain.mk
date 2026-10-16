# The tools. Set them in mk/local.mk or on the command line, see BUILDING.md.
-include mk/local.mk

WIBO ?= wibo
ARMCC_DIR ?=

# for both ROMs, built for space; each ROM's .mk adds its CPU and Thumb
ARMCC_FLAGS ?= --cpp -O3 -Ospace --split_sections -Iinclude

# for every program
ARMLINK_FLAGS ?= --no_remove --no_scanlib --diag_suppress=L6305 --diag_error=L6314
