#pragma once
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Point.h"


struct Math
{
	double GetDistance(const Point& p1, const Point& p2);

	double GetDistance(const Point& point, const Line& line);

	double GetDistance(const Point& point, const Circle& circle);

	double GetDistance(const Point& point, const Ellipse& ellipse);

	double GetDistance(const Line& line1, const Line& line2);

	double GetDistance(const Line& line, const Circle& circle);

	double GetDistance(const Line& line, const Ellipse& ellipse);

	double GetDistance(const Circle& circle1, const Circle& circle2);
};
