#pragma once
#include <ostream>

struct Modules
{
	virtual ~Modules() = default;
	virtual int GetSize() const = 0;
	virtual double GetCost() const = 0;

	bool IsEmpty() const
	{
		if (size == 0) return true;
		return false;
	}

	virtual std::string Description() const = 0;

protected:
	friend std::ostream& operator<<(std::ostream&, const Modules&);
	int size = 0;
	double cost = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Modules& m)
{
	if (m.IsEmpty()) os << "This module is missing" << std::endl;
	else os << m.Description() << ", size = " << m.size << ", cost = " << m.cost << std::endl;
	return os;
}
