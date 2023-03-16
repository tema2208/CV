#pragma once
#include <boost/smart_ptr/make_shared_object.hpp>

#include "GeometryObj.h"
#include "Point.h"
#include "Vector2d.h"

struct Line : GeometryObj
{
	Line(const Vector2d& l, const Vector2d& d, std::string n) :
		GeometryObj(std::move(n)), location(l), direction(d)
	{}
	Line(const Vector2d& l, const Vector2d& d) :
		location(l), direction(d)
	{}
	Line() = default;

	Vector2d GetPerpendicularVector(const Point& point) const;

	Vector2d GetLoc() const { return location; }
	Vector2d GetDir() const { return direction; }

	boost::shared_ptr<GeometryObj> Clone() const override
	{
		return boost::make_shared<Line>(*this);
	}

private:
	Vector2d location{};
	Vector2d direction{};
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<GeometryObj>(*this);
		ar& location;
		ar& direction;
	}

	std::string Description() const override
	{
		return "Line: location = " + location.ToString() + " direction = " + direction.ToString();
	}
};
