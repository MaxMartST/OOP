#pragma once
#include <cstdint>
#include <iostream>
#include <string>

class IShape
{
public:
	virtual double GetPerimeter() const = 0;
	virtual double GetArea() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;

	virtual ~IShape() = default;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
};
