#include "LivingModule.h"

LivingModule::LivingModule(int size_, double cost_)
{
	if (size_ >= 0 && cost_ >= 0)
	{
		size = size_;
		cost = cost_;
	}
	else throw std::exception("Wrong arguments");
}