#include "Point.h"

Point::Point(float x, float y)
{

	/*
	* TO DO -- check legal w.r.t. screen dims. Hmmm. Need comm with console-display class.

	if (x >= 0 && x < getScreenWidth() && y >= 2 && y < getScreenHeight())
	{
	}

	*/

	this->x = x;
	this->y = y;
}

Point::Point() : Point(0, 0)
{ }
