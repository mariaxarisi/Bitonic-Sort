CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
SRC = src/bsort.c src/bmerge.c src/sequence.c src/main.c
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
EXEC = bin/serialBitonic

all: $(EXEC)

$(EXEC): $(OBJ) | bin
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

bin obj:
	mkdir -p $@

clean:
	rm -rf obj bin

run: $(EXEC)
	./$(EXEC) $(Q)

.PHONY: all clean