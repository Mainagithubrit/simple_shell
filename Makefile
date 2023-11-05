CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

SRC = builtin.c builtin2.c environ.c functions.c interact.c main.c print.c string.c string2.c strtok.c utils.c

TARGET = hsh

all: $(TARGET)

DEBUG_FLAGS = -g

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

debug: $(SRC)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(SRC) -o hsh_debug

clean:
	rm -f $(TARGET) hsh_debug

betty: $(SRC)
	betty $(SRC)
