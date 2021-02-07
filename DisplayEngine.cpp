#include "Windows.h"
#include <chrono>			// std::chrono::system_clock::now(), std::chrono::duration<>

#include "DisplayEngine.h"

DisplayObj::DisplayObj()
{
	nScreenWidth = 120;
	nScreenHeight = 30;
	screen = new wchar_t[  nScreenWidth * nScreenHeight  ];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	dwBytesWritten = 0;
};

int DisplayObj::getScreenWidth()
{
	return nScreenWidth;
}
int DisplayObj::getScreenHeight()
{
	return nScreenHeight;
}

void DisplayObj::BufferWipe()
{
	for (int x = 0; x < nScreenWidth; x++)
	{
		for (int y = 0; y < nScreenHeight; y++)
		{
			screen[y * nScreenWidth + x] = ' ';
		}
	}
}

void DisplayObj::BufferAddCharacter(char symbol, int x, int y)
{

	short nShade = ' ';  
	
	if (symbol == 'G')
	{
		nShade = 0x2591;    // dark
		//nShade = 0x2592;    // medium
		//nShade = 0x2593;    // light
		//nShade = 0x2588;    // solid white
	}
	else if (symbol == 'R')
	{
		nShade = 0x2022;
	}
	screen[y * nScreenWidth + x] = nShade;
}

void DisplayObj::BufferAddStats(float energy)
{
	swprintf_s(screen, 25, L"Rabbit: Energy=%3.2f", energy);
}

//void DisplayObj::BufferAddText(std::string msg)
//{
//	COORD pos;
//	pos.X = getScreenWidth() / 2;
//	pos.Y = getScreenHeight() / 2;
//	SetConsoleCursorPosition(hConsole, pos);
//
//	WriteConsole(hConsole, msg.c_str(), 21, NULL, NULL);
//
//}

void DisplayObj::PaintBuffer()
{
	screen[nScreenWidth * nScreenHeight - 1] = '\0';
	WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0, 0 }, &dwBytesWritten);
}

