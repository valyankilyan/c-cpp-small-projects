CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = point.o line.o closedline.o polygon.o main.o

all: geometry clean

geometry: $(MODULES)
	$(CC) $(MODULES) -o geometry

main.o: point.o
	$(CC) $(FLAGS) $(DIR)/main.cpp

point.o:
	$(CC) $(FLAGS) $(DIR)/point.cpp

line.o:
		$(CC) $(FLAGS) $(DIR)/line.cpp

closedline.o:
		$(CC) $(FLAGS) $(DIR)/closedline.cpp

polygon.o:
		$(CC) $(FLAGS) $(DIR)/polygon.cpp

clean:
	rm -f $(MODULES)