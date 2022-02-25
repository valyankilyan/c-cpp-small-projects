CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = base.o derived.o main.o

all: test clean

test: $(MODULES)
	$(CC) $(MODULES) -o test

main.o: 
	$(CC) $(FLAGS) $(DIR)/main.cpp

base.o:
	$(CC) $(FLAGS) $(DIR)/base.cpp

derived.o:
		$(CC) $(FLAGS) $(DIR)/derived.cpp

clean:
	rm -f $(MODULES)