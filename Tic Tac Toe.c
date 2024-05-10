#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

//Symbols
const char PLAYER1='X';
const char PLAYER2='O';

//Functions
char gameMode();
int whoBegins();
void resetBoard(char bo[]);
void showBoard(char bo[]);
int checkAvailableBlocks(char bo[]);
void playerMove(char bo[],const char symbol);
void computerMove(char bo[],const char symbol,int P1W,int P2W,int P1L,int P2L,int D);
char checkWinner(char bo[]);
void showWinner(char winner);
void showStats(int P1W,int P2W,int P1L,int P2L,int D);
char playAgain();


int main()
{
	int P1Wins=0,P1Losses=0,P2Wins=0,P2Losses=0,Draws=0,firstPlayer,availableBlocks;
	
	char board[9],selection,winner,response;
	
	printf("\nWELCOME!\n");
	
	//gameMode defines if player will play single or two-player mode
	selection=gameMode();
		
		//Two players mode
		if(selection=='T')
		{
			do{
	
				winner=' ';
		
				response=' ';
		
				//whoBegins defines which player makes the first move
				firstPlayer=whoBegins();
		
				if (firstPlayer%2==0)
				{
					printf("Player 1 [X] is playing first :\n");
				}
		
				else
				{
					printf("Player 2 [O] is playing first :\n");
				}
	
				//Board initialization
				resetBoard(board);
			
				//checkAvailableBlocks checks how many blocks are available in the board
				availableBlocks=checkAvailableBlocks(board);
			
				while(winner==' '&& availableBlocks!=0){
			
					//Players' moves on the board
					if(firstPlayer%2==0)
					{			
						playerMove(board,PLAYER1);
					
						//After each move the available blocks are checked again by checkAvailableBlocks
						availableBlocks=checkAvailableBlocks(board);
						
						winner=checkWinner(board);
					
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
															
						playerMove(board,PLAYER2);
					
						availableBlocks=checkAvailableBlocks(board);
				
						winner=checkWinner(board);
					
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
					}
			
					else
					{	
						playerMove(board,PLAYER2);
					
						availableBlocks=checkAvailableBlocks(board);
					
						winner=checkWinner(board);
						
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
					
						playerMove(board,PLAYER1);
					
						availableBlocks=checkAvailableBlocks(board);
				
						winner=checkWinner(board);
						
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}	
					}
				}
				
				//The winner is shown here
				showBoard(board);
		
				showWinner(winner);
				
				//Statistics calculations
				if(winner==PLAYER1)
				{
					P1Wins++;
				
					P2Losses++;
				}
				else if(winner==PLAYER2)
				{
					P2Wins++;
					
					P1Losses++;
				}
				else
				{
					Draws++;
				}
			
				//Statistics are shown here
				showStats(P1Wins,P2Wins,P1Losses,P2Losses,Draws);
			
				//playAgain defines whether the user wants to play a new set
				response=playAgain();
		
			}while(response=='Y');
		}
		
		//One player mode
		else if(selection=='O')
		{
			do{
	
				winner=' ';
		
				response=' ';
		
				firstPlayer=whoBegins();
			
				if (firstPlayer%2==0)
				{
					printf("\nPlayer 1 [X] is playing first :\n");
				}
		
				else
				{
					printf("\nPlayer 2 [O] is playing first :\n");
				}
	
				resetBoard(board);
			
				availableBlocks=checkAvailableBlocks(board);
			
				while(winner==' '&& availableBlocks!=0){
			
					if(firstPlayer%2==0)
					{				
						playerMove(board,PLAYER1);

						availableBlocks=checkAvailableBlocks(board);	
					
						winner=checkWinner(board);
					
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
					
						computerMove(board,PLAYER2,P1Wins,P2Wins,P1Losses,P2Losses,Draws);
				
						availableBlocks=checkAvailableBlocks(board);
				
						winner=checkWinner(board);
						
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
					}
			
					else
					{	
						computerMove(board,PLAYER2,P1Wins,P2Wins,P1Losses,P2Losses,Draws);
					
						availableBlocks=checkAvailableBlocks(board);
					
						winner=checkWinner(board);
	
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}
					
						playerMove(board,PLAYER1);
				
						availableBlocks=checkAvailableBlocks(board);
				
						winner=checkWinner(board);
					
						if(winner!=' ' || availableBlocks==0)
						{
							break;
						}	
					}		
				}
		
				showBoard(board);
		
				showWinner(winner);
			
				if(winner==PLAYER1)
					{
						P1Wins++;
					
						P2Losses++;
					}
				else if(winner==PLAYER2)
					{
						P2Wins++;
					
						P1Losses++;
					}
				else
					{
						Draws++;
					}
			
				showStats(P1Wins,P2Wins,P1Losses,P2Losses,Draws);
				
				response=playAgain();
		
			}while(response=='Y');
		}
	
	printf("\nOverall Stats : ");
	
	showStats(P1Wins,P2Wins,P1Losses,P2Losses,Draws);
	
	printf("\n\nThanks for playing!\n");
	
	system ("pause");
		
}

//gameMode FUNCTION

char gameMode()
{

	char selection;

	printf("\nWould you like to play One-Player or Two-Players Mode ?");
	
	printf("\n[O] for One-Player [T] for Two-players :");
	
	scanf("%c", &selection);
	
	selection=toupper(selection);
	
	return selection;
}

int whoBegins()
{
	int x;
	
	srand(time(NULL));
	
	x=(rand()%(100-1+1)+1);
	
	return x;
}

void resetBoard(char bo[])
{
	int i;
	
	for(i=0;i<9;i++)
	{
		bo[i]=' ';
	}
}

void showBoard(char bo[])
{
	printf(" %c | %c | %c\n", bo[0], bo[1], bo[2]);
	
	printf("---|---|---\n");
	
	printf(" %c | %c | %c\n", bo[3], bo[4], bo[5]);
	
	printf("---|---|---\n");
	
	printf(" %c | %c | %c\n", bo[6], bo[7], bo[8]);
}

int checkAvailableBlocks(char bo[])
{
	int i,freeSpaces=9;
	
	for(i=0;i<9;i++)
	{
		if(bo[i]!=' ')
		{
			freeSpaces--;
		}
	}
	
	return freeSpaces;
}

void playerMove(char bo[],const char symbol)
{
	int choice;
	
	showBoard(bo);
	
	do{
		printf("\nSelect a block (1-9) : ");
	
		scanf("%d", &choice);
	
		choice--;
	
		if(bo[choice]!=' ')
		{
			printf("\nInvalid Move!");
		}
	
		else
		{
			bo[choice]=symbol;
			
			break;
		}
	}while(bo[choice]!=' ');
}

void computerMove(char bo[],const char symbol,int P1W,int P2W,int P1L,int P2L,int D)
{
	int x;

	srand(time(NULL));
	
	if(checkAvailableBlocks(bo)>0)
	{
		do{
			x=(rand()%(9-1+1)+1);
			
		}while(bo[x]!=' ');
		
		bo[x]=symbol;
	}
	
	return;
}

char checkWinner(char bo[])
{
	int i;
	
	//Rows check
	for(i=0;i<9;i+=3)
	{
		if(bo[i]==bo[i+1] && bo[i]==bo[i+2] && bo[i]!=' ')
		{
			return bo[i];
		}
	}
	
	//Columns check
	for(i=0;i<3;i++)
	{
		if(bo[i]==bo[i+3] && bo[i]==bo[i+6] && bo[i]!=' ')
		{
			return bo[i];
		}
	}
	
	//Diagonal lines check
	if(bo[0]==bo[4] && bo[0]==bo[8])
	{
		return bo[0];
	}
		
	if(bo[2]==bo[4] && bo[2]==bo[6])
	{
		return bo[2];
	}
	
	return ' ';
}

void showWinner(char winner)
{
	if(winner==PLAYER1)
	{
		printf("\nPLAYER 1 WINS!");
		
	}
	
	else if(winner==PLAYER2)
	{
		printf("\nPLAYER 2 WINS!");
		
	}
	
	else if(winner==' ')
	{
		printf("\nIT'S A TIE!");
	
	}
	
	return;
}

void showStats(int P1W,int P2W,int P1L,int P2L,int D)
{
	printf("\n\nPlayer 1 Stats : %d Wins/%d Draws/%d Losses", P1W, D, P1L);
	
	printf("\n\nPlayer 2 Stats : %d Wins/%d Draws/%d Losses", P2W, D, P2L);
	
	return;
}

char playAgain()
{
	char reply;

	printf("\n\nWould you like to play again?\n[Y] for Yes [N] for No : ");
	
	scanf("%c");
	
	scanf("%c", &reply);
	
	reply=toupper(reply);

	return reply;
}
