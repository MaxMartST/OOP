#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../task_1.2/CVector3D.h"
#include "../task_1.2/pch.h"

using namespace std;

TEST_CASE("Implementation of vector operators")
{
	GIVEN("Two vectors 3D and scalar")
	{
		CVector3D vector1(6, 9, 27);
		CVector3D vector2(28, 34, 75);
		CVector3D vector3;

		double scalar = 2.6;

		WHEN("Sum and subtraction of vectors")
		{
			THEN("Get the total sum vector")
			{
				CVector3D vector4 = vector1 + vector3;
				REQUIRE(vector4.m_x == 6);
				REQUIRE(vector4.m_y == 9);
				REQUIRE(vector4.m_z == 27);

				vector3 = vector1 + vector2;
				REQUIRE(vector3.m_x == 34);
				REQUIRE(vector3.m_y == 43);
				REQUIRE(vector3.m_z == 102);

				vector1 += vector2;
				REQUIRE(vector1.m_x == 34);
				REQUIRE(vector1.m_y == 43);
				REQUIRE(vector1.m_z == 102);
			}

			AND_THEN("Get the total difference vector")
			{
				CVector3D vector4 = vector3 - vector1;
				REQUIRE(vector4.m_x == -6);
				REQUIRE(vector4.m_y == -9);
				REQUIRE(vector4.m_z == -27);

				vector1 -= vector2;
				REQUIRE(vector1.m_x == -22);
				REQUIRE(vector1.m_y == -25);
				REQUIRE(vector1.m_z == -48);
			}
		}

		AND_WHEN("Multiplying and dividing a scalar by a vector")
		{
			THEN("Multiplication result")
			{
				CVector3D vector4 = vector1 * scalar;
				REQUIRE(vector4.m_x == Approx(15.6).epsilon(0.001));
				REQUIRE(vector4.m_y == Approx(23.4).epsilon(0.001));
				REQUIRE(vector4.m_z == Approx(70.2).epsilon(0.001));

				vector4 = scalar * vector2;
				REQUIRE(vector4.m_x == Approx(72.8).epsilon(0.001));
				REQUIRE(vector4.m_y == Approx(88.4).epsilon(0.001));
				REQUIRE(vector4.m_z == Approx(195).epsilon(0.001));

				vector2 *= scalar;
				REQUIRE(vector2.m_x == Approx(72.8).epsilon(0.001));
				REQUIRE(vector2.m_y == Approx(88.4).epsilon(0.001));
				REQUIRE(vector2.m_z == Approx(195).epsilon(0.001));
			}

			AND_THEN("Division result")
			{
				CVector3D vector4 = vector1 / scalar;
				REQUIRE(vector4.m_x == Approx(2.3076923077).epsilon(0.001));
				REQUIRE(vector4.m_y == Approx(3.4615384615).epsilon(0.001));
				REQUIRE(vector4.m_z == Approx(10.3846153846).epsilon(0.001));

				vector2 /= scalar;
				REQUIRE(vector2.m_x == Approx(10.7692300769).epsilon(0.001));
				REQUIRE(vector2.m_y == Approx(13.0769230769).epsilon(0.001));
				REQUIRE(vector2.m_z == Approx(28.8461538461).epsilon(0.001));

				scalar = 0;
				vector4 = vector1 / scalar;
				REQUIRE(vector4.m_x == 6);
				REQUIRE(vector4.m_y == 9);
				REQUIRE(vector4.m_z == 27);
			}
		}

		AND_WHEN("Unary plus and minus")
		{
			CVector3D vector4 = -vector1;
			REQUIRE(vector4.m_x == -6);
			REQUIRE(vector4.m_y == -9);
			REQUIRE(vector4.m_z == -27);
		}

		AND_WHEN("Execute an output statement")
		{
			THEN("Output vector coordinates to the output stream")
			{
				stringstream output;

				output << vector1;
				REQUIRE(output.str() == "6 9 27\n");
			}
		}

		AND_WHEN("Execute input statement")
		{
			THEN("Created vector with specified coordinates")
			{
				stringstream input;
				input << "27.1 5 88.6";
				input >> vector3;

				REQUIRE(vector3.m_x == 27.1);
				REQUIRE(vector3.m_y == 5);
				REQUIRE(vector3.m_z == 88.6);
			}
		}

		AND_WHEN("Find the result of the scalar product of two three-dimensional vectors")
		{
			THEN("Get scalar product")
			{
				REQUIRE(DotProduct(vector1, vector2) == 2499);
			}
		}

		AND_WHEN("Required to find the vector product of two three-dimensional vectors")
		{
			THEN("Get the vector product of two three-dimensional vectors")
			{
				CVector3D resultVector = CrossProduct(vector1, vector2);

				REQUIRE(resultVector.m_x == -243);
				REQUIRE(resultVector.m_y == 306);
				REQUIRE(resultVector.m_z == -48);
			}
		}

		AND_WHEN("Search for a unit vector")
		{
			THEN("Get unit vector")
			{
				CVector3D resultVector = Normalize(vector1);

				REQUIRE(resultVector.m_x == Approx(0.9486832981).epsilon(0.001));
				REQUIRE(resultVector.m_y == Approx(1.4230249471).epsilon(0.001));
				REQUIRE(resultVector.m_z == Approx(4.2690748412).epsilon(0.001));
			}
		}
	}
}