CC = gcc
CFLAGS = -Wall -Wextra
TARGET = file_copy
SRC = file_copy.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean
