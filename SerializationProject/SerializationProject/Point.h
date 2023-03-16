#pragma once
#include <boost/serialization/shared_ptr.hpp>

#include "GeometryObj.h"
#include "Vector2d.h"

struct Point : GeometryObj
{
	Point(double x, double y, std::string n) :
		GeometryObj(std::move(n)), location(x, y)
	{}
	Point(const Vector2d& v) :
		location(v)
	{}
	Point(double x = 0, double y = 0) :
		location(x, y)
	{}

	Vector2d GetLoc() const { return location; }

	boost::shared_ptr<GeometryObj> Clone() const override
	{
		return boost::make_shared<Point>(*this);
	}

private:
	Vector2d location{};

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<GeometryObj>(*this);
		ar& location;
	}

	std::string Description() const override
	{
		return "Point: location = " + location.ToString();
	}
};
