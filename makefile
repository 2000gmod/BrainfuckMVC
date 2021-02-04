CC = gcc

CFLAGS = -Wall

TARGET = bfmvmc

compile:
	$(CC) $(CFLAGS) -o $(TARGET) src/*.c

clean:
	rm $(TARGET)