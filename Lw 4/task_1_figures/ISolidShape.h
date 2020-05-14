#pragma once
#include "IShape.h"
#include <stdint.h>

class ISolidShape : public IShape
{
public:
	virtual double GetArea() const = 0;
	virtual uint32_t GetFillColor() const = 0;
};
