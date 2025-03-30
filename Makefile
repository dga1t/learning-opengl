CC = g++
CFLAGS = -Wall -std=c++17 -Iinclude -Ilib
LDFLAGS = -lglfw -lGL -ldl

# add these to COMMON_SRC later on - src/common/shader.cpp
COMMON_SRC = src/common/glad.c src/common/utils.cpp src/common/shader.cpp
CHAPTER01_SRC = $(COMMON_SRC) src/chapter01/main.cpp
CHAPTER01_EX1_SRC = $(COMMON_SRC) src/chapter01/exercise1.cpp
CHAPTER01_EX2_SRC = $(COMMON_SRC) src/chapter01/exercise2.cpp
CHAPTER01_EX3_SRC = $(COMMON_SRC) src/chapter01/exercise3.cpp
CHAPTER02_SRC = $(COMMON_SRC) src/chapter02/main.cpp

BIN_DIR = bin

all: chapter01 chapter01-ex1 chapter01-ex2 chapter01-ex3 chapter02

$(BIN_DIR):
	mkdir -p $(BIN_DIR)  # Create bin directory if it doesn't exist

chapter01: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER01_SRC) -o $(BIN_DIR)/chapter01 $(LDFLAGS)
	
chapter01-ex1: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER01_EX1_SRC) -o $(BIN_DIR)/chapter01ex1 $(LDFLAGS)
	
chapter01-ex2: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER01_EX2_SRC) -o $(BIN_DIR)/chapter01ex2 $(LDFLAGS)
	
chapter01-ex3: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER01_EX3_SRC) -o $(BIN_DIR)/chapter01ex3 $(LDFLAGS)

chapter02: $(BIN_DIR)
	$(CC) $(CFLAGS) $(CHAPTER02_SRC) -o $(BIN_DIR)/chapter02 $(LDFLAGS)
	
clean:
	rm -rf $(BIN_DIR)  # Remove bin directory and all compiled files
