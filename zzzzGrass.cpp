
#include "GameEngine.h"
#include "Point.h"
#include "zzzzGrass.h"

Grass::Grass() = default;

Grass::Grass(Point position)
	: Plant('G', position, f_ENERGY_INIT_GRASS)
{ }
