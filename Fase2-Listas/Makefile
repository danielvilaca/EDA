CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c11 -O2

SRC     := $(wildcard *.c)
OBJ     := $(SRC:.c=.o)
BIN     := teste2

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c *.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
