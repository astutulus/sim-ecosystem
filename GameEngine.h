#pragma once

#include <vector>
#include <random>					// rand()
#include <chrono>					// std::chrono::system_clock::now(), std::chrono::duration<>

#include "DisplayEngine.h"
#include "zEntity.h"
#include "zzzPlant.h"
#include "zzzzRabbit.h"

/*
Constants for tuning game balance
*/
const float f_GRASS_SEED_RATE = 0.1f; // seconds per plant

const float f_ENERGY_INIT_GRASS = 0.9f;
const float f_ENERGY_INIT_RABBIT = 2.8f;

const float f_ENERGY_TRANSFER_LOOKING = 0.3f;
const float f_ENERGY_TRANSFER_WALKING = 0.5f;
const float f_ENERGY_TRANSFER_EATING = 2.4f;

const int n_RABBIT_MAX_SPEED = 8;


class EcoSim {
protected:
	std::chrono::system_clock::time_point tpLastKeyPress;
	std::chrono::system_clock::time_point tpLastLoopStart;
	std::chrono::system_clock::time_point tpThisLoopStart;
	float looptime;
	
	DisplayObj* display;

	std::vector<Plant*> plants;
	std::vector<Animal*> animals;

public:
	EcoSim();

	void SpawnGrass();
	void SpawnGrass(int x, int y);
	void SpawnRabbit();
	void SpawnRabbit(int x, int y);

	bool IsKeyPressed(char);
	void UpdateLoopTime();
	bool AninalAcivity();
	bool PlantAcivity();

	void DrawAll();

private:
	float GetLoopTime();
	void BufferActor(Entity*);
};