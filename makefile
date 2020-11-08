CC = g++
CFLAGS = -g -Wall -pthread
TARGET = tsnake.cpp snake.cpp terminal_control.cpp frame_buffer.cpp 



all: $(TARGET)
	$(CC) $(CFLAGS) $(TARGET) -o tsnake

