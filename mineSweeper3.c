#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 25
// The variable 'i' always means the y coordinate, 'j' always means x coordiante
//FIXTHIS: Make it so the white space clears all other white space touching it
void layMines(int x, int y, int prob, int board[MAXSIZE][MAXSIZE]) {
	int randnum;
	int i;
	int j;
	time_t t;
	randnum = 0;
	srand((unsigned) time(&t));
	for(i = 0; i < 1; i ++) {
		for(j = 0; j < (x + 2); j++) {
			board[j][i] = 0;
		}
	}
	for(i = (y+1); i < (y +2); i ++) {
		for(j = 0; j < (x + 2); j++) {
			board[j][i] = 0;
		}
	}
	for(i = 0; i < (y+2); i ++) {
		for(j = 0; j < 1; j++) {
			board[j][i] = 0;
		}
	}
	for(i = 0; i < (y+2); i ++) {
		for(j = (x+1); j < (x + 2); j++) {
			board[j][i] = 0;
		}
	}
	for(i = 1; i < (y+1); i++) {
		for(j = 1; j < (x+1); j++) {
			randnum = (rand()%100);
			//printf("%d",randnum);
			if (prob > randnum) {
				board[j][i] = 0;
			}
			else {
				board[j][i] = 1;
			}
			//printf(" %d", board[j][i]);
		}
		//printf("\n");
	}
	for(i = 0; i < (y + 2); i++) {
		for(j = 0; j < (x + 2); j++) {
			//printf(" %d", board[j][i]);
		}
		//printf("\n");
	}
}

void mineFreq(int x, int y, int board[MAXSIZE][MAXSIZE], int map[MAXSIZE][MAXSIZE]) {
	int i;
	int j;
	for(j = 0; j < (x+1); j++) {
		//printf("- ");
	}
	//printf("\n");
	for(i = 1; i < (y+1); i++) {
		//printf("|");
		for(j = 1; j < (x+1); j++) {
			if(board[j][i] == 0) {
				map[j][i] = board[j-1][i+1] + board[j][i+1] + board[j+1][i+1] +
							 board[j-1][i] + board[j+1][i] +
							 board[j-1][i-1] + board[j][i-1] + board[j+1][i-1];
				if(map[j][i] == 0) {
					map[j][i] = 11;
					//printf("  ");
				}
				else {
				//printf(" %d", map[j][i]);
				}
			}
			else {
				map[j][i] = 9;
				//printf(" X");
			}
		}
		//printf("|\n");
	}
	for(j = 0; j < (x+1); j++) {
		//printf("- ");
	}
}	

int numMines(int x, int y, int board[MAXSIZE][MAXSIZE]) {
	int mines;
	int i;
	int j;
	for(i = 1; i < (y+1); i++) {
		for(j = 1; j < (x+1); j++) {
			mines = mines + board[j][i];
		}
	}
	return mines;
}

void playGame(int x, int y, int board[MAXSIZE][MAXSIZE], int map[MAXSIZE][MAXSIZE], int playBoard[MAXSIZE][MAXSIZE], int turns) {
	int i;
	int j;
	int guessX;
	int guessY;
	bool hitMine;
	int k;
	k = x * y;
	guessX = 0;
	guessY = 0;
	hitMine = false;
	for(j = 0; j < (x+1); j++) {
		printf("- ");
	}
	printf("\n");
	for(i = 0; i < y; i++) {
		printf("|");
		for(j = 0; j < x; j++) {
			playBoard[j][i] = 0;
			printf(" %d", playBoard[j][i]);
		}
		printf("|\n");
	}
	for(j = 0; j < (x+1); j++) {
		printf("- ");
	}
	printf("\n");
	while(hitMine == false) {
		if (k > turns) {
			printf("Guess an x value! (The top left spot is x = 1, y = 1)\n");
			scanf("%d", &guessX);
			j = guessX;
			printf("Guess a y value!\n");
			scanf("%d", &guessY);
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			i = guessY ;
			k = 0;
			if(board[j][i] == 0) {
				playBoard[j-1][i-1] = map[j][i];
				if(map[j][i] > 10) {
					if(map[j+1][i+1] != 9) {
						playBoard[j][i] = map[j+1][i+1];
					}
					if(map[j][i+1] != 9) {
						playBoard[j-1][i] = map[j][i+1];
					}
					if(map[j-1][i+1] != 9) {
						playBoard[j-2][i] = map[j-1][i+1];
					}
					if(map[j+1][i] != 9) {
						playBoard[j][i-1] = map[j+1][i];
					}
					if(map[j+1][i-1] != 9) {
						playBoard[j][i-2] = map[j+1][i-1];
					}
					if(map[j][i] != 9) {
						playBoard[j-1][i-1] = map[j][i];
					}
					if(map[j][i-1] != 9) {
						playBoard[j-1][i-2] = map[j][i-1];
					}
					if(map[j-1][i] != 9) {
						playBoard[j-2][i-1] = map[j-1][i];
					}
					if(map[j-1][i-1] != 9) {
						playBoard[j-2][i-2] = map[j-1][i-1];
					}	
				}
				for(j = 0; j < (x+1); j++) {
					printf("- ");
				}
				printf("\n");
				for(i = 0; i < y; i++) {
					printf("|");
					for(j = 0; j < x; j++) {
						if(playBoard[j][i] < 10) {
							printf(" %d", playBoard[j][i]);
							if(playBoard[j][i] == 0) {
								k = k + 1;
							}
						}
						else {
							printf("  ");
						}
					}
					printf("|\n");
				}
				for(j = 0; j < (x+1); j++) {
					printf("- ");
				}
				printf("\n");
			}	
			else {
				hitMine = true;
				printf("Sorry, you hit a mine.");
			}
		}
		else {
			hitMine = true;
			printf("Good job, you win!");
		}
	}
}

void main() {
	int grid[MAXSIZE][MAXSIZE];
	int bombfreq[MAXSIZE][MAXSIZE];
	int showBoard[MAXSIZE][MAXSIZE]; 
	int x;
	int y;
	int prob;
	int numberofmines;
	printf("What is the width of the board?(25 is the Max)\n");
	scanf("%d", &x);
	printf("What is the height of the board?(25 is the Max)\n");
	scanf("%d", &y);
	printf("How often should mines be laid down? (Pick 1 - 100 with 1 being very often)\n");
	scanf("%d", &prob);
	time_t t;
	layMines(x, y, prob, grid);
	printf("\n");
	mineFreq(x, y, grid, bombfreq);
	printf("\n");
	numberofmines = numMines(x, y, grid);
	//printf("%d", numberofmines);
	playGame(x, y, grid, bombfreq, showBoard, numberofmines);
}