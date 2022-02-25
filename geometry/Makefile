CC = g++
FLAGS = -Wextra -Wall -g -c
DIR = src
MODULES = point.o segment.o line.o closedline.o polygon.o \
triangle.o trapezium.o main.o

all: geometry clean

geometry: $(MODULES)
	$(CC) $(MODULES) -o geometry

main.o:
	$(CC) $(FLAGS) $(DIR)/main.cpp

point.o:
	$(CC) $(FLAGS) $(DIR)/point.cpp

segment.o:
	$(CC) $(FLAGS) $(DIR)/segment.cpp

line.o:
		$(CC) $(FLAGS) $(DIR)/line.cpp

closedline.o:
		$(CC) $(FLAGS) $(DIR)/closedline.cpp

polygon.o:
		$(CC) $(FLAGS) $(DIR)/polygon.cpp

triangle.o:
		$(CC) $(FLAGS) $(DIR)/triangle.cpp

trapezium.o:
	$(CC) $(FLAGS) $(DIR)/trapezium.cpp

clean:
	rm -f $(MODULES)