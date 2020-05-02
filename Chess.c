#include "Chess.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "Game.h"
#include "list.h"

// local function declaration
void moveDiagonal(MOVE* moveObject,int x, int y);
// Returns 1 if empty, 2 if enemy piece is present and 0 if occupied by own piece
int check(MOVE* myObject, BOARD* boardObject)
{
    //Check emptiness
    if(!(boardObject-> array[myObject->dest])){
      return 1;
    }
    //check Opponent.
    if(myObject -> piece -> color != boardObject->array[ myObject -> dest]-> color ){
      return 2;
    } 	
	return 0;

}
// pawn = 10
// horse, bishop = 30
// castle = 50
// queen = 90
// king = 900

NODE* possibleMoves(BOARD* myB, int source){
    NODE* head = NULL;
    MOVE* tempMv = (MOVE*) malloc(sizeof(MOVE));
	tempMv->piece =  myB -> array[source];
    for(int i = 0 ; i < 64 ; i++){
        tempMv->from = source;
        tempMv->dest = i;
            if(isLegal(tempMv, myB)){
				if(head == NULL){
					head = (NODE *) malloc(sizeof(NODE));
					assert(head);
					head->p_from = source;
					head->p_dest = i;
					printf("Creating Head\n");
				}
				else{
					PushBack(head, source, i);
					printf("Pushing into List\n");
				}
        }
        
    }
    free(tempMv);
    return head;
}

// void allPossibleMove(BOARD* myB, NODE* possibleArray){
//     int counter = 0;
//     // Wtf do i need to do? -> need to check all spots. 
//     for(int i = 0; i< 64 ;i++){
//         if(myB -> array[i]){ 
//             //if there's a piece at that location
//             possibleArray[counter++] = possibleMoves(myB, i);
//         }
//     }
// }
// void printPossibleMoves(int *possibleMovesArray){
//     int i = 0; // counter
//     while(possibleMovesArray[i] != -1 && i <28){
//         char* temp; 
//         temp = int2char(possibleMovesArray[i]);
//         printf("%s, ", temp );
//         free(temp);
//     }
// }



int neighbor(MOVE* myObject, BOARD* boardObject)
{
  char* current_CHAR = int2char(myObject->from);
  int result = 0;
	current_CHAR[0] += 1 ;
  PIECE *Ptemp = boardObject-> array[char2int(current_CHAR)];
  if((Ptemp -> color != myObject-> piece-> color)&& (Ptemp -> type == myObject-> piece-> type))
  {
    result = 2;
  }
  current_CHAR[0] -= 2 ;//to go to left 
  
	Ptemp = boardObject-> array[char2int(current_CHAR)];
  if((Ptemp -> color != myObject-> piece-> color)&& (Ptemp -> type == myObject-> piece-> type)){
    if(result ==2){
      result =3;
    }
    else{
      result = 1;
    }
  }
  return result;
    // Color , wether that 's a pawn'
    // No Left OR Right Opp -> return 0
    // Left -> 1
    // Right -> 2
    // Both possible -> 3
}

//this just checks if an enemy piece exists at that location with specific type
int checkSpace(int color, char type, int position, BOARD* boardObject){
	if(position < 0 || position > 63){
		return 0;
	}
	if (boardObject->array[position]!= 0){ 
		if ( boardObject->array[position] -> color == color && boardObject->array[position] -> type == type)
		{
		//result = result + 1;
		return 1;
		}
  	}
	return 0;
}

/* Returns a 1 if black king is in check, return a 2 if white king is in check, returns a 0 if no check */
int checkKing(BOARD* boardObject)
{
  //int result;
  char* blackKING;
  char* whiteKING;
  int position = 0;
 
  //int orientation = 0;
  char whiteKnight[2];
  char blackKnight[2];
  char diagonal[2];
  char rookQueen[2];
  //Gets the position of the black king and white king
  for(int i = 0; i < 64; i++)
  {
    position = i;
    if (boardObject->array[position] != NULL)
    {
      if(boardObject->array[position]->type == 'K')
      {
        if (boardObject->array[position]->color == 0)
        {
          blackKING = int2char(position);
        }
      }
      if(boardObject->array[position]->color == 1 && boardObject->array[position]->type == 'K')
      {
        whiteKING = int2char(position);
      }
    }
  }
  //black player, checks if white knight has black king in check
  //Top L Right Check 
  whiteKnight[0] = blackKING[0] + 1;
  whiteKnight[1] = blackKING[1] + 2;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Top L Left Check
  whiteKnight[0] = blackKING[0] - 1;
  whiteKnight[1] = blackKING[1] + 2;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Top Right Gun
 
  whiteKnight[0] = blackKING[0] + 2;
  whiteKnight[1] = blackKING[1] + 1;
  position = char2int(whiteKnight);
  
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  //Top Left Gun
  whiteKnight[0] = blackKING[0] - 2;
  whiteKnight[1] = blackKING[1] + 1;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Bottom L Left Check
  whiteKnight[0] = blackKING[0] - 1;
  whiteKnight[1] = blackKING[1] - 2;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if (char2int(whiteKnight) <= 63 && char2int(whiteKnight) >= 0)
    {
      if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
      {
        //result = result + 1;
        return 1;
      }
    }
  }*/
  //Bottom L Right Check
  whiteKnight[0] = blackKING[0] + 1;
  whiteKnight[1] = blackKING[1] - 2;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
   if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Bottom Left Gun
  whiteKnight[0] = blackKING[0] - 2;
  whiteKnight[1] = blackKING[1] - 1;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(whiteKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Bottom Right Gun
  whiteKnight[0] = blackKING[0] + 2;
  whiteKnight[1] = blackKING[1] - 1;
  position = char2int(whiteKnight);
  //107 = 'k' in char
  if(checkSpace(1, 'k', position, boardObject)){
	  return 1;
  }
  /*
  if ( boardObject->array[char2int(whiteKnight)] -> color == 1 && boardObject->array[char2int(whiteKnight)] -> type == 'k')
  {
    //result = result + 1;
    return 1;
  }
	*/
  //white player, checks if black knight has white king in check
  //Top L Right Check 
  blackKnight[0] = whiteKING[0] + 1;
  blackKnight[1] = whiteKING[1] + 2;
  position = char2int(blackKnight);
  //107 = 'k' in char
  if(checkSpace(0, 107, position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  { 
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Top L Left Check
  blackKnight[0] = whiteKING[0] - 1;
  blackKnight[1] = whiteKING[1] + 2;
  position = char2int(blackKnight);
  //107 = 'k' in char
  if(checkSpace(0, 'k', position, boardObject)){
	  return 1;
  }
  //Top Right Gun
  blackKnight[0] = whiteKING[0] + 2;
  blackKnight[1] = whiteKING[1] + 1;
  position = char2int(blackKnight);
  //107 = 'k' in char
  if(checkSpace(0, 107, position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Top Left Gun
  blackKnight[0] = whiteKING[0] - 2;
  blackKnight[1] = whiteKING[1] + 1;
  position = char2int(blackKnight);
  //107 = 'k' in char
  if(checkSpace(0, 107, position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom L Left Check
  blackKnight[0] = whiteKING[0] - 1;
  blackKnight[1] = whiteKING[1] - 2;
  
  if(checkSpace(0, 107, char2int(blackKnight), boardObject)){
	  return 2;
  }
  /*if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom L Right Check
  blackKnight[0] = whiteKING[0] + 1;
  blackKnight[1] = whiteKING[1] - 2;
   if(checkSpace(0, 107, char2int(blackKnight), boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom Left Gun
  blackKnight[0] = whiteKING[0] - 2;
  blackKnight[1] = whiteKING[1] - 1;
   if(checkSpace(0, 107, char2int(blackKnight), boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom Right Gun
  blackKnight[0] = whiteKING[0] + 2;
  blackKnight[1] = whiteKING[1] - 1;
   if(checkSpace(0, 107, char2int(blackKnight), boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(blackKnight)] != NULL)
  {
    if (char2int(blackKnight) <= 63 && char2int(blackKnight) >= 0)
    {
      if ( boardObject->array[char2int(blackKnight)] -> color == 0 && boardObject->array[char2int(blackKnight)] -> type == 'k')
      {
        //result = result + 2;
        return 2;
      }
    }
  } */

  //black player, checks if white pawn or white queen or white bishop has king in check within one space
  //Top Right
  diagonal[0] = blackKING[0] + 1;
  diagonal[1] = blackKING[1] + 1;
  position = char2int(diagonal);
  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Top Left
  diagonal[0] = blackKING[0] - 1;
  diagonal[1] = blackKING[1] + 1;
  position = char2int(diagonal);
  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Bottom Right
  diagonal[0] = blackKING[0] + 1;
  diagonal[1] = blackKING[1] - 1;
  position = char2int(diagonal);
  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject) || checkSpace(1, 'P', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 1;
      return 1;
    }
  }*/
  //Bottom Left
  diagonal[0] = blackKING[0] - 1;
  diagonal[1] = blackKING[1] - 1;
  position = char2int(diagonal);
  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject) || checkSpace(1, 'P', position, boardObject)){
	  return 1;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 1;
      return 1;
    }
  }*/

  //white player, checks if black pawn or black queen or black bishop has king in check within one space
  //Top Right
  diagonal[0] = whiteKING[0] + 1;
  diagonal[1] = whiteKING[1] + 1;
  position = char2int(diagonal);
  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject) || checkSpace(0, 'P', position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Top Left
  diagonal[0] = whiteKING[0] - 1;
  diagonal[1] = whiteKING[1] + 1;
  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject) || checkSpace(0, 'P', position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom Right
  diagonal[0] = whiteKING[0] + 1;
  diagonal[1] = whiteKING[1] - 1;
  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //Bottom Left
  diagonal[0] = whiteKING[0] - 1;
  diagonal[1] = whiteKING[1] - 1;
  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  return 2;
  }
  /*
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'P') || (boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
    {
      //result = result + 2;
      return 2;
    }
  }*/
  //black player, checks if white bishop or queen has king in check in space > 1
  //Bottom Right
  diagonal[0] = blackKING[0];
  diagonal[1] = blackKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] + i;
      diagonal[1] = diagonal[1] - i;
	  position = char2int(diagonal);
	  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
	  /*
      if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Bottom Left
  diagonal[0] = blackKING[0];
  diagonal[1] = blackKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] - i;
      diagonal[1] = diagonal[1] - i;
	  position = char2int(diagonal);
	  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
		/*
      if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Top Right
  diagonal[0] = blackKING[0];
  diagonal[1] = blackKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] + i;
      diagonal[1] = diagonal[1] + i;
	  position = char2int(diagonal);
	  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
		/*
      if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Top Left
  diagonal[0] = blackKING[0];
  diagonal[1] = blackKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] - i;
      diagonal[1] = diagonal[1] + i;
	  position = char2int(diagonal);
	  if(checkSpace(1, 'B', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
	  /*
      if ( (boardObject->array[char2int(diagonal)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }

  //white player, checks if black bishop or queen has king in check in space > 1
  //Bottom Right
  diagonal[0] = whiteKING[0];
  diagonal[1] = whiteKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] + i;
      diagonal[1] = diagonal[1] - i;
	  position = char2int(diagonal);
	  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }
	  /*
      if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Bottom Left
  diagonal[0] = whiteKING[0];
  diagonal[1] = whiteKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] - i;
      diagonal[1] = diagonal[1] - i;
	  position = char2int(diagonal);
	  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }
		/*
      if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Top Right
  diagonal[0] = whiteKING[0];
  diagonal[1] = whiteKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] + i;
      diagonal[1] = diagonal[1] + i;
	  position = char2int(diagonal);
	  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }/*
      if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }
  //Top Left
  diagonal[0] = whiteKING[0];
  diagonal[1] = whiteKING[1];
  if (boardObject->array[char2int(diagonal)] != NULL)
  {
    for(int i = 1; i < 8; i++)
    {
      diagonal[0] = diagonal[0] - i;
      diagonal[1] = diagonal[1] + i;
	  position = char2int(diagonal);
	  if(checkSpace(0, 'B', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }/*
      if ( (boardObject->array[char2int(diagonal)] -> color == 0) && ((boardObject->array[char2int(diagonal)] -> type == 'B') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(diagonal)] != 0)
      {
        break;
      }
    }
  }

  //black player, checks if white queen or rook has black king in check from horizontal and vertical
  //Up
  rookQueen[0] = blackKING[0];
  rookQueen[1] = blackKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[1] = rookQueen[1] + k;
	  position = char2int(rookQueen);
	  if(checkSpace(1, 'R', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
	/*
      if ( (boardObject->array[char2int(rookQueen)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'R') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    }
  }
  //Down
  rookQueen[0] = blackKING[0];
  rookQueen[1] = blackKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[1] = rookQueen[1] - k;
	  position = char2int(rookQueen);
	  if(checkSpace(1, 'R', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }
		/*
      if ( (boardObject->array[char2int(rookQueen)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'R') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    } 
  }
  //Right
  rookQueen[0] = blackKING[0];
  rookQueen[1] = blackKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[0] = rookQueen[0] + k;
	  position = char2int(rookQueen);
	  if(checkSpace(1, 'R', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }/*
      if ( (boardObject->array[char2int(rookQueen)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'R') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    } 
  }
  //Left
  rookQueen[0] = blackKING[0];
  rookQueen[1] = blackKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[0] = rookQueen[0] - k;
	  position = char2int(rookQueen);
	  if(checkSpace(1, 'R', position, boardObject) || checkSpace(1, 'Q', position, boardObject)){
	  	return 1;
  	  }/*
      if ( (boardObject->array[char2int(rookQueen)] -> color == 1) && ((boardObject->array[char2int(diagonal)] -> type == 'R') || (boardObject->array[char2int(diagonal)] -> type == 'Q')))
      {
        //result = result + 1;
        return 1;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    }
  } 

   //white player, checks if black queen or rook has white king in check from horizontal and vertical
  //Up
  rookQueen[0] = whiteKING[0];
  rookQueen[1] = whiteKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[1] = rookQueen[1] + k;
	  position = char2int(rookQueen);
	  if(checkSpace(0, 'R', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }/*
      if (boardObject->array[char2int(rookQueen)] -> color == 0 && (boardObject->array[char2int(diagonal)] -> type == 'R' || boardObject->array[char2int(diagonal)] -> type == 'Q'))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    }
  }
  //Down
  rookQueen[0] = whiteKING[0];
  rookQueen[1] = whiteKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[1] = rookQueen[1] - k;
	  position = char2int(rookQueen);
	  if(checkSpace(0, 'R', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }/*
      if (boardObject->array[char2int(rookQueen)] -> color == 0 && (boardObject->array[char2int(diagonal)] -> type == 'R' || boardObject->array[char2int(diagonal)] -> type == 'Q'))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    } 
  }
  //Right
  rookQueen[0] = whiteKING[0];
  rookQueen[1] = whiteKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[0] = rookQueen[0] + k;
	  position = char2int(rookQueen);
	  if(checkSpace(0, 'R', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }
	  /*
      if (boardObject->array[char2int(rookQueen)] -> color == 0 && (boardObject->array[char2int(diagonal)] -> type == 'R' || boardObject->array[char2int(diagonal)] -> type == 'Q'))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    } 
  }
  //Left
  rookQueen[0] = whiteKING[0];
  rookQueen[1] = whiteKING[1];
  if (boardObject->array[char2int(rookQueen)] != NULL)
  {
    for(int k = 1; k < 8; k++)
    {
      rookQueen[0] = rookQueen[0] - k;
	  position = char2int(rookQueen);
	  if(checkSpace(0, 'R', position, boardObject) || checkSpace(0, 'Q', position, boardObject)){
	  	return 2;
  	  }/*
      if (boardObject->array[char2int(rookQueen)] -> color == 0 && (boardObject->array[char2int(diagonal)] -> type == 'R' || boardObject->array[char2int(diagonal)] -> type == 'Q'))
      {
        //result = result + 2;
        return 2;
        break;
      }*/
      if (boardObject->array[char2int(rookQueen)] != 0)
      {
        break;
      }
    } 
  }
  return 0;
  }
//Control Function/ Switch 
int isLegal(MOVE* moveObject, BOARD* boardObject)
{
	//for isLegal move there is special return numbers
	//for en passant result = 5
  int result= 0;
if(moveObject->piece){
switch(moveObject->piece->type)
  {
    case 'K':
      result = isLegalKing(moveObject,boardObject);
      break;
    case 'k':
      result = isLegalKnight(moveObject,boardObject);
      break;
    case 'P':
      result = isLegalPawn(moveObject,boardObject);
      break;
    case 'B': 
      result = isLegalBishop(moveObject,boardObject);
      break;
    case 'R':
      result = isLegalRook(moveObject,boardObject);
      break;
    case 'Q':
      result = isLegalQueen(moveObject,boardObject);
      break;
  }
}
  
  return result;
  //return 1;
}
      
//*****************
/*GAME* init_Game(){
    BOARD* myB = malloc(sizeof(BOARD));
    initializePieces(0, myB);
    initializePieces(1, myB);
    return myB;
}*/

void init_Queen(PIECE* myObject, int color){
  
  myObject->type = 'Q';
  myObject-> color = color;
   if(color){ //color is white
     myObject-> position = 59;
   }else{
     myObject->position = 3;
   } 
}
//***

void init_King(PIECE* myObject, int color){
  (myObject)->type = 'K';
  (myObject)->color = color;
  myObject->special = 0; //means the king has not moved
   if(color){ //color is white
     myObject->position = 60;
   }else{
     myObject->position = 4;
   } 
}
void init_Knight(PIECE* myObject, int color, int number){
  
  myObject->type = 'k';
  myObject->color = color;
   if(color){ //color is white
     switch(number){
       case 0:
        myObject->position = 57;
        break;
       case 1:
        myObject->position = 62;
        break;
     }
   }else{
     switch(number){
       case 0:
        myObject->position = 1;
        break;
       case 1:
        myObject->position = 6;
        break;
     }
   } 
}
void init_Pawn(PIECE* myObject, int color, int number)
{
  
 	 myObject-> type = 'P';
   myObject->color = color;
   if(color){ //color is white
     switch(number){
       case 0:
        myObject->position = 48;
        break;
       case 1:
        myObject->position = 49;
        break;
       case 2:
        myObject->position = 50;
        break;
       case 3:
        myObject->position = 51;
        break;
       case 4:
        myObject->position = 52;
        break;
       case 5:
        myObject->position = 53;
        break;
       case 6:
        myObject->position = 54;
        break;
       case 7:
        myObject->position = 55;
        break;
     }
   }else{
     switch(number){
       case 0:
        myObject->position = 8;
        break;
       case 1:
        myObject->position = 9;
        break;
       case 2:
        myObject->position = 10;
        break;
       case 3:
        myObject->position = 11;
        break;
       case 4:
        myObject->position = 12;
        break;
       case 5:
        myObject->position = 13;
        break;
       case 6:
        myObject->position = 14;
        break;
       case 7:
        myObject->position = 15;
        break;
     }
   } 
}

void init_Rook(PIECE* myObject, int color, int number)
{
  
  myObject-> type = 'R';
  myObject-> color = color;
  myObject-> special = 0; //setting special to 0 means that rook has not moved yet. 
   if(color){ //color is white
     switch(number){
       case 0:
        myObject->position = 56;
        break;
       case 1:
        myObject->position = 63;
        break;
     }
   }else{
     switch(number){
       case 0:
        myObject->position = 0;
        break;
       case 1:
        myObject->position = 7;
        break;
     }
   } 
} 

void init_Bishop(PIECE* myObject, int color, int number){
  
  myObject->type = 'B';
  myObject->color =  color;
   if(color){ //color is white
     switch(number){
       case 0:
        myObject->position = 58 ;
        break;
       case 1:
        myObject->position = 61 ;
        break;
     }
   }else{
     switch(number){
       case 0:
        myObject->position = 02 ;
        break;
       case 1:
        myObject->position = 05;
        break;
     }
   } 
} 
/**************************************************/
// return 1 is move is legal; return 0 otherwise
// send MOVE* as an argument 
int isLegalKnight(MOVE* moveObject, BOARD* boardObject){

	int is_legal=0;
	if(!check(moveObject, boardObject)) return 0;

	// convert int to char; char* received has 2 indexes;
	//current_CHAR[0] is from A to H; current_CHAR[1] is from 1 to 8
	
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
  //check that dest is different from source
  if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;

  
  // check to see that destination is not out of board
  if( next_CHAR[0]>72 || next_CHAR[0]<65 || next_CHAR[1]<49 || next_CHAR[1]>56) return 0;
	//check if the move is legal for knight in top L form
	if( (abs(next_CHAR[0] - current_CHAR[0]) == 1) && (abs(next_CHAR[1] - current_CHAR[1]) == 2) )
	{

		is_legal=1;
	}
  
  //check if the move is legal for knight in L gun form
  if( (abs(next_CHAR[0] - current_CHAR[0]) == 2) && (abs(next_CHAR[1] - current_CHAR[1]) == 1) )
  {
          

    is_legal=1;
  }
  return is_legal;
}
int isLegalKing(MOVE* moveObject, BOARD* boardObject){

	// return 0 if destination is not empty
	if(!check(moveObject, boardObject)) return 0;
  
	char* current_CHAR =  int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
  //check that dest is different from source
  if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;
  
  // check to see that destination is not out of board
  if( (next_CHAR[0]>72) || (next_CHAR[0]<65) || (next_CHAR[1]<49) || (next_CHAR[1]>56) ) return 0;
  
	//King moves one step in all directions
  if(abs(next_CHAR[0]-current_CHAR[0]) < 2 && abs(next_CHAR[1]-current_CHAR[1]) < 2){
	  if(moveObject->piece->special == 0){
		  //change in special variable denotes king has moved now.
		  moveObject->piece->special = 1; 
	  }
        return 1;
		//check if king has not moved and are requesting to move 2 spaces horizontally
  }else if(moveObject->piece->special == 0 && abs(next_CHAR[0]-current_CHAR[0]) == 2 && abs(next_CHAR[1]-current_CHAR[1]) == 0){
	  	char tempChar[2] = {current_CHAR[0],current_CHAR[1]};
		PIECE* tempPiece;
	  	int sign = next_CHAR[0]-current_CHAR[0] < 0?-1:1;
	  	printf("checking castle %d/n", sign);
    	do{
			tempChar[0] = tempChar[0] + sign;
			tempPiece = boardObject->array[char2int(tempChar)];
			//check if reach rook
			if(tempPiece && tempPiece->type == 82 && tempPiece->special == 0){
				printf("Detected Castle Move");
				//store rook that will be moved
				boardObject->lastMove->piece = tempPiece;
				//give location of rook will be 1 above the last
				boardObject->lastMove->from = char2int(tempChar);
				tempChar[0] = current_CHAR[0] + sign;
				boardObject->lastMove->dest = char2int(tempChar);
				return 6;
			}
		}while(tempPiece == 0);
		//Testing castle
		//G1 F3 B1 C3	B8 C6	E7 E6
		//H7 H6 H7 H6	A2 A3	A2 A3
		//G2 G3 D2 D3	B7 B6	F8 D6
		//H6 H5 H6 H5	A3 A4	A3 A4
		//F1 H3 C1 E3	C8 B7	E8 E7
		//H5 H4 H5 H4	A4 A5	A4 A5
		//E1 G1 D1 D2	D8 B8	G8 H6
		//		H4 H3			A5 A6
		//		E1 C1			D8 F8
		return 0;
  }    
  return 0;
}

// CheckEmptyOrOpponent
int isLegalBishop(MOVE*moveObject, BOARD* boardObject){


	//checks if your object is there
	if(!check(moveObject, boardObject)) return 0;
	
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
  
  //check that dest is different from source
  if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0; //works

  // ensure diagonal destination
  if( abs(next_CHAR[0]-current_CHAR[0])!=abs(next_CHAR[1]-current_CHAR[1])){ 
    //printf("Destination is not diagonal \n");
    return 0;} 

  int step = abs(next_CHAR[0] - current_CHAR[0]);
  //printf("step is %d\n",step);
  char bishop_CHAR[2];
  bishop_CHAR[0] = current_CHAR[0];
  bishop_CHAR[1] = current_CHAR[1];
  for(int i=1; i < step; i++)
  {
    //printf("i= %d\n",i);
    //printf("Current position is %s\n",bishop_CHAR);
    
    if ( (next_CHAR[0] - current_CHAR[0]) < 0 && (next_CHAR[1] - current_CHAR[1] > 0) )
    {
      bishop_CHAR[0] = bishop_CHAR[0] - 1;
      bishop_CHAR[1] = bishop_CHAR[1] + 1;
    }
    else if ( (next_CHAR[0] - current_CHAR[0]) < 0 && (next_CHAR[1] - current_CHAR[1] < 0) )
    {
      bishop_CHAR[0] = bishop_CHAR[0] - 1;
      bishop_CHAR[1] = bishop_CHAR[1] - 1;
    }
    else if ( (next_CHAR[0] - current_CHAR[0]) > 0 && (next_CHAR[1] - current_CHAR[1] > 0) )
    {
      bishop_CHAR[0] = bishop_CHAR[0] + 1;
      bishop_CHAR[1] = bishop_CHAR[1] + 1;
    }
    else if ( (next_CHAR[0] - current_CHAR[0]) > 0 && (next_CHAR[1] - current_CHAR[1] < 0) )
    {
      bishop_CHAR[0] = bishop_CHAR[0] + 1;
      bishop_CHAR[1] = bishop_CHAR[1] - 1;
      
    }
    //printf("New position is %s\n",bishop_CHAR);
    // check that the block is not occupied
    if ( boardObject -> array[char2int(bishop_CHAR)] != 0)
    {
      //printf("Position is occupied along the way. Break loop \n");
      return 0;
      break;
    }

  }
	
	return 1;	
    
}
int isLegalPawn(MOVE* moveObject, BOARD* boardObject){
  
	//special variable documentation
	//if special == 0, then the pawn has not moved
	//if special == 1, then the pawn has moved in the regular way
	//if special == 2, then the pawn has moved two spaces forward
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);

	//CHECK FAIL CASES
	//If destination has same color piece
	if(!check(moveObject, boardObject)) return 0;
	//check that dest is different from source
	if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;
	// check to see that destination is not out of board
	if( next_CHAR[0]>72 || next_CHAR[0]<65 || next_CHAR[1]<49 || next_CHAR[1]>56 ) return 0;  
	// check for the first move of PAWN; special =1 if PAWN has been moved 
	//CHECK FOR MOVING BACKWARDS IF SO NOT LEGAL;
	if((moveObject->piece->color == 1) == (next_CHAR[1] - current_CHAR[1] < 1)){
		return 0;
	}

	//CHECK FOR MOVING FORWARD TWO MOVES on first move
	if( (abs(next_CHAR[1] - current_CHAR[1]) == 2) && (next_CHAR[0] - current_CHAR[0] == 0) ){
		if(moveObject->piece->special){
			return 0;
		}//CHECK IF FIRST MOVE AND THE SPACE RIGHT IN FRONT IS EMPTY
		else if(!boardObject->array[moveObject->piece->color?(moveObject->from - 8):(moveObject->from + 8)])
		{
			moveObject->piece->special = 2;
			return 1;
		}
  	}
	//Checking attacking diagonal
	if( (abs(next_CHAR[0] - current_CHAR[0]) == 1) && (abs(next_CHAR[1] - current_CHAR[1]) == 1)){
		//check if enemy is there
		if(check(moveObject, boardObject) == 2){
			if(moveObject->piece->special == 0){
				moveObject->piece->special = 1;
			}
			return 1;
		//check for en passant
		}else if(check(moveObject, boardObject) == 1 && boardObject->lastMove->piece->type == 80 && boardObject->lastMove->piece->special == 2 &&
		int2char(boardObject->lastMove->dest)[1] == current_CHAR[1]){
			//return 5 for specifically en passant special move
			return 5;
		}
		//testing for en passant
		//D2 D4
		//B8 A6
		//D4 D5
		//C7 C5
		//D5 C6
	  }
	
	// check for diagonal kill, EN PASSANT
	/*if( (abs(next_CHAR[0] - current_CHAR[0]) == 1) && (abs(next_CHAR[1] - current_CHAR[1]) == 1) ){
     char enPassantCHAR[2];
     enPassantCHAR[0] = next_CHAR[0];
     enPassantCHAR[1] = next_CHAR[1] - 1;
		 if (moveObject->piece->special==1)
     {
       if (boardObject -> array[char2int(enPassantCHAR)] -> special == 1)
       {
       	if (neighbor(moveObject, boardObject) == 1 || neighbor(moveObject, boardObject) == 2 || neighbor(moveObject, boardObject) == 3)
       	{
		if(moveObject->piece->special == 0){moveObject->piece->special = 1;}
         return 1;
       	}
       }
     }
	}*/
	// check for regular move
	if( (abs(next_CHAR[1] - current_CHAR[1]) == 1) && (next_CHAR[0] - current_CHAR[0] == 0) ){ 
		if(moveObject->piece->special == 0){moveObject->piece->special = 1;}
		return 1;
	}
	return 0;
}
/* Returns a 1 if black king is in check, return a 2 if white king is in check, returns a 0 if no check */
int checkmateKing(BOARD* boardObject,PIECE* kingObject){
	int check = checkKing(boardObject);
	MOVE* move = (MOVE*)malloc(sizeof(MOVE));
	move->from = kingObject->position;
	move->piece = kingObject;
	printf("Check - %d\n",check);
	if(check == 1 && kingObject->color == 0){//black king is in check
		for(int i = 0; i < 64; i++){
			move->dest = i;

			if(isLegal(move, boardObject)){//check if king has a possible move
				free(move);
				return 1;
			}
		}
	}else if(check == 2 && kingObject->color == 1){
		for(int i = 0; i < 64; i++){
			move->dest = i;
			if(isLegal(move, boardObject)){//check if king has a possible move
				free(move);
				return 1;
			}
		}
	}
	free(move);
	return 0;
}
int isLegalRook (MOVE* moveObject, BOARD* boardObject) {
	
  if(!check(moveObject, boardObject)) return 0;
  //printf("Line 1383");
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
	int sign; //whether going up=-1 or down=+1, left=-1 or right=+1
	int direction; // whether horizontal=0 or vertical=1 
	char* temp_CHAR = current_CHAR;
	//vertical
	if(next_CHAR[1]!=current_CHAR[1] && next_CHAR[0]==current_CHAR[0]){
		sign = next_CHAR[1]-current_CHAR[1] > 0 ? 1:-1;
		direction = 1;
	}
	//horizontal
	else if(next_CHAR[0]!=current_CHAR[0] && next_CHAR[1]==current_CHAR[1]){
		sign = next_CHAR[0]-current_CHAR[0] > 0 ? 1:-1;
		direction = 0;
	}
	//move is not a straight line
	else{
		return 0; 
	}
	do{
			//move checking piece to next level
			if(direction){//vertical
				temp_CHAR[1] += sign;
			}else{//horizontal
				temp_CHAR[0] += sign;
			}
			//check if reached destination;
			if(temp_CHAR[0] == next_CHAR[0] && temp_CHAR[1]==next_CHAR[1]){
				//already checked if spaces in between are empty and that the destination is filled by a enemy or empty
				return 1;
			}
		//only continue searching if current square is not occupied and within board
		}while(!boardObject->array[char2int(temp_CHAR)] && char2int(temp_CHAR)>-1 && char2int(temp_CHAR)<64);
	return 0;
}


//Queen method that uses isLegalBishop and isLegalQueen
int isLegalQueen (MOVE* moveObject, BOARD* boardObject) {
  if (isLegalBishop(moveObject, boardObject) || isLegalRook(moveObject, boardObject)){
    return 1;
  }
  else 
  {
    return 0;
  }
}



/*
step = abs(next_CHAR[0] - current_CHAR[0]);
char bishopCHAR[2];
bishopCHAR[0] = current_CHAR[0];
bishopCHAR[1] = current_CHAR[1];

for(int i=1; i < step; i++)
{
  if ( (next_CHAR[0] - current_CHAR[0]) < 0 && (next_CHAR[1] - current_CHAR[1] > 0) )
  {
    bishop_CHAR[0] = bishop_CHAR[0] - i;
    bishop_CHAR[1] = bishop_CHAR[1] + i;
  }
  if ( (next_CHAR[0] - current_CHAR[0]) < 0 && (next_CHAR[1] - current_CHAR[1] < 0) )
  {
    bishop_CHAR[0] = bishop_CHAR[0] - i;
    bishop_CHAR[1] = bishop_CHAR[1] - i;
  }
  if ( (next_CHAR[0] - current_CHAR[0]) > 0 && (next_CHAR[1] - current_CHAR[1] > 0) )
  {
    bishop_CHAR[0] = bishop_CHAR[0] + i;
    bishop_CHAR[1] = bishop_CHAR[1] + i;
  }
  if ( (next_CHAR[0] - current_CHAR[0]) > 0 && (next_CHAR[1] - current_CHAR[1] < 0) )
  {
    bishop_CHAR[0] = bishop_CHAR[0] + i;
    bishop_CHAR[1] = bishop_CHAR[1] - i;
  }
  if ( boardObject -> array[char2int(bishop_CHAR)] == 0)
  {
    break;
  }
  if ( boardObject -> array[char2int(bishop_CHAR)] != 0)
  {
    return 0;
    break;
  }

}*/
