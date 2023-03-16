#pragma once
#include "Engine.h"

struct StandardEngine : Engine
{
	StandardEngine() = default;
	StandardEngine(int, double);

	int GetSize() const override;
	double GetCost() const override;
	double GetSpeed() const;

	bool CheckEngine(const Frame& frame) const override;
	void SetSpeed(const Frame& frame) override;
	std::string Description() const override;

private:
	// these parameters are needed to calculate the speed
	static constexpr  double lowerParameter = static_cast<double> (1) / 12;
	double upperParameter = 0;
	static constexpr double maxSpeed = 100;
	static constexpr double boundaryNumber = 500;
};


inline int StandardEngine::GetSize() const
{
	return size;
}

inline double StandardEngine::GetCost() const
{
	return cost;
}

inline std::string StandardEngine::Description() const
{
	return "Standard Engine: speed = " + std::to_string(speed);
}

inline double StandardEngine::GetSpeed() const
{
	return speed;
}

inline bool StandardEngine::CheckEngine(const Frame& frame) const
{
	if (size < frame.GetSize() * lowerParameter && size > upperParameter * frame.GetSize()) return false;
	return true;
}

inline void StandardEngine::SetSpeed(const Frame& frame)
{
	speed = maxSpeed * size / (upperParameter * frame.GetSize() - lowerParameter * frame.GetSize());
}
