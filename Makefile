CC = mpicc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/bitonic_sort

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXECUTABLE)
	mpirun -np $$(echo $$((2**$(P)))) $(EXECUTABLE) $(Q)

.PHONY: all clean