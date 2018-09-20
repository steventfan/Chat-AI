$(shell mkdir -p bin)

CC = g++
CFLAGS = -Wall -Werror -Wextra -pedantic
EXEC = bin/chat
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(EXEC):$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

%.o:%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rfv bin
	rm -rfv $(EXEC) $(OBJECTS)