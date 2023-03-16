#include "StandardEngine.h"

StandardEngine::StandardEngine(int size_, double cost_)
{
	if (size_ >= 0 && cost_ >= 0)
	{
		size = size_;
		cost = cost_;
		// for an expensive engine
		if (cost > boundaryNumber) upperParameter = static_cast<double> (1) / 4;
		// for cheap engine
		else upperParameter = static_cast<double> (1) / 2;
	}
	else throw std::exception("Wrong arguments");
}
