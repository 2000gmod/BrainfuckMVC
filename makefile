CC = gcc

CFLAGS = -Wall

TARGET = bfmvc

compile:
	$(CC) $(CFLAGS) -o $(TARGET) src/*.c

clean:
	rm $(TARGET)