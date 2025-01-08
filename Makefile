##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makes files.
##

SRC = $(shell find src -name '*.c')


all:
	gcc -o my_top $(SRC) -std=c99 -lncurses

clean:
	rm -f my_top

fclean:
	make clean

re:
	make fclean
	make all
