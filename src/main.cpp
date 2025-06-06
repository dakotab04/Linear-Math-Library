#include <iostream>
#include <cmath>

class Vector3
{
public:
	const float x;
	const float y;
	const float z;

	// Constructor
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
		return Vector3(x * other.x, y * other.y, z * other.z);
	}

	// Returns true if two vectors are equal, false otherwise
	bool operator==(const Vector3& other) const
	{
		if ((x == other.x) && (y == other.y) && (z == other.z))
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
	float length() const
	{
		return std::sqrt((x * x) + (y * y) + (z * z));
	}

	// Normalizes any vector
	Vector3 normalize() const
	{
		float v_length = length(); // magnitude of vector
		return Vector3(x / v_length, y / v_length, z / v_length);
	}

	// Returns raw dot product of two vectors.
	// AKA how much two vectors point in the same direction on a scale of (-1, 0, 1)
	float dot(const Vector3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}
	// Returns the normalized dot product of two vectors
	float dotNormalized(const Vector3& other) const
	{
		const float dotNumerator = (x * other.x) + (y * other.y) + (z * other.z);
		const float dotDenominator = this->length() * other.length();

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

// For implementing Matrix 4x4 class.
class Vector4
{
public:
	float x;
	float y; 
	float z; 
	float w;

	// Constructor
	Vector4(float x, float y, float z, float t) : x(x), y(y), z(z), w(w) {}
};

class Matrix4x4
{
public:
	Vector4 x;
	Vector4 y;
	Vector4 z;
	Vector4 t;

	// Constructor
	Matrix4x4(Vector4 x, Vector4 y, Vector4 z, Vector4 t) : x(x), y(y), z(z), t(t) {}

	// Matrix-matrix addition
	Matrix4x4 operator+(const Matrix4x4& other) const
	{
		return Matrix4x4((x + other.x), (y + other.y), (z + other.z), (t + other.t));
	}

	// Matrix-matrix subtraction
	Matrix4x4 operator-(const Matrix4x4& other) const
	{
		return Matrix4x4((x - other.x), (y - other.y), (z - other.z), (t - other.t));
	}

	// Matrix-matrix multiplication
	Matrix4x4 operator*(const Matrix4x4& other) const
	{
		return Matrix4x4((x * other.x), (y * other.y), (z * other.z), (t * other.t));
	}

	// Scales 4x4 matrix
	Matrix4x4 scale(const float scalar) const
	{
		return Matrix4x4((x * scalar), (y * scalar), (z * scalar), (t * scalar));
	}

	// Matrix-vector multiplication
	Matrix4x4 linearTransformation(const Vector4& vector) const
	{
		float xVal = (x.x * vector.x) + (x.y * vector.y) + (x.z * vector.z) + (x.w * vector.w);
		float yVal = (y.x * vector.x) + (y.y * vector.y) + (y.z * vector.z) + (y.w * vector.w);
		float zVal = (z.x * vector.x) + (z.y * vector.y) + (z.z * vector.z) + (z.w * vector.w);
		float wVal = (t.x * vector.x) + (t.y * vector.y) + (t.z * vector.z) + (t.w * vector.w);

		return Vector4(xVal, yVal, zVal, wVal);
	}
};