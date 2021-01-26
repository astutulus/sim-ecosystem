#pragma once

#include "Windows.h"		// HANDLE type

#include <chrono>			// std::chrono::system_clock::now(), std::chrono::duration<>

class GameObj
{
public:
	int nScreenWidth, nScreenHeight;

	wchar_t* screen;		// Our buffer for the content of the console
	HANDLE hConsole;		// The Windows console
	DWORD dwBytesWritten;	// Windows not needed

	std::chrono::system_clock::time_point tpLastLoopStart;
	std::chrono::system_clock::time_point tpThisLoopStart;

	GameObj();

	int getScreenWidth();
	int getScreenHeight();

	void BufferWipe();
	void BufferAddCharacter(char, int, int);
	void BufferAddStats(float);
	void BufferPaint();

	float LatestLoopTime();
};
