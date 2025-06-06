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
	Vector3 cross(const Vector3& other) const
	{
		float ihat = (y * other.z) - (z * other.y);
		float jhat = (z * other.x) - (x * other.z);
		float khat = (x * other.y) - (y * other.x);

		return Vector3(ihat, jhat, khat);
	}

	float distance(const Vector3& other) const {
		return (*this - other).length();
	}

	Vector3 reflect(const Vector3& normal) const {
		return *this - normal.scale(2.0f * this->dot(normal));
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
	Vector4(float x, float y, float z, float t) : x(x), y(y), z(z), t(t) {}
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
	Matrix4x4 linearTransform(const Vector4& vector) const
	{
		float xVal = (x.x * vector.x) + (x.y * vector.y) + (x.z * vector.z) + (x.w * vector.w);
		float yVal = (y.x * vector.x) + (y.y * vector.y) + (y.z * vector.z) + (y.w * vector.w);
		float zVal = (z.x * vector.x) + (z.y * vector.y) + (z.z * vector.z) + (z.w * vector.w);
		float wVal = (t.x * vector.x) + (t.y * vector.y) + (t.z * vector.z) + (t.w * vector.w);

		return Vector4(xVal, yVal, zVal, wVal);
	}

	// Helper function for determinant
	float det3x3(float a1, float a2, float a3,
				 float b1, float b2, float b3,
				 float c1, float c2, float c3)
	{
		return a1 * (b2 * c3 - b3 * c2)
			- a2 * (b1 * c3 - b3 * c1)
			+ a3 * (b1 * c2 - b2 * c1);
	}

	// Calculates determinant of 4x4 matrix
	float determinant()
	{
		const float a = x.x, b = x.y, c = x.z, d = x.w;

		float detA = det3x3(y.y, y.z, y.w, z.y, z.z, z.w, t.y, t.z, t.w);
		float detB = det3x3(y.x, y.z, y.w, z.x, z.z, z.w, t.x, t.z, t.w);
		float detC = det3x3(y.x, y.y, y.w, z.x, z.y, z.w, t.x, t.y, t.w);
		float detD = det3x3(y.x, y.y, y.z, z.x, z.y, z.z, t.x, t.y, t.z);

		return a * detA - b * detB + c * detC - d * detD;
	}

	static Matrix4x4 identity()
	{
		return Matrix4x4(
			Vector4(1, 0, 0, 0), // x-axis (right)
			Vector4(0, 1, 0, 0), // y-axis (up)
			Vector4(0, 0, 1, 0), // z-axis (forward)
			Vector4(0, 0, 0, 1)  // translation + perspective
		);
	}

	// Flips matrix over on its diagonal
	Matrix4x4 transpose()
	{
		Vector4 columnA = Vector4(x.x, y.x, z.x, t.x);
		Vector4 columnB = Vector4(x.y, y.y, z.y, t.y);
		Vector4 columnC = Vector4(x.z, y.z, z.z, t.z);
		Vector4 columnD = Vector4(x.w, y.w, z.w, t.w);

		return Matrix4x4(columnA, columnB, columnC, columnD);
	}
	
	static Matrix4x4 rotationX(float angleRad)
	{

	}
		
	static Matrix4x4 scale(const Vector3& s)
	{

	}
		
	static Matrix4x4 translation(const Vector3& t)
	{

	}
};

