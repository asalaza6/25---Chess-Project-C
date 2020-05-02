/* fflush(stdin);  for flushing out stdin*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Chess.h"
#include "Game.h"


int main(){
  //game variables
  int playerColor;
  //menu
  printf("Choose a color(0 for black, 1 for white)\n");
  scanf("%d", &playerColor);
  printf("you chose %d\n",playerColor);
  //game initialization
  BOARD* gameBoard = (BOARD*) malloc(sizeof(BOARD));
  PIECES* playerPieces = initializePieces(playerColor,gameBoard);
  PIECES* computerPieces = initializePieces(!playerColor,gameBoard);
  //game loop
  
  while(1){
    //print board
    printBoard(gameBoard);
	//player 1's turn
	printf("Player 1! It's your turn!");
	playMove(playerPieces,gameBoard);
	printBoard(gameBoard);
	//player 2's turn
	printf("Player 2! It's your turn!");
	playMove(computerPieces,gameBoard);
    //AI STUFF
  }
  return 1;
}