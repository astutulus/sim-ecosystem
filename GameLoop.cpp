/*
* ------------------------------
* Simulated Ecosystem in Console
* ------ by Robin Wootton ------
* ------------------------------
*/

#include <iostream>
#include <string>

#include "GameEngine.h"
#include "GameEngine.h"

int main()
{
	EcoSim* eco = new EcoSim();

	eco->SpawnGrass(40, 5);
	eco->SpawnGrass(20, 10);
	eco->SpawnRabbit(50, 15);

	/*
	* GAME LOOP
	*/
	bool running = true;
	while (running)
	{
		/*
		TIMING
		*/
		eco->UpdateLoopTime();

		/*
		CONTROL
		*/
		if (eco->IsKeyPressed('G'))
			eco->SpawnGrass();

		if (eco->IsKeyPressed('R'))
			eco->SpawnRabbit();

		/*
		RUN SIMULATION
		*/
		if (!(eco->AninalAcivity()))
			running = false;

		eco->PlantAcivity();

		/*
		* DRAW
		*/
		if (running)
			eco->DrawAll();			
	}
	
	/*while (true)
	{
		std::string str = "You ran out of energy";
		cons->BufferAddText(str);
	}*/
}