# Makefile: Makefile for Team Lockdown
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g
DESIGN = Main

# Default target
all: Main

######################### Generate object files ######################
#Target for Chess.o
Game.o: Game.c Game.h
	gcc -c Game.c -o Game.o $(FLAGS)
# Target for Chess.o
Chess.o: Chess.c Chess.h
	gcc -c Chess.c -o Chess.o $(FLAGS)
# Target for main.o
main.o: Chess.h main.c
	gcc -c main.c -o main.o $(FLAGS)

######################### Generate the executable #####################
# Target for Main
Main: Chess.o main.o Game.o
	gcc  main.c Chess.o Game.o -o Main $(FLAGS)

###############################  others  ##############################
# Target for clean
clean:
	rm -f *.o $(DESIGN)
tar:
	tar -czvf ../Chess_Alpha_src.tar.gz ../Chess_Alpha_src
   

