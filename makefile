CC = gcc

SRC_DIR = src
BUILD_DIR = build

SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
LISTE_SRCS = $(filter $(SRC_DIR)/liste%, $(SRCS))
FILE_SRCS = $(filter $(SRC_DIR)/file.c, $(SRCS))

# Define the order in which source files should be compiled
ORDERED_SRCS = $(SRC_DIR)/MatAdj.c $(FILE_SRCS) $(LISTE_SRCS) $(filter-out $(FILE_SRCS) $(LISTE_SRCS), $(SRCS))

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(ORDERED_SRCS))

TARGET = my_program

$(TARGET): $(OBJS)
	$(CC) -o $@ $^

libs: $(OBJS)
	@echo "Libraries compiled !"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

$(BUILD_DIR)/MatAdj.o: $(SRC_DIR)/MatAdj.c $(SRC_DIR)/file.c
	$(CC) -c -o $@ $(SRC_DIR)/MatAdj.c

$(BUILD_DIR)/listeAdj%.o: $(SRC_DIR)/liste.c $(SRC_DIR)/file.c
	$(CC) -c -o $@ $(SRC_DIR)/liste.c $(BUILD_DIR)/MatAdj.o

clean:
	rm -rf $(OBJS)
