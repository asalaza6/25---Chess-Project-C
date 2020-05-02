#ifndef GAME_H
#define GAME_H
#include "Chess.h"
/* This is the header file for Game.c */

void printASCII(PIECE* myP);

PIECES* initializePieces(int color, BOARD* gameBoard);

PIECE *getPiece(int pos, BOARD* gameBoard);

void printBoard(BOARD* myBoard);

PIECE* movePiece(MOVE* myObject, BOARD* myB);

char* int2char(int number);

int char2int(char* myChar);

void playMove(PIECES* player, BOARD* gameBoard);


#endif