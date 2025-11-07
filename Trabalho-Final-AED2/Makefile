all: main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SOURCES = main.c Arvore.c Vetor.c Leitura.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main-debug: $(SOURCES)
	$(CC) $(CFLAGS) -g -O0 $(SOURCES) -o main-debug

clean:
	rm -f $(OBJECTS) $(TARGET) main-debug

.PHONY: all clean
