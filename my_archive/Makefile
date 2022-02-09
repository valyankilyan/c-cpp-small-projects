CC = gcc
FLAGS = -Wextra -Wall -std=c11 -g -c
DIR = src
MODULES = tree.o queue.o archivator.o main.o

all: archive clean

archive: $(MODULES)
	gcc $(MODULES) -o archive

main.o: queue.o tree.o
	$(CC) $(FLAGS) $(DIR)/main.c

archivator.o: queue.o tree.o
	$(CC) $(FLAGS) $(DIR)/archivator.c

queue.o: tree.o
	$(CC) $(FLAGS) $(DIR)/queue.c

tree.o:
	$(CC) $(FLAGS) $(DIR)/tree.c

clean:
	rm -f $(MODULES)