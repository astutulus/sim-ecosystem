#pragma once


class Point
{
public:
	float x, y;
	Point(float, float);
	Point(int, int);
	Point();
};

float DistToPoint(Point, Point);

float AngleToPoint(Point, Point);