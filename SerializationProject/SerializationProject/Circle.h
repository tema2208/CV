#pragma once
#include <boost/smart_ptr/make_shared_object.hpp>

#include "GeometryObj.h"
#include "Vector2d.h"

struct Circle : GeometryObj
{
	Circle(const Vector2d& l, double r, std::string n) :
		GeometryObj(std::move(n)), location(l), radius(r)
	{}
	Circle(const Vector2d& l, double r) :
		location(l), radius(r)
	{}
	Circle() = default;

	Vector2d GetLoc() const { return location; }
	double GetRadius() const { return radius; }

	boost::shared_ptr<GeometryObj> Clone() const override
	{
		return boost::make_shared<Circle>(*this);
	}

private:
	Vector2d location{};
	double radius = 0;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<GeometryObj>(*this);
		ar& location;
		ar& radius;
	}

	std::string Description() const override
	{
		return "Circle: location = " + location.ToString() + " radius = " + std::to_string(radius);
	}
};
