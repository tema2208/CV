#pragma once
#include <boost/smart_ptr/make_shared_object.hpp>

#include "GeometryObj.h"
#include "Point.h"
#include "Vector2d.h"

struct Ellipse : GeometryObj
{
	Ellipse(const Vector2d& l, const Vector2d& d, double majorAxis, double minorAxis, std::string n) :
		GeometryObj(std::move(n)), location(l), majorAxisDir(d), majorAxis(majorAxis), minorAxis(minorAxis)
	{}
	Ellipse(const Vector2d& l, const Vector2d& d, double majorAxis, double minorAxis) :
		location(l), majorAxisDir(d), majorAxis(majorAxis), minorAxis(minorAxis)
	{}
	Ellipse() = default;

	//this angle strict counterclockwise
	double GetRotationAngle() const;

	//calculate in polar coordinates
	Point GetPointOnEllipse(double angle) const;

	double GetAngleWithMajorAxis(const Vector2d& vector) const;

	Vector2d GetLoc() const { return location; }
	Vector2d GetAxisDir() const { return majorAxisDir; }
	double GetMajorAxis() const { return majorAxis; }
	double GetMinorAxis() const { return minorAxis; }

	boost::shared_ptr<GeometryObj> Clone() const override
	{
		return boost::make_shared<Ellipse>(*this);
	}
private:
	Vector2d location{};
	Vector2d majorAxisDir{};
	double majorAxis = 0;
	double minorAxis = 0;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& boost::serialization::base_object<GeometryObj>(*this);
		ar& location& majorAxisDir;
		ar& majorAxis& minorAxis;
	}

	std::string Description() const override
	{
		return "Ellipse: location = " + location.ToString() + " major axis = " + std::to_string(majorAxis) + " minor axis = " + std::to_string(minorAxis);
	}
};
