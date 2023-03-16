#pragma once
#include <algorithm>
#include <cmath>
#include <ostream>
#include <string>
#include <boost/serialization/access.hpp>

struct Vector2d
{
	Vector2d(double x, double y) :
		x(x), y(y)
	{}
	Vector2d() = default;

	double operator*(const Vector2d& v) const
	{
		return x * v.x + y * v.y;
	}
	Vector2d operator+(const Vector2d& v) const
	{
		return { x + v.x, y + v.y };
	}
	Vector2d operator-(const Vector2d& v) const
	{
		return { x - v.x, y - v.y };
	}

	double GetLength() const
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	bool IsCollinear(const Vector2d& v) const
	{
		// comparison as in Qt
		return abs(x / y - v.x / v.y) <= 0.000000000001 * std::min(abs(x / y), abs(v.x / v.y));
	}
	bool IsRightHandedOrientation(const Vector2d& v) const
	{
		return x * v.y - y * v.x >= 0;
	}
	double CrossProductLen(const Vector2d& v) const
	{
		return abs(x * v.y - y * v.x);
	}
	std::string ToString() const
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
	double GetX() const { return x; }
	double GetY() const { return y; }

private:
	double x = 0;
	double y = 0;

	friend std::ostream& operator<<(std::ostream& os, const Vector2d& v);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& x& y;
	}
};

inline std::ostream& operator<<(std::ostream& os, const Vector2d& v)
{
	return os << v.ToString() << std::endl;
}