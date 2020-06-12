#pragma once
#include "IShape.h"
#include <stdint.h>
#include <cstdint>

class ISolidShape : public IShape
{
public:
	double GetArea() const = 0;
	virtual uint32_t GetFillColor() const = 0;
};
