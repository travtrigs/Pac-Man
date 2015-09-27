#include <iostream>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <limits>
#include <thread>
#include <chrono>
#include "Carbon/Carbon.h"
using namespace std;

bool isPressed( unsigned short);
void clearscreen();

int main(int argc, const char * argv[]) {
	string icon[12] = { "   ", " * ", " X ", " ╔═", "═╗ ", " ╚═", "═╝ ", " ║ ", "═══", " O ", "   ",  " &"};
	int board[31][28] = {
		{ 3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4 },
		{ 7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,7 },
		{ 7,1,3,4,1,3,8,8,4,1,3,8,8,8,8,8,8,4,1,3,8,8,4,1,3,4,1,7 },
		{ 7,2,7,7, 1,7,0,0,7,1,7,3,8,8,8,8,4,7,1,7,0,0,7,1,7,7,2,7 },
		{ 7,1,7,7, 1,5,8,8,6,1,7,7,1,1,1,1,7,7,1,5,8,8,6,1,7,7,1,7 },
		{ 7,1,7,7,1,1,1,1,1,1,7,7,1,3,4,1,7,7,1,1,1,1,1,1,7,7,1,7},
		{ 7,1,7,5,8,4,1,3,4,1,7,7,1,7,7,1,7,7,1,3,4,1,3,8,6,7,1,7},
		{ 7,1,5,8,8,6,1,7,7,1,5,6,1,7,7,1,5,6,1,7,7,1,5,8,8,6,1,7},
		{ 7,1,1,1,1,1,1,7,7,1,1,1,1,7,7,1,1,1,1,7,7,1,1,1,1,1,1,7},
		{ 5,8,4,1,3,8,8,6,5,8,8,4,0,7,7,0,3,8,8,6,5,8,8,4,1,3,8,6},
		{ 0,0,7,1,5,8,8,4,3,8,8,6,0,5,6,0,5,8,8,4,3,8,8,6,1,7,0,0},
		{ 0,0,7,1,1,1,1,7,7,0,0,0,0,0,0,0,0,0,0,7,7,1,1,1,1,7,0,0},
		{ 8,8,6,0,3,4,1,7,7,0,3,8,8,0,0,8,8,4,0,7,7,1,3,4,0,5,8,8},
		{ 10,0,0,0,7,7,1,5,6,0,7,0,0,0,0,0,0,7,0,5,6,1,7,7,0,0,0,10},
		{ 8,8,8,8,6,7,1,0,0,0,7,0,0,0,0,0,0,7,0,0,0,1,7,5,8,8,8,8},
		{ 8,8,8,8,4,7,1,3,4,0,7,0,0,0,0,0,0,7,0,3,4,1,7,3,8,8,8,8},
		{ 10,0,0,0,7,7,1,7,7,0,5,8,8,8,8,8,8,6,0,7,7,1,7,7,0,0,0,10},
		{ 8,8,4,0,5,6,1,7,7,0,0,0,0,0,0,0,0,0,0,7,7,1,5,6,0,3,8,8},
		{ 0,0,7,1,1,1,1,7,5,8,8,4,0,3,4,0,3,8,8,6,7,1,1,1,1,7,0,0},
		{ 0,0,7,1,3,4,1,5,8,8,8,6,0,7,7,0,5,8,8,8,6,1,3,4,1,7,0,0},
		{ 0,0,7,1,7,7,1,1,1,1,1,0,0,7,7,0,0,1,1,1,1,1,7,7,1,7,0,0},
		{ 0,0,7,1,7,5,8,8,4,1,3,4,0,7,7,0,3,4,1,3,8,8,6,7,1,7,0,0},
		{ 3,8,6,1,5,8,8,8,6,1,7,7,0,5,6,0,7,7,1,5,8,8,8,6,1,5,8,4},
		{ 7,1,1,1,1,1,1,1,1,1,7,7,0,0,0,0,7,7,1,1,1,1,1,1,1,1,1,7},
		{ 7,1,3,8,8,4,1,3,4,1,7,5,8,8,8,8,6,7,1,3,4,1,3,8,8,4,1,7},
		{ 7,1,7,3,8,6,1,7,7,1,5,8,8,8,8,8,8,6,1,7,7,1,5,8,4,7,1,7},
		{ 7,1,7,7,1,1,1,7,7,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1,7,7,1,7},
		{ 7,2,7,7,1,3,8,6,5,8,8,4,1,3,4,1,3,8,8,6,5,8,4,1,7,7,2,7},
		{ 7,1,5,6,1,5,8,8,8,8,8,6,1,7,7,1,5,8,8,8,8,8,6,1,5,6,1,7},
		{ 7,1,1,1,1,1,1,1,1,1,1,1,1,7,7,1,1,1,1,1,1,1,1,1,1,1,1,7},
		{ 5,8,8,8,8,8,8,8,8,8,8,8,8,6,5,8,8,8,8,8,8,8,8,8,8,8,8,6}
	};
	bool blocked[31][28];
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 28; j++) {
			if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 0) {
				blocked[i][j] = true;
			}
			else blocked[i][j] = false;
			cout << icon[board[i][j]];
		}
		cout << endl;
	}
	
	int score = 0;
	bool power = false;
	int length = 30;
	int remaining = 0;
	int ghost = 0;
	int y=23, x=13;
	board[y][x] = 9;
	while (true) {
		clearscreen();
		this_thread::sleep_for (chrono::milliseconds(50));
		ghost++;
		
		for (int i = 0; i < 31; i++) {
			for (int j = 0; j < 28; j++) {
				if (board[i][j] == 1 || board[i][j] == 2 || board[i][j] == 0) {
					blocked[i][j] = true;
				}
				else blocked[i][j] = false;
				cout << icon[board[i][j]];
			}
			cout << endl;
		}
		
		if (isPressed(123)) {
			if (board[y][x-1] == 0) {
				board[y][x] = 0;
				x--;
				board[y][x] = 9;
			}
			if (board[y][x-1] == 1) {
				board[y][x] = 0;
				x--;
				board[y][x] = 9;
				score += 5;
			}
			if (board[y][x-1] == 2) {
				board[y][x] = 0;
				x--;
				board[y][x] = 9;
				score += 10;
				power = true;
			}
			if (board[y][x-2] == 10) {
				board[y][x] = 0;
				x = 26;
				board[y][x] = 9;
			}
		}
		if (isPressed(124)) {
			if (board[y][x+1] == 0) {
				board[y][x] = 0;
				x++;
				board[y][x] = 9;
			}
			if (board[y][x+1] == 1) {
				board[y][x] = 0;
				x++;
				board[y][x] = 9;
				score += 5;
			}
			if (board[y][x+1] == 2) {
				board[y][x] = 0;
				x++;
				board[y][x] = 9;
				score += 10;
				power = true;
			}
			if (board[y][x+2] == 10) {
				board[y][x] = 0;
				x = 2;
				board[y][x] = 9;
			}
		}
		if (isPressed(125)) {
			if (board[y+1][x] == 0) {
				board[y][x] = 0;
				y++;
				board[y][x] = 9;
			}
			if (board[y+1][x] == 1) {
				board[y][x] = 0;
				y++;
				board[y][x] = 9;
				score += 5;
			}
			if (board[y+1][x] == 2) {
				board[y][x] = 0;
				y++;
				board[y][x] = 9;
				score += 10;
				power = true;
			}
		}
		if (isPressed(126)) {
			if (board[y-1][x] == 0) {
				board[y][x] = 0;
				y--;
				board[y][x] = 9;
			}
			if (board[y-1][x] == 1) {
				board[y][x] = 0;
				y--;
				board[y][x] = 9;
				score += 5;
			}
			if (board[y-1][x] == 2) {
				board[y][x] = 0;
				y--;
				board[y][x] = 9;
				score += 10;
				power = true;
			}
		}
		
	}
	return 0;
}

bool isPressed( unsigned short inKeyCode ) {
	unsigned char keyMap[16];
	GetKeys((BigEndianUInt32*) &keyMap);
	return (0 != ((keyMap[ inKeyCode >> 3] >> (inKeyCode & 7)) & 1));
}

void clearscreen()
{
	if (!cur_term)
	{
		void *a;
		int result;
		setupterm( NULL, STDOUT_FILENO, &result );
		a = malloc(sizeof(int) *result);
		free (a);
		if (result <= 0) free (a); return;
	}
	putp( tigetstr( "clear" ) );
}

