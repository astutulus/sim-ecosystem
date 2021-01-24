
#include "Windows.h"

#include <vector>				// Used as container for Entities

#include "LifeForms.h"			// Entity type is used when printing them to screen
#include "ConsoleGraphics.h"	// So own methods don't have to be in particular order

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
	screen = new wchar_t[ (long long)(nScreenWidth * nScreenHeight) ];
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
	WipeScreenBuffer(); // phase out when rabbit moves and wipes footprints

	for (Entity* ent : getEntities())
	{
		Entity en = *ent;

		short symbol = en.name;
		int x = (int)en.xPos;	// casting from accurate coordinate to ascii screen character position
		int y = (int)en.yPos;	// (ditto)

		screen[y * nScreenWidth + x] = symbol;

	}
	PaintStats();
	screen[nScreenWidth * nScreenHeight - 1] = '\0';
	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}

void PaintStats()
{
	Entity* firstRabbit = new Entity(); // placeholder
	for (Entity* ent : getEntities())
	{
		if (ent->name == 'R')
		{
			firstRabbit = ent;
		}
	}
	swprintf_s(screen, 30, L"Rabbit X=%3.2f, Y=%3.2f", firstRabbit->xPos, firstRabbit->yPos);

}

