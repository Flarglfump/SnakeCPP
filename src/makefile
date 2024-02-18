
CC = g++

ifdef OS
FLAGS = -std=c++20 -DNCURSES_STATIC
OBJS = main.cpp -lncurses ScreenBuffer.cpp -lncurses Snake.cpp -lncurses 
else
OBJS = main.cpp ScreenBuffer.cpp Snake.cpp
FLAGS = -std=c++20 -lcurses	
endif

all:
	$(CC) $(FLAGS) $(OBJS) -o Snake
Snake:
	$(CC) $(FLAGS) $(OBJS) -o Snake

run: Snake
	./Snake
clean:
	rm -f Snake; rm -rf Snake.dSYM