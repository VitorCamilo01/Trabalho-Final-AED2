# TrabalhoFinalAED2 Makefile

CC = gcc
CFLAGS = -Wall -O2
DEBUGFLAGS = -g -Wall

SRC = main.c Arvore.c Leitura.c Vetor.c
OBJ = $(SRC:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug:
	$(CC) $(DEBUGFLAGS) -o $(TARGET)-debug $(SRC)

clean:
	del /Q *.o *.exe $(TARGET) $(TARGET)-debug

.PHONY: all clean debug
