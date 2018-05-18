// PROG - MIEIC
// JAS
// Example of a programme that prints coloured characters on the console (in text mode)

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

//=================================================================================================
//COLOUR CODES: (alternative: use symbolic constants)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

// BACKGROUND COLOR CODES (for better Linux compatibility)
#define BLACK_B			0
#define RED_B			4
#define GREEN_B			2
#define YELLOW_B		14
#define BLUE_B			1
#define MAGENTA_B		5
#define CYAN_B			3
#define WHITE_B			15
//

#define DEFAULT_TEXT 15
#define DEFAULT_BG 0

//=================================================================================================

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; //upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	//fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);

	//cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

//=================================================================================================

// Position the cursor at column 'x', line 'y'
// The coordinates of upper left corner of the screen are (x,y)=(0,0)

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//=================================================================================================

// Set text colour

void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//=================================================================================================

// Set text colour and background

void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

//=================================================================================================

// Fill the screen with coloured numbers
/*
int main()
{
	clrscr();

	srand((unsigned int)time(NULL));

	for (int x = 0; x < 80; x++)
		for (int y = 0; y < 24; y++)
		{
			gotoxy(x, y);
			if (rand() % 2 == 0)
				setcolor(x % 15 + 1);
			else
				setcolor(y % 15 + 1, rand() % 2);
			cout << x % 10;
		}
}
*/

//End of file
