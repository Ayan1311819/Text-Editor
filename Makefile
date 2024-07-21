# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I/usr/local/include/SDL2
LIBS = -L/usr/local/lib -lSDL2
# Source file
SRC = txt.c
# Output binary
OUTPUT = txt
all: $(OUTPUT)
$(OUTPUT):	$(SRC)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC) $(LIBS)
clean:
	rm -f $(OUTPUT)
