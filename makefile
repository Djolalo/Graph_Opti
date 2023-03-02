# @authors: Djilali BAHOUS, Matthieu VAYSSE
# @version: 1.0.0

# config
CC := gcc
SRC_DIR := src
BUILD_DIR := build

# SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
# LISTE_SRCS = $(filter $(SRC_DIR)/liste%, $(SRCS))
# FILE_SRCS = $(filter $(SRC_DIR)/file.c, $(SRCS))

# define the C source files
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# define the C object files 
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(BUILD_DIR)/main
	@echo "✅ Build complete 🥳"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c clean create-build-dir
	@$(CC) -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	@$(CC) -c $< -o $@

create-build-dir:
	@mkdir build
	@echo "✅ Created build directory"

clean:
	@rm -rf $(BUILD_DIR)
	@echo "✅ Cleaned build and output directories 🗑️"

run:
	@echo "🚀 executing main programm"
	@./build/main