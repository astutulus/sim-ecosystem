
#include "GameEngine.h"
#include "Point.h"
#include "Grass.h"

Grass::Grass() = default;

Grass::Grass(Point position)
	: Plant('G', position, f_ENERGY_INIT_GRASS)
{ }
