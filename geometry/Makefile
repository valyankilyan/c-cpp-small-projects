CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = point.o main.o

all: geometry clean

geometry: $(MODULES)
	$(CC) $(MODULES) -o geometry

main.o: point.o
	$(CC) $(FLAGS) $(DIR)/main.cpp

point.o:
	$(CC) $(FLAGS) $(DIR)/point.cpp

clean:
	rm -f $(MODULES)