#include "Chess.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//local function declaration
void moveDiagonal(MOVE* moveObject,int x, int y);
// Returns 1 if empty, 2 if enemy piece and 0 if occupied by own piece
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
/*
int possibleMovesArray[28];
int* possibleMoves(MOVE *myM, BOARD* myB, int* myArray ){
    int j = 0; //Keeping count of number of possible moves
    //Initially setting all the values in the possibleMoves array to -1;
    for(int i = 0; i< 28; i++){
        possibleMovesArray[i] = -1;
    }
    //Feeding in the enire board into the islegalFunction
    for(int i = 0 ; i < 64 ; i++){
        myM-> dest = i;
        if(isLegal(myM, myB)){
          myArray[j++] = myM -> dest;  
        }else{
            continue;
        }
    }
}
void printPossibleMoves(int *possibleMovesArray){
    int i = 0; // counter
    while(possibleMovesArray[i] != -1 && i <28){
        char* temp; 
        temp = int2char(possibleMovesArray[i]);
        printf("%s, ", temp );
        free(temp);
    }
}
*/

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

//Control Function/ Switch 
int isLegal(MOVE* moveObject, BOARD* boardObject)
{
  int result;
  switch(moveObject-> piece->type)
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
  return result;
}
      
//*****************
GAME* init_Game(){
    BOARD* myB = malloc(sizeof(BOARD));
    initializePieces(0, myB);
    initializePieces(1, myB);
    return myB;
}

void init_Queen(PIECE* myObject, int color){
  
  myObject->type = 'Q';
  myObject-> color = color;
   if(color){ //color is white
     myObject-> position = 59;
   }else{
     myObject->position = 4;
   } 
}
//***

void init_King(PIECE* myObject, int color){
  (myObject)->type = 'K';
  (myObject)->color = color;
   if(color){ //color is white
     myObject->position = 60;
   }else{
     myObject->position = 3;
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
        return 1;
  }else{
        return 0;
  }
     
}





// Check Diagonal

// CheckEmpty

// CheckEmptyOrOpponent
int isLegalBishop(MOVE*moveObject, BOARD* boardObject){
  MOVE tempMove = (MOVE) {.from=moveObject->from,.dest = moveObject->dest,.piece = moveObject->piece};

	//checks if your object is there
	if(!check(moveObject, boardObject)) return 0;
	
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
  
  //check that dest is different from source
  if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;
	// check to see that destination is not out of board
	if( (next_CHAR[0]>72) || (next_CHAR[0]<65) || (next_CHAR[1]<49) || (next_CHAR[1]>56) ) return 0;  
  //Andy's effort
  if ( (next_CHAR[0] - current_CHAR[0] == 0) || (next_CHAR[1] - current_CHAR[1] == 0) )
  {
    return 0;
  }
  int step = abs(next_CHAR[0] - current_CHAR[0]);
  char bishop_CHAR[2];
  bishop_CHAR[0] = current_CHAR[0];
  bishop_CHAR[1] = current_CHAR[1];

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

  }
  /*
  //check diagonal move for bishop; horizontal step = vertical step
	if( abs(next_CHAR[0]-current_CHAR[0])!= abs(next_CHAR[1]-current_CHAR[1]) ) return 0;
	
  //check for no obstacle in the way
	char x = next_CHAR[0]-current_CHAR[0] > 0 ? 1:-1; //defines horizontal direction
  char y = next_CHAR[1]-current_CHAR[1] > 0 ? -1:1; //defines vertical direction
  //obstacle mechanism
  printf("total moves = %d",abs(next_CHAR[0]-current_CHAR[0]));
	for (int i=1; i<abs(next_CHAR[0]-current_CHAR[0]); i++){
    moveDiagonal(&tempMove,x,y); //move diagonally (tempMove.dest));
    if(check(&tempMove, boardObject)!=1){
      return 0;
    }
  }*/
	
	/*// top right move
		if((next_CHAR[0]>current_CHAR[0])&&(next_CHAR[1]>current_CHAR[1]){
			int x = char2int(current_CHAR[0]+i);
			int y = char2int(current_CHAR[1]+i);
			if ( board [x][y]!=null) return 0;
		}
		// bottom right move
		else if ((next_CHAR[0]>current_CHAR[0])&&(next_CHAR[1]<current_CHAR[1]){
			int x = char2int(current_CHAR[0]+i);
			int y = char2int(current_CHAR[1]-i);
			if ( board [x][y]!=null) return 0;
		}
		// top left move
		else if ((next_CHAR[0]<current_CHAR[0])&&(next_CHAR[1]>current_CHAR[1]){
			int x = char2int(current_CHAR[0]-i);
			int y = char2int(current_CHAR[1]+i);
			if ( board [x][y]!=null) return 0;
		}
		// bottom left move
		else if ((next_CHAR[0]<current_CHAR[0])&&(next_CHAR[1]<current_CHAR[1]){
			int x = char2int(current_CHAR[0]-i);
			int y = char2int(current_CHAR[1]-i);
			if ( board [x][y]!=null) return 0;
		}	*/
	
	return 1;	
    
}
//used for temporary variable to check diagonal 
void moveDiagonal(MOVE* moveObject,int x, int y){//x and y will tell you which direction
  moveObject->dest = moveObject->dest + 8*y + x;
}

int isLegalPawn(MOVE* moveObject, BOARD* boardObject){
  
  //If destination has same color piece
	if(!check(moveObject, boardObject)) return 0;
	
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
	
	//check that dest is different from source
	if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;
  
	// check to see that destination is not out of board
	if( next_CHAR[0]>72 || next_CHAR[0]<65 || next_CHAR[1]<49 || next_CHAR[1]>56 ) return 0;  
	
	// check for the first move of PAWN; special =1 if PAWN has been moved 
	 
	if( (abs(next_CHAR[1] - current_CHAR[1]) == 2) && (next_CHAR[0] - current_CHAR[0] == 0) )
  {		
    if(moveObject->piece->special==0)
    {
        moveObject->piece->special = 1;
      	return 1;
    }
  }
	//Pawn Capture Another Pawn
  if( (abs(next_CHAR[0] - current_CHAR[0]) == 1) && (abs(next_CHAR[1] - current_CHAR[1]) == 1) && (check(moveObject, boardObject) == 2 ) )
  {
    return 1;
  }
	
	// check for diagonal kill, EN PASSANT
	if( (abs(next_CHAR[0] - current_CHAR[0]) == 1) && (abs(next_CHAR[1] - current_CHAR[1]) == 1) ){
     char enPassantCHAR[2];
     enPassantCHAR[0] = next_CHAR[0];
     enPassantCHAR[1] = next_CHAR[1] - 1;
		 if (moveObject->piece->special==1)
     {
       if (boardObject -> array[char2int(enPassantCHAR)] -> special == 1)
       {
       	if (neighbor(moveObject, boardObject) == 1 || neighbor(moveObject, boardObject) == 2 || neighbor(moveObject, boardObject) == 3)
       	{
         return 1;
       	}
       }
     }
	}
	// check for regular move
	if( (abs(next_CHAR[1] - current_CHAR[1]) == 1) && (next_CHAR[0] - current_CHAR[0] == 0) ) return 1;
	
	return 0;
}
int isLegalRook (MOVE* moveObject, BOARD* boardObject) {
	
  if(!check(moveObject, boardObject)) return 0;
  
	char* current_CHAR = int2char(moveObject->from);
	char* next_CHAR = int2char(moveObject->dest);
	
	// check that dest is different from source 
	if((current_CHAR[0]==next_CHAR[0])&&(current_CHAR[1]==next_CHAR[1])) return 0;
  
	// check to see that destination is not out of board
//	if( next_CHAR[0]>72 || next_CHAR[0]<65 || next_CHAR[1]<49 || next_CHAR[1]>56) result = 0; 
	
	// check Rook's legal moves
	// vertical move
	if(current_CHAR[0]==next_CHAR[0]){
		int step1 = abs(next_CHAR[1]-current_CHAR[1]);
    char rookCHAR[2];
    rookCHAR[0] = current_CHAR[0];
    rookCHAR[1] = current_CHAR[1];
    printf("rookCHAR is %s\n", rookCHAR);
		for (int i=1; i<step1; i++ )
    {
      if ( (next_CHAR[1] - current_CHAR[1]) > 0)
      {
        rookCHAR[1] = rookCHAR[1] + i;
        printf("rookCHAR is %s\n", rookCHAR);
      }
      if ( (next_CHAR[1] - current_CHAR[1]) < 0)
      {
        rookCHAR[1] = rookCHAR[1] - i;
        printf("rookCHAR is %s\n", rookCHAR);
      }
			if( boardObject -> array[char2int(rookCHAR)] == 0)
      {
       
        break;
      }
      if ( boardObject -> array[char2int(rookCHAR)] != 0)
      {
        return 0;
        break;
      }
       
		}
	}
  // horizontal move
	if(current_CHAR[1]==next_CHAR[1])
  {
    int step2 = abs(next_CHAR[0] - current_CHAR[0]);
    char rookCHAR2[2];
    rookCHAR2[0] = current_CHAR[0];
    rookCHAR2[1] = current_CHAR[1];
    for (int j=1; j<step2; j++)
    {
      if ( (next_CHAR[0] - current_CHAR[0]) > 0)
      {
        rookCHAR2[0] = rookCHAR2[0] + j;
      }
      if ( (next_CHAR[0] - current_CHAR[0]) < 0)
      {
        rookCHAR2[0] = rookCHAR2[0] - j;
      }
      if( boardObject -> array[char2int(rookCHAR2)] == 0)
      {
        
        break;
      }
      else
      {
        return 0;
        break;
      }
    }
	} 
	return 1;
}

//collin im gonna comment this out for now so i can compile
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
