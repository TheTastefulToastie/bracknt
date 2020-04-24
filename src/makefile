.PHONY: clean

CC     := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -O3
SRC    := bracknt.br
CSRC   := $(patsubst %.br, %.c, $(wildcard *.br))
TARGET := bracknt

all: $(CSRC)
	$(CC) $(CFLAGS) $(CSRC) -o $(TARGET)

%.c: %.br
	bracknt $< | clang-format > $@

clean:
	rm *.c
	rm -f $(TARGET)

test: all
	./$(TARGET) ../examples/C/example.c

valgrind: all
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TARGET) ../examples/C/example.c

install: all
	cp $(TARGET) /usr/bin
