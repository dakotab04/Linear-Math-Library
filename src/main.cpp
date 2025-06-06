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

class Vector4
{
public:
	float x;
	float y; 
	float z; 
	float w;

	// Constructor
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// Addition of two 4d vectors
	Vector4 operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	// Subtraction of two 4d vectors
	Vector4 operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	// Multiplication of two 4d vectors
	Vector4 operator*(const Vector4& other) const
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}

	// Returns true if two 4d vectors are equal, false otherwise
	bool operator==(const Vector4& other) const
	{
		if ((x == other.x) && (y == other.y) && (z == other.z) && (w == other.w)
		{
			return true;
		}
		return false;
	}

	// Scales 4d vector according to scalar
	Vector4 scale(const float scalar) const
	{
		return Vector3(x * scalar, y * scalar, z * scalar, w * scalar);
	}
};

class Matrix3x3
{
public:
	Vector3 x;
	Vector3 y;
	Vector3 z;

	// Constructor
	Matrix3x3(Vector3 x, Vector3 y, Vector3 z) : x(x), y(y), z(z) {}

	// Matrix-matrix addition
	Matrix3x3 operator+(const Matrix3x3& other) const
	{
		return Matrix3x3((x + other.x), (y + other.y), (z + other.z));
	}

	// Matrix-matrix subtraction
	Matrix3x3 operator-(const Matrix3x3& other) const
	{
		return Matrix3x3((x - other.x), (y - other.y), (z - other.z));
	}

	// Matrix-matrix multiplication
	Matrix3x3 operator*(const Matrix3x3& other) const
	{
		Matrix3x3 t = this->transpose();

		return Matrix3x3(
			Vector3(t.x.dot(other.x), t.y.dot(other.x), t.z.dot(other.x)),
			Vector3(t.x.dot(other.y), t.y.dot(other.y), t.z.dot(other.y)),
			Vector3(t.x.dot(other.z), t.y.dot(other.z), t.z.dot(other.z))
		);
	}

	// Scales 3x3 matrix by corresponding scalar
	Matrix3x3 scalar(const float s) const
	{
		return Matrix3x3((x * s), (y * s), (z * s));
	}

	// 3x3Matrix-vector3 multiplication
	Vector3 linearTransform(const Vector3& vector) const
	{
		float xVal = (x.x * vector.x) + (x.y * vector.y) + (x.z * vector.z);
		float yVal = (y.x * vector.x) + (y.y * vector.y) + (y.z * vector.z);
		float zVal = (z.x * vector.x) + (z.y * vector.y) + (z.z * vector.z);

		return Vector3(xVal, yVal, zVal);
	}

	// Returns determinant of a 3x3 matrix
	float determinant() const
	{
		return
			x.x * (y.y * z.z - y.z * z.y) -
			y.x * (x.y * z.z - x.z * z.y) +
			z.x * (x.y * y.z - x.z * y.y);
	}

	// Resets a 3x3 matrix
	static Matrix3x3 identity()
	{
		return Matrix3x3(
			Vector3(1, 0, 0), // x-axis (right)
			Vector3(0, 1, 0), // y-axis (up)
			Vector3(0, 0, 1) // z-axis (forward)
		);
	}

	// Flips matrix over on its diagonal
	Matrix3x3 transpose() const
	{
		Vector3 columnA = Vector3(x.x, y.x, z.x);
		Vector3 columnB = Vector3(x.y, y.y, z.y);
		Vector3 columnC = Vector3(x.z, y.z, z.z);

		return Matrix3x3(columnA, columnB, columnC);
	}

	static Matrix3x3 rotationX(float angleRad)
	{
		float c = std::cos(angleRad);
		float s = std::sin(angleRad);

		return Matrix3x3(
			Vector3(1, 0, 0),  // First column (X-axis unchanged)
			Vector3(0, c, s),  // Second column (rotated Y)
			Vector3(0, -s, c)  // Third column (rotated Z)
		);
	}

	// Scales a 3x3 matrix by corresponding vector scalar.
	static Matrix3x3 scale(const Vector3& s)
	{
		return Matrix3x3(
			Vector3(s.x, 0, 0),
			Vector3(0, s.y, 0),
			Vector3(0, 0, s.z)
		);
	}
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
		const Vector4 col0(
			x.x * other.x.x + y.x * other.x.y + z.x * other.x.z + t.x * other.x.w,
			x.y * other.x.x + y.y * other.x.y + z.y * other.x.z + t.y * other.x.w,
			x.z * other.x.x + y.z * other.x.y + z.z * other.x.z + t.z * other.x.w,
			x.w * other.x.x + y.w * other.x.y + z.w * other.x.z + t.w * other.x.w
		);

		const Vector4 col1(
			x.x * other.y.x + y.x * other.y.y + z.x * other.y.z + t.x * other.y.w,
			x.y * other.y.x + y.y * other.y.y + z.y * other.y.z + t.y * other.y.w,
			x.z * other.y.x + y.z * other.y.y + z.z * other.y.z + t.z * other.y.w,
			x.w * other.y.x + y.w * other.y.y + z.w * other.y.z + t.w * other.y.w
		);

		const Vector4 col2(
			x.x * other.z.x + y.x * other.z.y + z.x * other.z.z + t.x * other.z.w,
			x.y * other.z.x + y.y * other.z.y + z.y * other.z.z + t.y * other.z.w,
			x.z * other.z.x + y.z * other.z.y + z.z * other.z.z + t.z * other.z.w,
			x.w * other.z.x + y.w * other.z.y + z.w * other.z.z + t.w * other.z.w
		);

		const Vector4 col3(
			x.x * other.t.x + y.x * other.t.y + z.x * other.t.z + t.x * other.t.w,
			x.y * other.t.x + y.y * other.t.y + z.y * other.t.z + t.y * other.t.w,
			x.z * other.t.x + y.z * other.t.y + z.z * other.t.z + t.z * other.t.w,
			x.w * other.t.x + y.w * other.t.y + z.w * other.t.z + t.w * other.t.w
		);

		return Matrix4x4(col0, col1, col2, col3);
	}

	// Scales 4x4 matrix by corresponding scalar
	Matrix4x4 scalar(const float s) const
	{
		return Matrix4x4((x * s), (y * s), (z * s), (t * s));
	}

	// 4x4Matrix-vector4 multiplication
	Vector4 linearTransform(const Vector4& vector) const
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
	Matrix4x4 transpose() const
	{
		Vector4 columnA = Vector4(x.x, y.x, z.x, t.x);
		Vector4 columnB = Vector4(x.y, y.y, z.y, t.y);
		Vector4 columnC = Vector4(x.z, y.z, z.z, t.z);
		Vector4 columnD = Vector4(x.w, y.w, z.w, t.w);

		return Matrix4x4(columnA, columnB, columnC, columnD);
	}
	
	// Rotates a 4x4 matrix around the X-axis by given angle in radians.
	static Matrix4x4 rotationX(float angleRad)
	{
		float c = std::cos(angleRad);
		float s = std::sin(angleRad);

		return Matrix4x4(
			Vector4(1, 0, 0, 0),
			Vector4(0, c, -s, 0),
			Vector4(0, s, c, 0),
			Vector4(0, 0, 0, 1)
		);
	}
	
	// Scales a 4x4 matrix by corresponding vector scalar.
	static Matrix4x4 scale(const Vector3& s)
	{
		return Matrix4x4(
			Vector4(s.x, 0, 0, 0),
			Vector4(0, s.y, 0, 0),
			Vector4(0, 0, s.z, 0),
			Vector4(0, 0, 0, 1)
		);
	}

	// Translates a 4x4 matrix by given vector along the x, y, and z axes.
	static Matrix4x4 translation(const Vector3& t)
	{
		return Matrix4x4(
			Vector4(1, 0, 0, 0),
			Vector4(0, 1, 0, 0),
			Vector4(0, 0, 1, 0),
			Vector4(t.x, t.y, t.z, 1)
		);
	}
};

