#include "CVector3D.h"

using namespace std;

CVector3D::CVector3D(const double x, const double y, const double z)
	: m_x(x)
	, m_y(y)
	, m_z(z)
{
}

double CVector3D::GetLength() const
{
	return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

void CVector3D::Normalize()
{
	double invLength = GetLength();

	m_x /= invLength;
	m_y /= invLength;
	m_z /= invLength;
}

CVector3D const CVector3D::operator+(CVector3D const& vector3d) const
{
	return CVector3D(m_x + vector3d.m_x, m_y + vector3d.m_y, m_z + vector3d.m_z);
}

CVector3D const CVector3D::operator-(CVector3D const& vector3d) const
{
	return CVector3D(m_x - vector3d.m_x, m_y - vector3d.m_y, m_z - vector3d.m_z);
}

CVector3D const CVector3D::operator*(double scalar) const
{
	return CVector3D(m_x * scalar, m_y * scalar, m_z * scalar);
}

CVector3D const operator*(double scalar, CVector3D const& vector3d)
{
	return CVector3D(scalar * vector3d.m_x, scalar * vector3d.m_y, scalar * vector3d.m_z);
}

CVector3D const CVector3D::operator/(double scalar) const
{
	if (scalar != 0)
	{
		return CVector3D(m_x / scalar, m_y / scalar, m_z / scalar);
	}

	return *this;
}

CVector3D const CVector3D::operator-() const
{
	return CVector3D(-m_x, -m_y, -m_z);
}

CVector3D const CVector3D::operator+() const
{
	return *this;
}

CVector3D& CVector3D::operator+=(CVector3D const& vector3d)
{
	m_x += vector3d.m_x;
	m_y += vector3d.m_y;
	m_z += vector3d.m_z;

	return *this;
}

CVector3D& CVector3D::operator-=(CVector3D const& vector3d)
{
	m_x -= vector3d.m_x;
	m_y -= vector3d.m_y;
	m_z -= vector3d.m_z;

	return *this;
}

CVector3D& CVector3D::operator*=(double scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;

	return *this;
}

CVector3D& CVector3D::operator/=(double scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;

	return *this;
}

bool CVector3D::operator==(CVector3D const& vector3d) const
{
	return (m_x == vector3d.m_x) && (m_y == vector3d.m_y) && (m_z == vector3d.m_z);
}

bool CVector3D::operator!=(CVector3D const& vector3d) const
{
	return !(*this == vector3d);
}

ostream& operator<<(ostream& stream, CVector3D const& vector3d)
{
	stream << vector3d.m_x << " " << vector3d.m_y << " " << vector3d.m_z << "\n";
	return stream;
}

istream& operator>>(istream& stream, CVector3D& vector3d)
{
	double x, y, z;

	if ((stream >> x) && (stream >> y) && (stream >> z))
	{
		vector3d = CVector3D(x, y, z);
	}
	else
	{
		stream.setstate(ios_base::failbit | stream.rdstate());
	}

	return stream;
}

double const DotProduct(CVector3D const& vector3d1, CVector3D const& vector3d2)
{
	return vector3d1.m_x * vector3d2.m_x + vector3d1.m_y * vector3d2.m_y + vector3d1.m_z * vector3d2.m_z;
}

double const GetVectorValue(double arg1, double arg2, double arg3, double arg4)
{
	return (arg1 * arg2 - arg3 * arg4);
}

CVector3D const CrossProduct(CVector3D const& vector3d1, CVector3D const& vector3d2)
{
	double x = GetVectorValue(vector3d1.m_y, vector3d2.m_z, vector3d1.m_z, vector3d2.m_y);
	double y = GetVectorValue(vector3d1.m_z, vector3d2.m_x, vector3d1.m_x, vector3d2.m_z);
	double z = GetVectorValue(vector3d1.m_x, vector3d2.m_y, vector3d1.m_y, vector3d2.m_x);

	return CVector3D(x, y, z);
}

CVector3D Normalize(CVector3D const& vector3d)
{
	double length = vector3d.GetLength();

	return CVector3D(vector3d.m_x / length, vector3d.m_y / length, vector3d.m_z / length);
}