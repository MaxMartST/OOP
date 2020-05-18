#pragma once
#include <iostream>

class CVector3D
{
public:
	CVector3D() = default;
	CVector3D(double x, double y, double z);
	
	double GetLength() const;
	void Normalize();

	CVector3D const operator+(CVector3D const& vector3d) const;
	CVector3D const operator-(CVector3D const& vector3d) const;
	CVector3D const operator*(double scalar) const;
	CVector3D const operator/(double scalar) const;
	CVector3D const operator-() const;
	CVector3D const operator+() const;
	CVector3D operator+=(CVector3D const& vector3d);
	CVector3D operator-=(CVector3D const& vector3d);
	CVector3D operator*=(double scalar);
	CVector3D operator/=(double scalar);
	bool operator==(CVector3D const& vector3d) const;
	bool operator!=(CVector3D const& vector3d) const;

	double m_x = 0, m_y = 0, m_z = 0;
};

CVector3D const operator*(double scalar, CVector3D const& vector3d);

std::ostream& operator<<(std::ostream & stream, CVector3D const& vector3d);
std::istream& operator>>(std::istream& stream, CVector3D& vector3d);

double const DotProduct(CVector3D const& vector3d1, CVector3D const& vector3d2);
CVector3D const CrossProduct(CVector3D const& vector3d1, CVector3D const& vector3d2);
CVector3D Normalize(CVector3D const& vector3d);