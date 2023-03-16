#pragma once
#define M_PI

#include <boost/archive/text_oarchive.hpp>

#include <ostream>
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

struct GeometryObj
{
	GeometryObj() = default;
	virtual ~GeometryObj() = default;

	std::string GetName() const { return name; }

	virtual boost::shared_ptr<GeometryObj> Clone() const = 0;

protected:
	GeometryObj(std::string n) :
		name(std::move(n))
	{}

private:
	std::string name;
	friend std::ostream& operator<<(std::ostream& os, const GeometryObj& go);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& name;
	}

	virtual std::string Description() const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const GeometryObj& go)
{
	return os << go.Description() << ' ' << "name " << go.name << ' ' << std::endl;
}

inline bool IsZero(double info)
{
	return abs(info) <= 0.000000000001;
}