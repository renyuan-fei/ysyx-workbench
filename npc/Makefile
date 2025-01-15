BUILD_DIR=build

# 编译选项
FLAG = -Wall --trace --exe --build --cc
CPP_SOURCE = $(wildcard ./csrc/*.cpp)
V_SOURCE = $(wildcard ./vsrc/*.v)

# 自动查找二进制文件和 VCD 文件
BINARY_FILE = $(shell find ./build/obj_dir -type f -executable | head -n 1)
VCD_FILE = $(wildcard ./build/*.vcd)

# 默认目标
all: build
	@echo "Building simulation..."
	@verilator --cc $(V_SOURCE)
	@verilator $(FLAG) $(V_SOURCE) $(CPP_SOURCE)

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
	@rm -rf build

# 引入父目录的规则
include ../Makefile