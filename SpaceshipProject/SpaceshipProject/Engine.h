#pragma once
#include "Frame.h"
#include "Modules.h"

struct Engine : Modules
{
	virtual bool CheckEngine(const Frame& frame) const = 0;
	virtual void SetSpeed(const Frame& frame) = 0;

protected:
	double speed = 0;
};

