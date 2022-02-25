CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = polynom.o main.o

all: polynom clean

polynom: $(MODULES)
	$(CC) $(MODULES) -o polynom

main.o:
	$(CC) $(FLAGS) $(DIR)/main.cpp

polynom.o:
	$(CC) $(FLAGS) $(DIR)/polynom.cpp

clean:
	rm -f $(MODULES)