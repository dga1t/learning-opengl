CC = g++
CFLAGS = -Wall -std=c++17 -Iinclude -Ilib
LDFLAGS = -lglfw -lGL -ldl

# add these to COMMON_SRC later on - src/common/shader.cpp src/common/utils.cpp
COMMON_SRC = src/common/glad.c
CHAPTER01_SRC = $(COMMON_SRC) src/chapter01/main.cpp
# CHAPTER02_SRC = $(COMMON_SRC) src/chapter02/main.cpp

BIN_DIR = bin

# add chapter02, etc..
all: chapter01

$(BIN_DIR):
	mkdir -p $(BIN_DIR)  # Create bin directory if it doesn't exist

chapter01: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER01_SRC) -o $(BIN_DIR)/chapter01 $(LDFLAGS)

# chapter02: $(BIN_DIR)
# 	$(CC) $(CFLAGS) $(CHAPTER02_SRC) -o $(BIN_DIR)/chapter02 $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)  # Remove bin directory and all compiled files
