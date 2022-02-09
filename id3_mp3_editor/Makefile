CC = gcc
FLAGS = -Wextra -Wall -std=c11 -g -c
DIR = src
MODULES = Frame.o FLL.o ID3.o Shell.o main.o

all: id3_editor clean

id3_editor: $(MODULES)
	$(CC) $(MODULES) -o id3_editor

main.o:
	$(CC) $(FLAGS) $(DIR)/main.c

Shell.o:
	$(CC) $(FLAGS) $(DIR)/Shell.c

ID3.o: FLL.o
	$(CC) $(FLAGS) $(DIR)/ID3.c

FLL.o: Frame.o
	$(CC) $(FLAGS) $(DIR)/FLL.c

Frame.o:
	$(CC) $(FLAGS) $(DIR)/Frame.c

clean:
	rm -f $(MODULES)
