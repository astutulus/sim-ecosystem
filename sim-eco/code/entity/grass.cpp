#include "game-engine.h"
#include "point.h"
#include "grass.h"

Grass::Grass() = default;

Grass::Grass(Point position)
	: Plant('G', position, f_ENERGY_INIT_GRASS)
{ }
