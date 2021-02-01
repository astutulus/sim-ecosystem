#pragma once

#include <string>
#include "Windows.h"		// HANDLE type


class DisplayObj
{
protected:
	int nScreenWidth, nScreenHeight;

	wchar_t* screen;		// Our buffer for the content of the console
	HANDLE hConsole;		// The Windows console
	DWORD dwBytesWritten;	// Windows not needed

public:
	DisplayObj();

	int getScreenWidth();
	int getScreenHeight();

	void BufferWipe();
	void BufferAddCharacter(char, int, int);
	void BufferAddStats(float);
	// void BufferAddText(std::string);
	void PaintBuffer();

};
