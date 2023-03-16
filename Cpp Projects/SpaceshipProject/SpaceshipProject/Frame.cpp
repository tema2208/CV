#include "Frame.h"

Frame::Frame(int n_, double cost_, double armor_)
{
	if (n_ < 0 && armor_ < 0 && cost_ < 0) throw std::exception("Wrong arguments");
	cost = cost_;
	armor = armor_;
	if (n_ == 0) size = 0;
	// this formula from the condition
	else size = static_cast<int>(round(aCoef * pow(2, n_ / 2)));
}