# Variables
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra
LIBS = -lm
TARGET = mergesort
SRC = mergesort.c

# The default target (what happens when you just type 'make')
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# New Debug target: Adds the -g flag and optimization level 0
# -O0 ensures the compiler doesn't "rearrange" your code,
# making it easier to follow in GDB.
debug: CFLAGS += -g -O0
debug: $(TARGET)

# Clean target: Removes the compiled binary
clean:
	rm -f $(TARGET)

# Phony targets prevent 'make' from getting confused if you
# ever create a file named 'clean' or 'debug'.
.PHONY: all debug clean
