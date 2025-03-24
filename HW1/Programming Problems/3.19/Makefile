CC = gcc
CFLAGS = -Wall -Wextra
TARGET = time

v1:
	$(MAKE) $(TARGET) SRC=time_v1.c

v2:
	$(MAKE) $(TARGET) SRC=time_v2.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean
