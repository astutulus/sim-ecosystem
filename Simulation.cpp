#include <math.h>

#include "Simulation.h"
#include "ConsoleGraphics.h"

Point::Point(float x, float y)
{
	if (x >= 0 && x < getScreenWidth() && y >= 2 && y < getScreenHeight())
	{
		this->x = x;
		this->y = y;
	}
	else     // THROW EXCEPTION?
	{
		this->x = 2;
		this->y = 2;
	}
}

Point::Point(int x, int y) : Point((float)x, (float)y)
{
}

Point::Point() : Point(2.0f, 2.0f)
{
}

float DistToPoint(Point start, Point end)
{
	// Gonna be squared so no need to take the absolute
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	return sqrtf(powf(dx, 2.0f) + powf(dy, 2.0f));
}

float AngleToPoint(Point start, Point end)
{
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	return atanf(dy / dx);
}
