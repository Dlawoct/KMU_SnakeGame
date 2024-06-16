HEADERS = Constant.h Snake.h Color.h SnakeGame.h
SOURCES = main.cpp SnakeGame.cpp Snake.cpp
CC = g++
CFLAGS = -std=c++11
LDFLAGS =
EXECUTABLE = snake
LIBS = -lncurses
RM = rm -rf

all: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS) $(LIBS)

clean:
	$(RM) *.o $(EXECUTABLE)
