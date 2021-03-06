// PROG - MIEIC
// JAS (Header by João N. Matos)
// Header for a library that prints coloured characters on the console (in text mode)
#ifndef COLOUR_WINDOWS_H
#define COLOUR_WINDOWS_H
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

// Functions

//Clears the screen
void clrscr(void);

// Position the cursor at column 'x', line 'y'
// The coordinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y);

// Set text colour
void setcolor(unsigned int color);

// Set text colour and background
void setcolor(unsigned int color, unsigned int background_color);

#endif
//End of file
