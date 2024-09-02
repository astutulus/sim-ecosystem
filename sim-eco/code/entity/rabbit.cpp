#include "game-engine.h"
#include "point.h"
#include "rabbit.h"

Rabbit::Rabbit() = default;

Rabbit::Rabbit(Point position)
	: Animal('R', position, f_ENERGY_INIT_RABBIT, 30, n_RABBIT_MAX_SPEED)		// nutrition, sight, maxspeed
{ }



Fox::Fox() = default;

Fox::Fox(Point position)
	: Animal('R', position, f_ENERGY_INIT_RABBIT, 30, n_RABBIT_MAX_SPEED)		// nutrition, sight, maxspeed
{ }
