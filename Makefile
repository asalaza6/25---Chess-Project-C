# Makefile: Makefile for Team Lockdown
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g
DESIGN = Main

# Default target
all: Main

######################### Generate object files #######################
# Target for Chess.o
Chess.o: Chess.c Chess.h
	gcc -c Chess.c -o Chess.o $(FLAGS)
# Target for main.o
main.o: Chess.h main.c
	gcc -c main.c -o main.o $(FLAGS)

######################### Generate the executable #####################
# Target for Main
Main: Chess.o main.o
	gcc  main.c Chess.o -o Main $(FLAGS)

###############################  others  ##############################
# Target for clean
clean:
	rm -f *.o $(DESIGN)

   

