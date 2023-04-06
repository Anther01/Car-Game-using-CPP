#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void modes();
void gotoxy(int x, int y);
void instructions();
void setcursor(bool visible, DWORD size);
void gameover();
void getMenu();
void easyPlay();
void mediumPlay();
void hardPlay();
void drawEnemy(int);
void eraseEnemy(int ind);
void resetEnemy(int ind);
int collision();
void drawBorder();
void updateScore();
void drawCar();
void eraseCar();
void genEnemy(int ind);

int carPos = WIN_WIDTH/2;
int score = 0;
const char car[4][4]  = {' ', '±', '±', ' ',
				  '±', '*', '*', '±', 
				  ' ', '*', ' *', ' ', 
				  '±', '*', '*', '±',}; 
int enemyY[5];
int enemyX[5];
int enemyFlag[3];

int main(int argc, char** argv) {
	
	getMenu();
}

void getMenu(){
	setcursor(0,0);
	srand((unsigned)time(NULL));
	
	do {
		system("cls");
		system("color A");
		gotoxy(50,5); cout << " ------------------- ";
		gotoxy(50,6); cout << " |     CAR GAME    |";
		gotoxy(50,7); cout << " ------------------- ";
		gotoxy(50,9); cout << " 	NEW GAME      	";
		gotoxy(50,10); cout << " 	INSTRUCTIONS	";
		gotoxy(50,11); cout << " 	QUIT			";
		gotoxy(50,13); cout << ">>> CHOICE:		";
		char op = getche();
		
		switch(op) {
			case '1':
				modes();
				break;
			case '2':
				instructions();
				break;
			case '3':
				exit(0);
				break;
			default:
				cout << "Invalid! Try again";
				break;
		}
		
	} while (1);

}

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;
		
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo (console, &lpCursor);
} 

void gameover() {
	system("cls");
	cout << "it's over.";
	getch();
}

void instructions() {
	system("cls");
	cout << "Avoid cars, A = left, d = right, escape = exit" << endl;
	cout << "Press any key to continue";
	getch();
}

void modes(){
	
	setcursor(0,0);
	srand((unsigned)time(NULL));
	
	do {
		system("cls");
		system("color A");
		gotoxy(50,5); cout << " ------------------- ";
		gotoxy(50,6); cout << " |     CAR GAME    |";
		gotoxy(50,7); cout << " ------------------- ";
		gotoxy(50,9); cout << " 	EASY MODE      	";
		gotoxy(50,10); cout << " 	MEDIUM MODE	";
		gotoxy(50,11); cout << " 	LEGENDARY MODE(HARD)	";
		gotoxy(50,12); cout << " 	BACK	";
		gotoxy(50,14); cout << ">>> CHOICE:		";
		char op = getche();
		
		switch(op) {
			case '1':
				easyPlay();
				break;
			case '2':
				mediumPlay();
				break;
			case '3':
				hardPlay();	
			case '4':
				getMenu();	
			default:
				cout << "Invalid! Try again";
				Sleep(888);
				break;
		}
		
	} while (1);
}

void genEnemy(int ind) {
	enemyX[ind] = 17 + rand()%(33);
}

void drawEnemy(int ind) {
	
	if(enemyFlag[ind] == true) {
		gotoxy(enemyX[ind], enemyY[ind]);   cout << "|  |";
		gotoxy(enemyX[ind], enemyY[ind]);   cout << "±**±";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout << " ** ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout << "±**±";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout << " ** ";
	}

}

void eraseEnemy(int ind) {
	if(enemyFlag[ind] == true) {
		gotoxy(enemyX[ind], enemyY[ind]);   cout << "     ";
		gotoxy(enemyX[ind], enemyY[ind]);   cout << "     ";
		gotoxy(enemyX[ind], enemyY[ind]+1); cout << "     ";
		gotoxy(enemyX[ind], enemyY[ind]+2); cout << "     ";
		gotoxy(enemyX[ind], enemyY[ind]+3); cout << "     ";
	}
}

void resetEnemy(int ind) {
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}

void drawBorder() {
	for(int i = 0; i < SCREEN_HEIGHT; i++) {
		for(int j = 0; j < 17; j++) {
			gotoxy(0+j, i); cout << "±";
			gotoxy(WIN_WIDTH-j, i); cout << "±";
		}
	}
	
	for(int i = 0; i < SCREEN_HEIGHT; i++) {
		gotoxy(SCREEN_WIDTH, i); cout << "±";
	}
		
}

int collision() {
	if((enemyY[0]) + 4 >= 23) {
		if(enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9) {
			return 1;
		}
	}
	return 0;
}

void updateScore() {
	
	gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
	
	
}
			  
void drawCar() {
	for(int i = 0; i<4; i++) {
		for(int j = 0; j<4; j++) {
			gotoxy(j+carPos, i+22); cout << car[i][j];
		}
	}
	
}

void eraseCar() {
	for(int i = 0; i<4; i++) {
		for(int j = 0; j<4; j++) {
			gotoxy(j+carPos, i+22); cout << " ";
		}
	}
}

void easyPlay() {
	
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	
	system("cls");
	system("color A");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 2); cout << "THE CAR GAME";
	gotoxy(WIN_WIDTH + 6, 4); cout << "---------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "CONTROLS:";
	gotoxy(WIN_WIDTH + 7, 13); cout << "---------";
	gotoxy(WIN_WIDTH + 2, 14); cout << "A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15); cout << "D Key - Right";
	
	gotoxy(18, 5); cout << "Press any key to begin";
	getch();
	gotoxy(18, 5); cout << "                        ";
	
	
	while(1) {
		if(kbhit()) {
			char ch = getch();
			if( ch == 'a' || ch == 'A') {
				// Change speed of left
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch == 'd' || ch == 'D') {
				// Change speed of right
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27) {
				break;
			}
		}
		
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if ( collision() == 1) {
			gameover();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if (enemyY[0] == 10)
			if( enemyFlag[1] == 0 )
		    	enemyFlag[1] = 1;
		    	
			if(enemyFlag[0] == 1)
				enemyY[0] += 1;
				
			if ( enemyFlag[1] == 1)
				enemyY[1] += 1;
				
			if(enemyY[0] > SCREEN_HEIGHT - 4) {
				resetEnemy(0);
				score++;
				updateScore();
			}
			if( enemyY[1] > SCREEN_HEIGHT- 4) {
				resetEnemy(1);
				score++;
				updateScore();
			}
	}
	
}

void mediumPlay() {
	
	system("color f");
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	
	system("cls");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 2); cout << "THE CAR GAME";
	gotoxy(WIN_WIDTH + 6, 4); cout << "---------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "CONTROLS:";
	gotoxy(WIN_WIDTH + 7, 13); cout << "---------";
	gotoxy(WIN_WIDTH + 2, 14); cout << "A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15); cout << "D Key - Right";
	
	gotoxy(18, 5); cout << "Press any key to begin";
	getch();
	gotoxy(18, 5); cout << "                        ";
	
	
	while(1) {
		if(kbhit()) {
			char ch = getch();
			if( ch == 'a' || ch == 'A') {
				// Change speed of left
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch == 'd' || ch == 'D') {
				// Change speed of right
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27) {
				break;
			}
		}
		
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if ( collision() == 1) {
			gameover();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if (enemyY[0] == 10)
			if( enemyFlag[1] == 0 )
		    	enemyFlag[1] = 1;
		    	
			if(enemyFlag[0] == 1)
				enemyY[0] += 2;
				
			if ( enemyFlag[1] == 1)
				enemyY[1] += 1;
				
			if(enemyY[0] > SCREEN_HEIGHT - 4) {
				resetEnemy(0);
				score++;
				updateScore();
			}
			if( enemyY[1] > SCREEN_HEIGHT- 4) {
				resetEnemy(1);
				score++;
				updateScore();
			}
	}
}

void hardPlay() {
	
	carPos = -1 + WIN_WIDTH/2;
	score = 0;
	enemyFlag[0] = 1;
	enemyFlag[1] = 0;
	enemyY[0] = enemyY[1] = 1;
	
	system("cls");
	system("color C");
	drawBorder();
	updateScore();
	genEnemy(0);
	genEnemy(1);
	
	gotoxy(WIN_WIDTH + 7, 2); cout << "THE CAR GAME";
	gotoxy(WIN_WIDTH + 6, 4); cout << "---------";
	gotoxy(WIN_WIDTH + 7, 12); cout << "CONTROLS:";
	gotoxy(WIN_WIDTH + 7, 13); cout << "---------";
	gotoxy(WIN_WIDTH + 2, 14); cout << "A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15); cout << "D Key - Right";
	
	gotoxy(18, 5); cout << "Press any key to begin";
	getch();
	gotoxy(18, 5); cout << "                        ";
	
	
	while(1) {
		if(kbhit()) {
			char ch = getch();
			if( ch == 'a' || ch == 'A') {
				// Change speed of left
				if( carPos > 18 )
					carPos -= 4;
			}
			if( ch == 'd' || ch == 'D') {
				// Change speed of right
				if( carPos < 50 )
					carPos += 4;
			}
			if(ch==27) {
				break;
			}
		}
		
		drawCar();
		drawEnemy(0);
		drawEnemy(1);
		if ( collision() == 1) {
			gameover();
			return;
		}
		Sleep(50);
		eraseCar();
		eraseEnemy(0);
		eraseEnemy(1);

		if (enemyY[0] == 10)
			if( enemyFlag[1] == 0 )
		    	enemyFlag[1] = 1;
		    	
			if(enemyFlag[0] == 1)
				enemyY[0] += 3;
				
			if ( enemyFlag[1] == 1)
				enemyY[1] += 1;
				
			if(enemyY[0] > SCREEN_HEIGHT - 4) {
				resetEnemy(0);
				score++;
				updateScore();
			}
			if( enemyY[1] > SCREEN_HEIGHT- 4) {
				resetEnemy(1);
				score++;
				updateScore();
			}
	}
	
}

