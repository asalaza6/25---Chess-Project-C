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

  NODE* head = malloc(sizeof(NODE));
  //game loop
  
  while(1){
    //print board
    printBoard(gameBoard);
	//player 1's turn
	printf("Player 1! It's your turn!");
	playMove(playerPieces,gameBoard);
	printBoard(gameBoard);
    head = possibleMoves(gameBoard,playerPieces->Queen->position) ;
    print_list(head);
	//player 2's turn
	printf("Player 2! It's your turn!");
	playMove(computerPieces,gameBoard);
    printf("Gets Here\n");
    head = possibleMoves(gameBoard, playerPieces->Queen->position) ;
    print_list(head);
    //AI STUFF
  }
  return 1;
}