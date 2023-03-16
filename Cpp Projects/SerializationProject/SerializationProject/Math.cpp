#include "Math.h"

double Math::GetDistance(const Point& p1, const Point& p2)
{
	return (p1.GetLoc() - p2.GetLoc()).GetLength();
}

double Math::GetDistance(const Point& point, const Line& line)
{
	Vector2d vBetweenPoints = point.GetLoc() - line.GetLoc();
	if (line.GetDir().IsCollinear(vBetweenPoints)) return 0;
	return vBetweenPoints.CrossProductLen(line.GetDir()) / line.GetDir().GetLength();
}

double Math::GetDistance(const Point& point, const Circle& circle)
{
	double dist = (point.GetLoc() - circle.GetLoc()).GetLength();
	return dist >= circle.GetRadius() ? dist - circle.GetRadius() : circle.GetRadius() - dist;
}

double Math::GetDistance(const Point& point, const Ellipse& ellipse)
{
	Vector2d vector = point.GetLoc() - ellipse.GetLoc();
	double angle = ellipse.GetAngleWithMajorAxis(vector);
	Point tmpPoint = ellipse.GetPointOnEllipse(angle);
	return GetDistance(tmpPoint, point);
}

double Math::GetDistance(const Line& line1, const Line& line2)
{
	if (line1.GetDir().IsCollinear(line2.GetDir())) return GetDistance(line1.GetLoc(), line2);
	return 0;
}

double Math::GetDistance(const Line& line, const Circle& circle)
{
	double dist = GetDistance(circle.GetLoc(), line);
	return dist > 0 ? dist : 0;
}

double Math::GetDistance(const Line& line, const Ellipse& ellipse)
{
	Vector2d vector = line.GetPerpendicularVector(ellipse.GetLoc());
	double angle = ellipse.GetAngleWithMajorAxis(vector);
	Point tmpPoint = ellipse.GetPointOnEllipse(angle);
	Point perpendicularPoint = { vector + ellipse.GetLoc() };
	return GetDistance(tmpPoint, perpendicularPoint);
}

double Math::GetDistance(const Circle& circle1, const Circle& circle2)
{
	Vector2d vector = circle1.GetLoc() - circle2.GetLoc();
	double dist = vector.GetLength() - circle1.GetRadius() - circle2.GetRadius();
	return dist > 0 ? dist : 0;
}