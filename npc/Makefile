FLAG=-Wall --trace --exe --build --cc
CPP_SOURCE=$(wildcard ./csrc/*.cpp)
V_SOURCE=$(wildcard ./vsrc/*.v)

BINARY_FILE=$(shell find obj_dir -type f -executable)
VCD_FILE=$(wildcard *.vcd)

all:
	@echo "sim start"
	@verilator --cc $(V_SOURCE)
	@verilator $(FLAG) $(V_SOURCE) $(CPP_SOURCE)

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@./$(BINARY_FILE)
	@gtkwave ./$(VCD_FILE)
	
clean:
	@rm -rf obj_dir
	
include ../Makefile