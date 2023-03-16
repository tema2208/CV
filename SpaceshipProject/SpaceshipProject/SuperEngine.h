#pragma once
#include "Engine.h"

struct SuperEngine : Engine
{
	SuperEngine() = default;
	SuperEngine(int, double);

	int GetSize() const override;
	double GetCost() const override;
	double GetSpeed() const;

	bool CheckEngine(const Frame& frame) const override;
	void SetSpeed(const Frame& frame) override;
	std::string Description() const override;

private:
	// these parameters are needed to calculate the speed
	static constexpr double lowerParameter = static_cast<double> (1) / 12;
	double upperParameter = 0;
	static constexpr double maxSpeed = 1000;
	static constexpr double boundaryNumber = 500;
};

inline int SuperEngine::GetSize() const
{
	return size;
}

inline double SuperEngine::GetCost() const
{
	return cost;
}

inline double SuperEngine::GetSpeed() const
{
	return speed;
}

inline bool SuperEngine::CheckEngine(const Frame& frame) const
{
	if (size < frame.GetSize() * lowerParameter && size > upperParameter * frame.GetSize()) return false;
	return true;
}

inline void SuperEngine::SetSpeed(const Frame& frame)
{
	speed = maxSpeed * size / (upperParameter * frame.GetSize() - lowerParameter * frame.GetSize());
}

inline std::string SuperEngine::Description() const
{
	return "Super Engine: speed = " + std::to_string(speed);
}
