#include <iostream>
#define LOG(x) std::cout << x << std::endl;

/*
* ------------------------------
* Simulated Ecosystem in Console
* ------ by Robin Wootton ------
* ------------------------------
*
* To do:-
* 
*/

#include "Windows.h"	// GetAsyncKeyState()

#include <chrono>		// std::chrono::system_clock::now(), std::chrono::duration<>
#include <random>		// rand()

#include "ConsoleGraphics.h"	// CreateScreenBuffer(), PaintScreenBuffer()
#include "LifeForms.h"		// addGrass(), addRabbit()


int main()
{
	/*
	* Global - Time
	*/
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();
	auto tpLastKeyPress = std::chrono::system_clock::now();

	/*
	* Initialise world
	*/
	CreateScreenBuffer();

	addGrass(30, 10);
	addGrass(90, 12);
	addRabbit(5, 5, 4);

	/*
	* Game Loop
	*/
	bool running = true;
	while (running)
	{
		// CONTROL
		// Add random grass
		if (GetAsyncKeyState((unsigned short)'G') & 0x8000)
		{
			auto tpPresentKeyPress = std::chrono::system_clock::now();

			std::chrono::duration<float> timeSinceLast = tpPresentKeyPress - tpLastKeyPress;
			float fElapsedTime = timeSinceLast.count(); // timeSinceLast has "seconds" after it!
			if (fElapsedTime > 1)
			{
				int randomX = rand() % getScreenWidth(); // e.g.  rand() % 100;   uses the range 0 to 99 
				int randomY = rand() % getScreenHeight();

				addGrass(randomX, randomY);
				tpLastKeyPress = std::chrono::system_clock::now();
			}
		}

		WipeScreenBuffer(); // phase out when rabbit moves and wipes footprints
		PaintScreenBuffer();

	}

	std::cin.get();
}