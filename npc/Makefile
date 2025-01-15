.PHONY: default all clean run

TOPNAME = top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)

# 编译选项
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

# # 自动查找二进制文件和 VCD 文件
# BINARY_FILE = $(shell find obj_dir -type f -executable | head -n 1)
# VCD_FILE = $(wildcard *.vcd)

default: $(BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# CPP_SOURCE = $(wildcard ./csrc/*.cpp)
# V_SOURCE = $(wildcard ./vsrc/*.v)
# CPP_SOURCE += $(SRC_AUTO_BIND)

VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

# 默认目标
# all:
# 	@echo "Building simulation..."
# 	@$(VERILATOR) --cc $(V_SOURCE)
# 	@$(VERILATOR) $(FLAG) $(V_SOURCE) $(CPP_SOURCE)

all: default

run: $(BIN)
	@$^

# 仿真目标
sim: all
	@echo "Running simulation..."
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
ifeq ($(BINARY_FILE),)
	@echo "Error: No binary file found!" && exit 1
else
	@echo "Executing binary: $(BINARY_FILE)"
	@./$(BINARY_FILE)
endif
ifeq ($(VCD_FILE),)
	@echo "Warning: No VCD file found to open with GTKWave."
else
	@echo "Opening VCD file: $(VCD_FILE)"
	@gtkwave $(VCD_FILE)
endif

clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)

# 引入父目录的规则
include ../Makefile