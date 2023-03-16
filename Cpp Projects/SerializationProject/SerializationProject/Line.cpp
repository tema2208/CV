#include "Line.h"

Vector2d Line::GetPerpendicularVector(const Point& point) const
{
	if (IsZero(direction.GetX())) return { location.GetX() - point.GetLoc().GetX(), 0 };
	if (IsZero(direction.GetY())) return { 0, location.GetY() - point.GetLoc().GetY() };
	double y = (location.GetY() * pow(direction.GetX(), 2) - location.GetX() * direction.GetY() + point.GetLoc().GetX() * direction.GetX() * direction.GetY() +
		point.GetLoc().GetY() * pow(direction.GetY(), 2)) / (pow(direction.GetX(), 2) + pow(direction.GetY(), 2));
	double x = direction.GetX() * (y - location.GetY()) / direction.GetY() + location.GetX() / direction.GetX();
	return { x - point.GetLoc().GetX(), y - point.GetLoc().GetY() };
}