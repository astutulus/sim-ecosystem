#include "Point.h"

Point::Point(float x, float y) : x{ x }, y { y }
{
	
	/*
	* 
	if (x < 0)
		x = 0;
	if (x > getScreenWidth())
		x = getScreenWidth();

	if (y < 2)
		y = 2;
	if (y > getScreenHeight())
		y = getScreenHeight();
		
	*/

}

Point::Point() : Point(0, 0)
{ }
