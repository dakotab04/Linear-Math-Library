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

	Vector3 operator*(const Vector3& other) const
	{
		return Vector3(x * other.x, y * other.y, z * other.z)
	}

	// Scales vector according to scalar
	Vector3 scale(const float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar);
	}

	// Returns magnitude of any vector
	float magnitude(const Vector3& vector)
	{
		return std::sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z))
	}

	// Returns the normalized dot product of two vectors
	float dotProduct(const Vector3& other) const
	{
		const float dotNumerator = (x * other.x) + (y * other.y) + (z * other.z);
		const float dotDenominator = std::sqrt((x * x) + (y * y) + (z * z)) * 
							std::sqrt((other.x * other.x) + (other.y * other.y) + (other.z * other.z));
		return (dotNumerator / dotDenominator);
	}
};