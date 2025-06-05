#include <iostream>
#include <cmath>

class Vector3
{
public:
	const float x;
	const float y;
	const float z;

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	// Returns the sum of two vectors
	Vector3 operator+(const Vector3& other) const
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	// Returns the difference of two vectors
	Vector3 operator-(const Vector3& other) const
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	// Returns the product of two vectors
	Vector3 operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z)
	}

	// Returns true if two vectors are equal, false otherwise
	Vector3 operator==(const Vector3& other) const
	{
		if (x == other.x) && (y == other.y) && (z == other.z)
		{
			return true;
		}
		return false;
	}

	// Scales vector according to scalar
	Vector3 scale(const float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	// Returns magnitude of any vector
	float length(const Vector3& vector)
	{
		return std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z))
	}

	// Normalizes any vector
	Vector3 normalize(const Vector3& vector)
	{
		const float length = std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
		return Vector3(vector.x / length, vector.y / length, vector.z / length);
	}

	// Returns the normalized dot product of two vectors
	// AKA how much two vectors point in the same direction on a scale of (-1, 0, 1)
	float dotProduct(const Vector3& other) const
	{
		const float dotNumerator = (x * other.x) + (y * other.y) + (z * other.z);
		const float dotDenominator = length(x, y, z) * 
							length(other.x, other.y, other.z);
		return (dotNumerator / dotDenominator);
	}

	// Creates a third vector perpendicular to parallelogram spanned by two vectors
	// With length equal to area of that parallelogram
	Vector3 crossProduct(const Vector3& other) const
	{
		float ihat = (y * other.z) - (z * other.y);
		float jhat = (z * other.x) - (x * other.z);
		float khat = (x * other.y) - (y * other.x);

		return Vector3(ihat, jhat, khat);
	}
};