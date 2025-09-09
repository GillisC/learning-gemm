CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -O3 -march=native

SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/main

GEMM ?= naive

SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/matrix.cpp $(SRC_DIR)/$(GEMM)_gemm.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

all: $(BIN)
	@$(BIN)

naive:
	$(MAKE) GEMM=naive

blocked:
	$(MAKE) GEMM=blocked

avx:
	$(MAKE) GEMM=avx
	
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean

