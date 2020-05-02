
#include "Game.h"
#include "Chess.h"
/*
void log(MOVE* myObject){
  FILE * fptr;
  int i,n;
  char str[14]= "XX,XX,K,0" ; // The log format: from , dest , type , color
  // 2 ,2 , 1, 1 -> 
  char fname[10]="log.txt";
  fptr = fopen (fname,"w"); 
 char* charPTR = int2char(myObject-> from);
 str[0]= charPTR[0];
 str[1]= charPTR[1];
 charPTR = int2char(myObject-> dest);
 str[3]= charPTR[0];
 str[4]= charPTR[1];
str[6] = myObject-> piece -> type;
free(charPTR);
str[8] = myObject-> piece -> color;
 fgets(str, sizeof str, stdin);
 fputs(str, fptr);
  fclose (fptr)
  }
*/

PIECE *getPiece(int pos, BOARD* gameBoard){
	return gameBoard->array[pos];
}

PIECE* movePiece(MOVE* myObject, BOARD* myB){
	PIECE* temp = NULL;
    //Returing the taken peiece if any, otherwise returns nullptr
    if(myB->array[myObject-> dest]){ // if there's a peice that will be taken
		/*myB -> array[myObject-> from] = NULL;
		PIECE* temp = myB->array[myObject-> dest]; // temporarily storing the value of the taken on
		myObject-> piece-> position = myObject-> dest;
		temp -> position = -1;
		*/
		//remove the current piece that is going to be taken
		free(myB->array[myObject-> dest]);
		//change destination of current piece from move
		myB->array[myObject->from] = NULL;		
		myB->array[myObject->dest] = myObject->piece;
    return temp;
    }
    else{
        myB-> array[myObject-> from] = NULL;
        myObject-> piece-> position = myObject-> dest;
        myB-> array[myObject->dest]= myObject-> piece ;
        return NULL;
    }
    return NULL;
    
}
    
    

void printASCII(PIECE* myP)
{
    char caseValue = myP->type;
    switch(caseValue)
    {
        case 'Q':
            (myP->color == 0)?printf("\u2655"):printf("\u265B");
            break;
        case 'K':
            (myP->color == 0)?printf("\u2654"):printf("\u265A");
            break;
        case 'P':
            (myP->color == 0)?printf("\u2659"):printf("\u265F");
            break;
        case 'k':
            (myP->color == 0)?printf("\u2658"):printf("\u265E");
            break;
        case 'R':
            (myP->color == 0)?printf("\u2656"):printf("\u265C");
            break;  
        case 'B':
            (myP->color == 0)?printf("\u2657"):printf("\u265D");
            break;
    }
}
void printBoard(BOARD* myBoard){
    int num = 8;
  for(int i =0; i < 64; i++){
    if((i)%8 == 0){
      printf("%d ",num);
            num--;
    }
    if(myBoard-> array[i]){
      printf("[");
      printASCII(myBoard-> array[i]);
      printf("]");
    }else{
      printf("[ ]");
    }
    if((i+1)%8 == 0){
      printf("\n");
    }
  }
  
  printf("  ");
  for(char i = 'A';i<'I'; i++){
      printf(" %c ", i);
  }
        printf("\n");
}
  
  
PIECES* initializePieces(int color, BOARD* gameBoard){
  
  // PIECES -> ALL PIECES
  PIECES* player= (PIECES*) malloc(sizeof(PIECES));
  player->color = color;
  player->King = (PIECE*) malloc(sizeof(PIECE));
  init_King(player->King, color);
  gameBoard->array[player->King->position] = player->King;

  
  player->Queen = (PIECE*) malloc(sizeof(PIECE));
  init_Queen(player->Queen, color);
  gameBoard->array[player->Queen->position] = player->Queen;
    
  player->Knight1 = (PIECE*) malloc(sizeof(PIECE));
  init_Knight(player->Knight1, color, 0);
  gameBoard->array[player->Knight1->position] = player->Knight1;
  
  player->Knight2 = (PIECE*) malloc(sizeof(PIECE));
  init_Knight(player->Knight2, color, 1);
  gameBoard->array[player->Knight2->position] = player->Knight2;
  
  player->Bishop1 = (PIECE*) malloc(sizeof(PIECE));
  init_Bishop(player->Bishop1, color, 0);
  gameBoard->array[player->Bishop1->position] = player->Bishop1;
  
  player->Bishop2 = (PIECE*) malloc(sizeof(PIECE));
  init_Bishop(player->Bishop2, color, 1);
  gameBoard->array[player->Bishop2->position] = player->Bishop2;
  
  player->Pawn1 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn1, color, 0);
  gameBoard->array[player->Pawn1->position] = player->Pawn1;
  
  player->Pawn2 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn2, color, 1);
  gameBoard->array[player->Pawn2->position] = player->Pawn2;
  
  player->Pawn3 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn3, color, 2);
  gameBoard->array[player->Pawn3->position] = player->Pawn3;
  
  player->Pawn4 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn4, color, 3);
  gameBoard->array[player->Pawn4->position] = player->Pawn4;
  
  player->Pawn5 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn5, color, 4);
  gameBoard->array[player->Pawn5->position] = player->Pawn5;
  
  player->Pawn6 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn6, color, 5);
  gameBoard->array[player->Pawn6->position] = player->Pawn6;
  
  player->Pawn7 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn7, color, 6);
  gameBoard->array[player->Pawn7->position] = player->Pawn7;
  
  player->Pawn8 = (PIECE*) malloc(sizeof(PIECE));
  init_Pawn(player->Pawn8, color, 7);
  gameBoard->array[player->Pawn8->position] = player->Pawn8;
  
  player->Rook1 = (PIECE*) malloc(sizeof(PIECE));
  init_Rook(player->Rook1, color, 0);
  gameBoard->array[player->Rook1->position] = player->Rook1;
  
  player->Rook2 = (PIECE*) malloc(sizeof(PIECE));
  init_Rook(player->Rook2, color, 1);
  gameBoard->array[player->Rook2->position] = player->Rook2;
  return player;
}

char* int2char(int number){
  char *cell = malloc(2*sizeof(char));
  cell[0] = number % 8 +65 ; //<---------
  cell[1] = 7 - number / 8 +49;
  return cell;
  /*
  char cell[2];
  cell[0] = number % 8 +65 ; //<---------
  cell[1] = 7 - number / 8 +49;
  return &cell;
  */
}

int char2int(char* myChar){
  int number = myChar[0]-65;
//   if(number >7 || number < 0) return -1;
  // printf("%c%c", myChar[0],myChar[1]);
  int number2 = 8- atoi(&myChar[1]);
  // printf("%d, %d",number,number2);
  return (number2)* 8 + number;
}
// //
// void loadMoves(char* moveList, BOARD* gameBoard){
// 	char temp[2];
// 	MOVE* playerMove;
// 	while(*moveList != 0){
// 		temp[0] = *moveList;
// 		moveList++;
// 		temp[1] = *moveList;
// 		moveList++;
		
// 		playerMove->from = char2int(temp);
// 		playerMove->piece = getPiece(playerMove->from,gameBoard);
		
// 		temp[0] = *moveList;
// 		moveList++;
// 		temp[1] = *moveList;
// 		moveList++;
// 		playerMove->dest = char2int(temp);
// 		movePiece(playerMove, gameBoard);
// 	}
// }

void playMove(PIECES* player, BOARD* gameBoard){
	MOVE* playerMove = (MOVE*) malloc(sizeof(MOVE));
	int tempInt;
	char from[2];
	char dest[2];
	 //pick a correct piece belonging to player
	do{
		//
		printf("\nWhich piece do you want to move?\n");
		scanf("%s", from);
		printf("TEST :: %s\n", from);
		playerMove->from = char2int(from);
		printf("TEST::char2int %d", char2int(from));
		//
		playerMove->piece = (getPiece(char2int(from),gameBoard));
		
		printf("Type = %c color = %d myColor = %d\n",playerMove->piece->type, playerMove->piece->color,player->color);
		tempInt = playerMove->piece->color != player->color;
		if(tempInt){
			printf("You chose an enemy piece!");
		}
	}while(tempInt);	 
	
	//move said piece
    do
    {
    	printf("Where do you want to move it?\n");
     	scanf("%s", dest);
		playerMove->dest = char2int(dest);
		tempInt = isLegal(playerMove,gameBoard);
		if(!tempInt){
			printf("Move not Legal! Try again!\n");
		//isLegal will return a 5 if en passant is detected
		}else if(tempInt == 5){
			//remove last moved piece which was the pawn that move 2 pieces up
			gameBoard->array[gameBoard->lastMove->dest] = NULL;
			free(gameBoard->lastMove->piece);
		}else if(tempInt == 6){//isLegal will return a 6 if a castle is detected
			movePiece(gameBoard->lastMove, gameBoard);
		}
    }while(!tempInt);
	movePiece(playerMove, gameBoard);

	//will keep track of last move specifically for an passant
	free(gameBoard->lastMove);
	gameBoard->lastMove = playerMove;
	printf("LastMove type is %c\n", gameBoard->lastMove->piece->type);

	//check for check king ? 
	printf("Is Check? %d\n",checkKing(gameBoard));
}