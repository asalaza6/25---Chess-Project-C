/* This is the Chess GUI File */
/* EECS 22L, Team17, Andy Tran */


#include <stdio.h>
#include <gtk/gtk.h>
#include "ChessGUI.h"
#include <string.h>



GtkWidget *window;
GtkWidget *fixed;
GtkWidget *chess_icon;
GtkWidget *table;


enum GRID Board[8][8];

void ResetBoard()
{
    Board[0][0] = WHITE;
	Board[1][0] = BLACK;
	Board[2][0] = WHITE;
	Board[3][0] = BLACK;
	Board[4][0] = WHITE;
	Board[5][0] = BLACK;
	Board[6][0] = WHITE;
	Board[7][0] = BLACK;
	Board[0][1] = BLACK;
    Board[1][1] = WHITE;
    Board[2][1] = BLACK;
	Board[3][1] = WHITE;
	Board[4][1] = BLACK;
	Board[5][1] = WHITE;
	Board[6][1] = BLACK;
	Board[7][1] = WHITE; 
	
	Board[0][2] = WHITE;
	Board[1][2] = BLACK;
	Board[2][2] = WHITE;
	Board[3][2] = BLACK;
	Board[4][2] = WHITE;
	Board[5][2] = BLACK;
	Board[6][2] = WHITE;
	Board[7][2] = BLACK;

	Board[0][3] = BLACK;
	Board[1][3] = WHITE;
	Board[2][3] = BLACK;
	Board[3][3] = WHITE;
	Board[4][3] = BLACK;
	Board[5][3] = WHITE;
	Board[6][3] = BLACK;
	Board[7][3] = WHITE;

	Board[0][4] = WHITE;
	Board[1][4] = BLACK;
	Board[2][4] = WHITE;
	Board[3][4] = BLACK;
	Board[4][4] = WHITE;
	Board[5][4] = BLACK;
	Board[6][4] = WHITE;
	Board[7][4] = BLACK;

	Board[0][5] = BLACK;
	Board[1][5] = WHITE;
	Board[2][5] = BLACK;
	Board[3][5] = WHITE;
	Board[4][5] = BLACK;
	Board[5][5] = WHITE;
	Board[6][5] = BLACK;
	Board[7][5] = WHITE;

    Board[0][7] = BLACK;
	Board[1][7] = WHITE;
	Board[2][7] = BLACK;
	Board[3][7] = WHITE;
	Board[4][7] = BLACK;
	Board[5][7] = WHITE;
	Board[6][7] = BLACK;
	Board[7][7] = WHITE;
	Board[0][6] = WHITE;
    Board[1][6] = BLACK;
    Board[2][6] = WHITE;
	Board[3][6] = BLACK;
	Board[4][6] = WHITE;
	Board[5][6] = BLACK;
	Board[6][6] = WHITE;
	Board[7][6] = BLACK; 
	
     
} 


void InitBoard()
{
    Board[0][0] = BLACK_ROOK;
	Board[1][0] = BLACK_KNIGHT;
	Board[2][0] = BLACK_BISHOP;
	Board[3][0] = BLACK_QUEEN;
	Board[4][0] = BLACK_KING;
	Board[5][0] = BLACK_BISHOP;
	Board[6][0] = BLACK_KNIGHT;
	Board[7][0] = BLACK_ROOK;
	Board[0][1] = BLACK_PAWN;
    Board[1][1] = BLACK_PAWN;
    Board[2][1] = BLACK_PAWN;
	Board[3][1] = BLACK_PAWN;
	Board[4][1] = BLACK_PAWN;
	Board[5][1] = BLACK_PAWN;
	Board[6][1] = BLACK_PAWN;
	Board[7][1] = BLACK_PAWN; 
	
	Board[0][2] = WHITE;
	Board[1][2] = BLACK;
	Board[2][2] = WHITE;
	Board[3][2] = BLACK;
	Board[4][2] = WHITE;
	Board[5][2] = BLACK;
	Board[6][2] = WHITE;
	Board[7][2] = BLACK;

	Board[0][3] = BLACK;
	Board[1][3] = WHITE;
	Board[2][3] = BLACK;
	Board[3][3] = WHITE;
	Board[4][3] = BLACK;
	Board[5][3] = WHITE;
	Board[6][3] = BLACK;
	Board[7][3] = WHITE;

	Board[0][4] = WHITE;
	Board[1][4] = BLACK;
	Board[2][4] = WHITE;
	Board[3][4] = BLACK;
	Board[4][4] = WHITE;
	Board[5][4] = BLACK;
	Board[6][4] = WHITE;
	Board[7][4] = BLACK;

	Board[0][5] = BLACK;
	Board[1][5] = WHITE;
	Board[2][5] = BLACK;
	Board[3][5] = WHITE;
	Board[4][5] = BLACK;
	Board[5][5] = WHITE;
	Board[6][5] = BLACK;
	Board[7][5] = WHITE;

    Board[0][7] = WHITE_ROOK;
	Board[1][7] = WHITE_KNIGHT;
	Board[2][7] = WHITE_BISHOP;
	Board[3][7] = WHITE_QUEEN;
	Board[4][7] = WHITE_KING;
	Board[5][7] = WHITE_BISHOP;
	Board[6][7] = WHITE_KNIGHT;
	Board[7][7] = WHITE_ROOK;
	Board[0][6] = WHITE_PAWN;
    Board[1][6] = WHITE_PAWN;
    Board[2][6] = WHITE_PAWN;
	Board[3][6] = WHITE_PAWN;
	Board[4][6] = WHITE_PAWN;
	Board[5][6] = WHITE_PAWN;
	Board[6][6] = WHITE_PAWN;
	Board[7][6] = WHITE_PAWN; 
	
	

}


void ReverseGridColor(int gridX, int gridY)
{
        if(Board[gridX][gridY] == BLACK)
        {
                Board[gridX][gridY] = WHITE;
        }
        else
        {
                Board[gridX][gridY] = BLACK;
        }
}

void MoveTheKing(int gridX, int gridY, int tempX, int tempY)
{
		int temp;
        ResetBoard();
		temp = Board[tempX][tempY];
		printf("temp is %d \n", temp);
		InitBoard();
		if (temp == 0)
		{
			Board[tempX][tempY] = BLACK;
		}
		else
		{
			Board[tempX][tempY] = WHITE;
		}
        Board[gridX][gridY] = WHITE_KING;
}

void DrawBoard()
{
        int i, j;

        for(i = 0; i < 8; i++)
        {
                for(j = 0; j < 8; j++)
                {
                        switch(Board[i][j])
                        {
                                case BLACK:
                                        chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_square.jpg");
                                        break;
                                case WHITE:
                                        chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_square.jpeg");
                                        break;
                                case WHITE_KING:
                                        chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_king.png");
                                        break;
								case WHITE_QUEEN:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_queen.png");
                                        break;
								case WHITE_KNIGHT:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_knight.png");
                                        break;
								case WHITE_BISHOP:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_bishop.png");
                                        break;
								case WHITE_ROOK:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_rook.png");
                                        break;
								case WHITE_PAWN:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/white_pawn.png");
                                        break;
								case BLACK_KING:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_king.png");
                                        break;
								case BLACK_QUEEN:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_queen.png");
                                        break;
								case BLACK_KNIGHT:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_knight.png");
                                        break;
								case BLACK_BISHOP:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_bishop.png");
                                        break;
								case BLACK_ROOK:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_rook.png");
                                        break;
								case BLACK_PAWN:
										chess_icon = gtk_image_new_from_file("./Chess_Pieces/black_pawn.png");
                                		break;       
								 default:
                                        break;
                        }

                        gtk_table_attach(GTK_TABLE(table), chess_icon, i, i+1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0);
                }
        }
}

void CoordToGrid(int coordX, int coordY, int *gridX, int *gridY)
{
        *gridX = (coordX - BOARD_BORDER) / SQUARE_SIZE;
        *gridY = (coordY - BOARD_BORDER) / SQUARE_SIZE;
}

/* Callback Function */
static void print_hello(GtkWidget *widget, gpointer data)
{
        g_print("Hello World\n");
}

/* Callback Function */
static gboolean on_delete_event(GtkWidget *widget, GdkEvent  *event, gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
 *  *      * GTK will emit the "destroy" signal. Returning TRUE means
 *   *           * you don't want the window to be destroyed.
 *    *                * This is useful for popping up 'are you sure you want to quit?'
 *     *                     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
 *  *      * a "delete-event". */
        gtk_main_quit();
    return TRUE;
}
		

/* This function changes the original location of a chess piece to the original black or white square */
int PieceOrigin(int gridX, int gridY)
{
	int  flag;
	if (gridX % 2 == 0)
	{
		if (gridY % 2 == 0)
		{
			Board[gridX][gridY] = WHITE;
		}
		else
		{
			Board[gridX][gridY] = BLACK;
		}
	}
	else
	{
		if (gridY % 2 == 0)
		{
			Board[gridX][gridY] = BLACK;
		}
		else
		{
			Board[gridX][gridY] = WHITE;
		}
	} 
	

	
	printf("gridX = %d, gridY = %d\n", gridX, gridY);
	flag = 1;
	return flag;

}
/* This function moves a Chess Piece to the destination indicated by the user and redraws the Chess Board */
void MovePiece(int gridX, int gridY, enum GRID temp)
{
	switch(temp)
	{
		case WHITE_KING:
			Board[gridX][gridY] = WHITE_KING;
			break;
		case WHITE_QUEEN:
			Board[gridX][gridY] = WHITE_QUEEN;
			break;
		case WHITE_KNIGHT:
			Board[gridX][gridY] = WHITE_KNIGHT;
			break;
		case WHITE_BISHOP:
			Board[gridX][gridY] = WHITE_BISHOP;
			break;
		case WHITE_ROOK:
			Board[gridX][gridY] = WHITE_ROOK;
			break;
		case WHITE_PAWN:
			Board[gridX][gridY] = WHITE_PAWN;
			break;
		case BLACK_KING:
			Board[gridX][gridY] = BLACK_KING;
			break;
		case BLACK_QUEEN:
			Board[gridX][gridY] = BLACK_QUEEN;
			break;
		case BLACK_KNIGHT:
			Board[gridX][gridY] = BLACK_KNIGHT;
			break;
		case BLACK_BISHOP:
			Board[gridX][gridY] = BLACK_BISHOP;
			break;
		case BLACK_ROOK:
			Board[gridX][gridY] = BLACK_ROOK;
			break;
		case BLACK_PAWN:
			Board[gridX][gridY] = BLACK_PAWN;
			break;
		default:
			break;
	}
	printf("gridX = %d, gridY = %d\n", gridX, gridY);

	gtk_container_remove(GTK_CONTAINER(window), fixed);
    table = gtk_table_new(8, 8, TRUE);
    gtk_widget_set_size_request(table, BOARD_WIDTH, BOARD_HEIGHT);
    DrawBoard();

     

    fixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_widget_show_all(window);


}	
/* This is the function that controls the user clicking and moving a piece */
gint area_click(GtkWidget *widget, GdkEvent *event, gpointer data)
{
        int x1, y1;
        char words[MAX_GLEN];

        int coordX, coordY, gridX, gridY;
		static int flag;
		static int tempX, tempY; //Variables to hold the initial location of the piece the user wanst to move
		static enum GRID temp; //Variable to hold the name of what piece the user is moving

        struct BOARD *chess_board;
        struct SQUARE *chess_piece;
        struct SQUARE *piece_dest;


        GdkModifierType state;

        gdk_window_get_pointer(widget->window, &coordX, &coordY, &state);

        CoordToGrid(coordX, coordY, &gridX, &gridY);
		
        printf("coordX = %d, coordY = %d, gridX = %d, gridY = %d \n", coordX, coordY, gridX, gridY);

		printf("Please select a piece to move! \n");
		switch(Board[gridX][gridY])
		{
			case WHITE_KING:
				printf("Please select where you want to move the piece! \n");
				printf("flag before is %d\n", flag);
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_KING;
				flag = PieceOrigin(gridX, gridY);
				printf("flag after is %d\n", flag);
				break;
			case WHITE_QUEEN:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_QUEEN;
				flag = PieceOrigin(gridX, gridY);
				break;
			case WHITE_KNIGHT:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_KNIGHT;
				flag = PieceOrigin(gridX, gridY);
				break;
			case WHITE_BISHOP:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_BISHOP;
				flag = PieceOrigin(gridX, gridY);
				break;
			case WHITE_ROOK:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_ROOK;
				flag = PieceOrigin(gridX, gridY);
				break;
			case WHITE_PAWN:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = WHITE_PAWN;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_KING:
				printf("Please select where you want to move the piece! \n");
				printf("Flag is %d\n", flag);
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_KING;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_QUEEN:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_QUEEN;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_KNIGHT:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_KNIGHT;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_BISHOP:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_BISHOP;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_ROOK:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_ROOK;
				flag = PieceOrigin(gridX, gridY);
				break;
			case BLACK_PAWN:
				printf("Please select where you want to move the piece! \n");
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;
					break;		
				}		
				tempX = gridX;
				tempY = gridY;
				temp = BLACK_PAWN;
				flag = PieceOrigin(gridX, gridY);
				break;

			default:
				printf("flag is %d\n", flag);
				if (flag == 1)
				{
					printf("tempX is %d, tempY is %d\n", tempX, tempY);		
					MovePiece(gridX, gridY, temp);
					flag = 0;		
				}		
				break;
		}

    /*  gtk_container_remove(GTK_CONTAINER(window), fixed);
        table = gtk_table_new(8, 8, TRUE);
        gtk_widget_set_size_request(table, BOARD_WIDTH, BOARD_HEIGHT);
        DrawBoard();
     
        fixed = gtk_fixed_new();
        gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0);
        gtk_container_add(GTK_CONTAINER(window), fixed);
        gtk_widget_show_all(window);
*/
        return TRUE;
}



int main(int argc, char *argv[])
{
        char str[MAX_GLEN];

        gtk_init(&argc, &argv);
    //    ResetBoard();
		InitBoard();
  
        /*Create a new Window*/
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT);
        gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_BORDER);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!");
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        /*Register event handlers*/
        g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL);
        gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK);
        g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL);

        /*Create a table and draw the board*/
        table = gtk_table_new(8, 8, TRUE);
        gtk_widget_set_size_request(table, BOARD_WIDTH, BOARD_HEIGHT);
        DrawBoard();

        fixed = gtk_fixed_new();
        gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0);
        gtk_container_add(GTK_CONTAINER(window), fixed);

        /*show the window*/
        gtk_widget_show_all(window);
        gtk_main();

        return 0;
}
