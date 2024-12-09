# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -I../include -Wall

# Source files
SRC = main.c bmerge.c bsort.c sequence.c

# Object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Target executable name
TARGET = bitonic_sort

# Default target to build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Declare targets that are not associated with files
.PHONY: all clean