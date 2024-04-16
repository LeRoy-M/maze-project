CC = gcc
SRC = main.c sdl.c raycaster.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -pedantic -std=gnu89
FSDLFLAGS =  `sdl2-config --libs --cflags`
LSDLFLAGS = -lSDL2 -lSDL2_image -lm -ldl
PROG_NAME = game

build : $(OBJ)
	$(CC) $(CFLAGS) $(FSDLFLAGS) $(OBJ) -g -o $(PROG_NAME) $(LSDLFLAGS)

clean :
	rm -f *.o game

run :
	./game

all :
	make clean && make build && make run
