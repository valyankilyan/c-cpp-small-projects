CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = main.o

all: polynom clean

polynom: $(MODULES)
	$(CC) $(MODULES) -o polynom

clean:
	rm -f $(MODULES)