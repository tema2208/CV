#include "Radar.h"

Radar::Radar(int size_, double cost_, double range_, double detectionForce_)
{
	if(size_ >= 0 && cost_ >= 0 && range_ >= 0 && detectionForce_>= 0)
	{
		size = size_;
		cost = cost_;
		range = range_;
		detectionForce = detectionForce_;
	}
	else throw std::exception("Wrong arguments");
}

