CC = gcc
FLAGS = -Wextra -Wall -std=c11 -g -c
DIR = src
MODULES = Field.o BMP.o BMP_converter.o main.o

all: game_of_life clean

game_of_life: $(MODULES)
	gcc $(MODULES) -o game_of_life

main.o: Field.o BMP.o BMP_converter.o
	$(CC) $(FLAGS) $(DIR)/main.c

Field.o: BMP.o
	$(CC) $(FLAGS) $(DIR)/Field.c

BMP.o: BMP_converter.o
	$(CC) $(FLAGS) $(DIR)/BMP.c

BMP_converter.o:
	$(CC) $(FLAGS) $(DIR)/BMP_converter.c


clean:
	rm -f $(MODULES)