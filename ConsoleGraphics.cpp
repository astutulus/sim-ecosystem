
#include "Windows.h"

#include <vector>			// Used as container for Entities

#include "LifeForms.h"		// Entity type is used when printing them to screen

/*
Screen Buffer dimensions
*/
int nScreenWidth = 120;
int nScreenHeight = 30;

wchar_t* screen;		// Our buffer for the content of the console
HANDLE hConsole;		// The Windows console
DWORD dwBytesWritten;	// Windows not needed

/*
Accessors
*/
int getScreenWidth()
{
	return nScreenWidth;
}

int getScreenHeight()
{
	return nScreenHeight;
}

void CreateScreenBuffer()
{
	screen = new wchar_t[nScreenWidth * nScreenHeight];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
}


void WipeScreenBuffer()
{
	for (int x = 0; x < nScreenWidth; x++)
	{
		for (int y = 0; y < nScreenHeight; y++)
		{
			screen[y * nScreenWidth + x] = ' ';
		}
	}
}


void PaintScreenBuffer()
{

	for (Entity* ent : getEntities())
	{
		Entity en = *ent;

		short symbol = en.name;
		int x = (int)en.xPos;	// casting from accurate coordinate to ascii screen character position
		int y = (int)en.yPos;	// (ditto)

		screen[y * nScreenWidth + x] = symbol;

	}

	screen[nScreenWidth * nScreenHeight - 1] = '\0';
	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}
