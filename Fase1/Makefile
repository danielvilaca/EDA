CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJ = antena.o matriz.o main.o
TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
