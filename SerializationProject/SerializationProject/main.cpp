#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>



#include "Circle.h"
#include "Ellipse.h"
#include "GeometryObj.h"
#include "Line.h"
#include "Math.h"
#include "Point.h"
#include "Vector2d.h"


struct GeometryObjInfo
{
	using goPtr = boost::shared_ptr<GeometryObj>;

	GeometryObjInfo(const GeometryObj& go1_, const GeometryObj& go2_, double d) :
		dist(d)
	{
		go1 = go1_.Clone();
		go2 = go2_.Clone();
	}
	GeometryObjInfo() = default;

private:
	goPtr go1;
	goPtr go2;
	double dist = 0;

	friend std::ostream& operator <<(std::ostream& os, const GeometryObjInfo& go);
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar.register_type(static_cast<Point*>(nullptr));
		ar.register_type(static_cast<Line*>(nullptr));
		ar.register_type(static_cast<Circle*>(nullptr));
		ar.register_type(static_cast<Ellipse*>(nullptr));
		ar& go1;
		ar& go2;
		ar& dist;
	}
};

std::ostream& operator<<(std::ostream& os, const GeometryObjInfo& go)
{
	os << "------------------------------------" << std::endl;
	return os << *go.go1 << *go.go2 << "dist = " << go.dist << std::endl;
}

struct Module
{
	Module() = default;

	void Append(const GeometryObjInfo& goInfo)
	{
		info.insert(info.end(), goInfo);
	}

private:
	std::list<GeometryObjInfo> info;

	friend class boost::serialization::access;
	friend std::ostream& operator<<(std::ostream& os, const Module& m);
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& info;
	}
};

std::ostream& operator<<(std::ostream& os, const Module& m)
{
	for (auto it = m.info.begin(); it != m.info.end(); ++it) {
		os << *it;
	}
	return os;
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(GeometryObj)

void SaveInformation(const Module& m, const char* filename) {
	// make an archive
	std::ofstream ofs(filename);
	boost::archive::text_oarchive oa(ofs);
	oa << m;
}

void RestoreInformation(Module& m, const char* filename)
{
	// open the archive
	std::ifstream ifs(filename);
	boost::archive::text_iarchive ia(ifs);
	// restore the schedule from the archive
	ia >> m;
}


int main()
{
	Math m;
	Point p1 = Point(0, 5);
	Line l1 = Line(Vector2d(1, 1), Vector2d(2, 2), "line1");
	Circle c1 = Circle(Vector2d(1, 1), 5, "circle1");
	Ellipse el1 = Ellipse(Vector2d(1, 1), Vector2d(1, 0), 1, 1, "ellipse1");

	GeometryObjInfo info1 = GeometryObjInfo(p1, l1, m.GetDistance(p1, l1));
	GeometryObjInfo info2 = GeometryObjInfo(p1, el1, m.GetDistance(p1, el1));
	GeometryObjInfo info3 = GeometryObjInfo(el1, p1, m.GetDistance(p1, el1));
	GeometryObjInfo info4 = GeometryObjInfo(l1, c1, m.GetDistance(l1, c1));

	Module module;

	module.Append(info1);
	module.Append(info2);
	module.Append(info3);
	module.Append(info4);

	std::cout << module << std::endl;
	std::string filename = "testData.json";

	SaveInformation(module, filename.c_str());

	Module newModule{};
	RestoreInformation(newModule, filename.c_str());

	std::cout << newModule;

	return 0;
}