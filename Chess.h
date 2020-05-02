
#ifndef CHESS_H
#define CHESS_H
/* This is the Header file for Chess.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "list.h"

// struct declarations
typedef struct piece{
    int color; 
    int position; 
    char type; // 'Q' // ALREADY EXISTS
    int special;
} PIECE;

typedef struct pieces{
    int inRange; 
    int outRange;
    int color; // 0 White, 1 Black
    PIECE* King;
    PIECE* Queen;
    PIECE* Knight1;
    PIECE* Knight2;
    PIECE* Bishop1;
    PIECE* Bishop2;
    PIECE* Rook1;
    PIECE* Rook2;
    PIECE* Pawn1;
    PIECE* Pawn2;
    PIECE* Pawn3;
    PIECE* Pawn4;
    PIECE* Pawn5;
    PIECE* Pawn6;
    PIECE* Pawn7;
    PIECE* Pawn8;
} PIECES;

typedef struct move{
  int from; //initial position
  int dest; //destination position
  PIECE* piece; //piece that is moved
} MOVE;
// board is a one dimensional array of size 64
typedef struct Board{
    PIECE* array[64];
	MOVE* lastMove;
}BOARD;

typedef struct game{
  	BOARD* chessBoard;
  	PIECES* player1;
  	PIECES* player2;
    FILE* f;
    //TIME* ***********
  	MOVE* lastMove;
} GAME; 


//Function declarations
char* int2char(int number);
int char2int(char* myChar);
void printBoard();
int isLegal(MOVE* moveObject, BOARD* boardObject);
int neighbor(MOVE* myObject, BOARD* boardObject);
int checkKing(BOARD* boardObject);
PIECES* initializePieces(int color, BOARD* gameBoard);
void init_Queen(PIECE* myObject, int color);
void init_King(PIECE* myObject, int color);
void init_Pawn(PIECE* myObject, int color, int number);
void init_Rook(PIECE* myObject, int color, int number);
void init_Bishop(PIECE* myObject, int color, int number);
void init_Knight(PIECE* myObject, int color, int number);
GAME* init_Game();
char* int2char(int number);
int char2int(char* myChar);
int isLegalKing(MOVE* moveObject, BOARD* boardObject);
int isLegalQueen(MOVE* moveObject, BOARD* boardObject);
int isLegalKnight(MOVE* moveObject, BOARD* boardObject);
int isLegalBishop(MOVE*moveObject, BOARD* boardObject);
int isLegalPawn(MOVE* moveObject, BOARD* boardObject);
int isLegalRook (MOVE* moveObject, BOARD* boardObject);
int check(MOVE* myObject, BOARD* boardObject);
NODE* possibleMoves(BOARD* myB, int source);

#endif