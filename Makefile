# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I$(PWD)/include
LDFLAGS := -lglfw -lGL

# Directories
SRC_DIR := src
BIN_DIR := bin

# Common source files (TODO - include later on)
# COMMON_DIR := $(SRC_DIR)/common
# COMMON_OBJS := $(COMMON_DIR)/glad.o $(COMMON_DIR)/shader.o $(COMMON_DIR)/utils.o

# Default target
all: help

# Build a specific chapter and exercise
build: $(SRC_DIR)/common $(COMMON_OBJS)
	@echo "Building chapter $(CHAPTER), exercise $(EXERCISE)..."
	$(eval CHAPTER_SRC := $(wildcard $(SRC_DIR)/chapter$(CHAPTER)/*.cpp))
	$(eval TARGET := $(BIN_DIR)/chapter$(CHAPTER)/exercise$(EXERCISE))
	mkdir -p $(dir $(TARGET))
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/chapter$(CHAPTER)/exercise$(EXERCISE).cpp -o $@ $(LDFLAGS) $(SRC_DIR)/chapter$(CHAPTER)/exercise$(EXERCISE).o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_DIR)/chapter$(CHAPTER)/exercise$(EXERCISE).o $(COMMON_OBJS) -lGL -lglfw -ldl
	@echo "Built: $(TARGET)"
	
# Compile all exercises across all chapters
build_all:
	@find $(SRC_DIR) -type f -name '*.cpp' | while read file; do \
		chapter=$$(basename $$(dirname $$file)); \
		exercise=$$(basename $$file .cpp); \
		output_path="$(BIN_DIR)/$$chapter"; \
		echo "Building $$chapter/$$exercise..."; \
		mkdir -p $$output_path; \
		obj_file=$${file}.o; \
		$(CXX) $(CXXFLAGS) -c $$file -o $$obj_file; \
		$(CXX) $(CXXFLAGS) -o $$output_path/$$exercise $$obj_file -lGL -lglfw -ldl; \
	done

# Compile the common files once
# build_common:
# 	@echo "Compiling common objects..."
# 	$(CXX) $(CXXFLAGS) -c $(COMMON_DIR)/glad.c -o $(COMMON_DIR)/glad.o
# 	$(CXX) $(CXXFLAGS) -c $(COMMON_DIR)/shader.cpp -o $(COMMON_DIR)/shader.o
# 	$(CXX) $(CXXFLAGS) -c $(COMMON_DIR)/utils.cpp -o $(COMMON_DIR)/utils.o

# Generate compile_commands.json
compile_commands:
	@echo "Removing existing bin/chapter01 if it's a file..."
	rm -f $(BIN_DIR)/chapter01
	bear -- make build_all

# Clean up object files and binaries
clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/**/*.o $(COMMON_DIR)/*.o compile_commands.json

# Show help
help:
	@echo "Usage:"
	@echo "  make build CHAPTER=<n> EXERCISE=<name>  # Build specific exercise"
	@echo "  make clean                              # Clean all artifacts"
	@echo "  make compile_commands                   # Regenerate compile_commands.json"
	@echo ""
	@echo "Examples:"
	@echo "  make build CHAPTER=1 EXERCISE=main"
	@echo "  make build CHAPTER=2 EXERCISE=exercise2"

.PHONY: all build clean compile_commands help
