#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../task_1.2/CVector3D.h"
#include "../task_1.2/CompareTwoDouble.h"
#include "../task_1.2/pch.h"

using namespace std;

TEST_CASE("Implementation of vector operators")
{
	GIVEN("3D initialized vectors available")
	{
		CVector3D vector1(3.2, 2.1, 1);
		CVector3D vector2(4.5, 6.7, 8.9);
		CVector3D result;

		WHEN("Normalization of a vector using a method")
		{
			vector1.Normalize();

			THEN("This 3d vector is normalized")
			{
				REQUIRE(IsEqual(vector1.m_x, 0.80889622266489380));
				REQUIRE(IsEqual(vector1.m_y, 0.53083814612383662));
				REQUIRE(IsEqual(vector1.m_z, 0.25278006958277932));
			}

			AND_THEN("Vector normalization")
			{
				CVector3D vector3(0, 5, 0);
				vector3.Normalize();
				REQUIRE(vector3 == CVector3D(0, 1, 0));
			}
		}

		AND_WHEN("Normalizing a vector with a function")
		{
			result = Normalize(vector1);

			THEN("This 3d vector is normalized")
			{
				REQUIRE(IsEqual(result.m_x, 0.80889622266489380));
				REQUIRE(IsEqual(result.m_y, 0.53083814612383662));
				REQUIRE(IsEqual(result.m_z, 0.25278006958277932));
			}
		}

		WHEN("Use unary minus")
		{
			result = -vector1;

			THEN("Return a vector with the opposite direction")
			{
				REQUIRE(result.m_x == -3.2);
				REQUIRE(result.m_y == -2.1);
				REQUIRE(result.m_z == -1);
			}
		}

		AND_WHEN("Use unary plus")
		{
			result = +vector2;

			THEN("Return a vector with the opposite direction")
			{
				REQUIRE(result.m_x == 4.5);
				REQUIRE(result.m_y == 6.7);
				REQUIRE(result.m_z == 8.9);
			}
		}

		WHEN("Use binary plus")
		{
			result = vector1 + vector2;

			THEN("The result is the sum of the vectors")
			{
				REQUIRE(result.m_x == 7.7);
				REQUIRE(result.m_y == 8.8);
				REQUIRE(result.m_z == 9.9);
			}
		}

		AND_WHEN("Use binary minus")
		{
			result = vector1 - vector2;

			THEN("The result is the difference of vectors")
			{
				REQUIRE(result.m_x == -1.3);
				REQUIRE(result.m_y == -4.6);
				REQUIRE(result.m_z == -7.9);
			}
		}

		WHEN("Increase vector length by second vector length")
		{
			THEN("Increased vector result")
			{
				CVector3D vector3(1, 0, 0);
				CVector3D vector4(1, 0, 0);

				(vector3 += vector4) += vector4;
				REQUIRE(vector3 == CVector3D(3, 0, 0));
			}
		}

		AND_WHEN("Reduce vector length by second vector length")
		{
			THEN("Reduced vector result")
			{
				CVector3D vector3(5, 0, 0);
				CVector3D vector4(2, 0, 0);

				(vector3 -= vector4) -= vector4;
				REQUIRE(vector3 == CVector3D(1, 0, 0));
			}
		}

		WHEN("Operations with a scalar")
		{
			CVector3D vector3(2, 4, 6);

			result = (vector3 * 2) / 4;
			REQUIRE(result == CVector3D(1, 2, 3));
			REQUIRE((3 * result) == CVector3D(3, 6, 9));

			result *= 3;
			REQUIRE(result == CVector3D(3, 6, 9));

			(result /= 3) *= 2;
			REQUIRE(result == CVector3D(2, 4, 6));
		}

		WHEN("Vector comparison")
		{
			CVector3D vector3(2, 4, 6);
			CVector3D vector4(1, 2, 3);

			REQUIRE(vector3 != vector4);

			vector4 *= 2;
			REQUIRE(vector3 == vector4);
		}

		WHEN("Correct data input into the vector")
		{
			stringstream input;
			input << "9.1 8.2 7.3";
			input >> result;

			THEN("Get 3D vector")
			{
				REQUIRE(IsEqual(result.m_x, 9.1));
				REQUIRE(IsEqual(result.m_y, 8.2));
				REQUIRE(IsEqual(result.m_z, 7.3));
			}
		}

		AND_WHEN("Incorrect data input into the vector")
		{
			stringstream input;
			ios_base::iostate oldState = input.rdstate();
			input << "9.1 8.2";
			input >> result;

			THEN("Change thread state to failbit")
			{
				REQUIRE_FALSE(oldState == input.rdstate());
			}
		}

		AND_WHEN("3d vector content output")
		{
			stringstream output;
			output << vector1;

			REQUIRE(output.str() == "3.2 2.1 1\n");
		}

		WHEN("Computes the result of the scalar product of two 3d vectors")
		{
			double resultProd = DotProduct(vector1, vector2);

			THEN("Get the scalar product of two 3d vectors")
			{
				REQUIRE(resultProd == 37.37);
			}
		}

		WHEN("Calculate the result of a vector product of two 3d vectors")
		{
			result = CrossProduct(vector1, vector2);

			THEN("Get the result of a vector product of two 3d vectors")
			{
				REQUIRE(IsEqual(result.m_x, 11.99));
				REQUIRE(IsEqual(result.m_y, -23.98));
				REQUIRE(IsEqual(result.m_z, 11.99));
			}
		}
	}
}