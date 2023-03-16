#include "Ellipse.h"

double Ellipse::GetRotationAngle() const
{
	double angle = acos(Vector2d(1, 0) * majorAxisDir / majorAxisDir.GetLength());
	return Vector2d(1, 0).IsRightHandedOrientation(majorAxisDir) ? angle : 2 * M_PI - angle;
}

Point Ellipse::GetPointOnEllipse(double angle) const
{
	double rotationAngle = GetRotationAngle();
	double xTmp = (majorAxis * cos(angle) + location.GetX()) * cos(rotationAngle) -
		(minorAxis * sin(angle) + location.GetY()) * sin(rotationAngle);
	double yTmp = (majorAxis * cos(angle) + location.GetX()) * sin(rotationAngle) +
		(minorAxis * sin(angle) + location.GetY()) * cos(rotationAngle);

	return { xTmp, yTmp };
}

double Ellipse::GetAngleWithMajorAxis(const Vector2d& vector) const
{
	double angle = acos(vector * majorAxisDir / (vector.GetLength() * majorAxisDir.GetLength()));
	angle = majorAxisDir.IsRightHandedOrientation(vector) ? angle : 2 * M_PI - angle;
	return angle;
}