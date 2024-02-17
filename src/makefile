OBJS = main.cpp ScreenBuffer.cpp Snake.cpp
FLAGS = -std=c++20 -lcurses
CC = g++

all:
	$(CC) $(OBJS) $(FLAGS) -o Snake
Snake:
	$(CC) $(OBJS) $(FLAGS) -o Snake

run: Snake
	./Snake

clean:
	rm -f Snake; rm -rf Snake.dSYM