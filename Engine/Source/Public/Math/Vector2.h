#pragma once

struct Vector2 {
	// Simple Constructor
	Vector2() : x(0.0f), y(0.0f) {}

	// Assigned constructor
	Vector2(float x, float y) : x(x), y(y) {}

	// Uniform constructor
	Vector2(float uniform) : x(uniform), y(uniform) {}

	~Vector2() = default;

	// OPERATORS


	// Vector 2 assignment operator
	Vector2& operator=(const Vector2& other) {
		x = other.x;
		y = other.y;

		return *this;
	}

	// Boolean operators
	bool operator==(const Vector2 other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2 other)
	{
		return x != other.x && y != other.y;
	}

	// Arithmetic operators
	// Addition
	Vector2 operator+(const Vector2& other)
	{
		return Vector2(other.x + x, other.y + y);
	}
	// Addition equals
	Vector2& operator+=(const Vector2& other)
	{
		return *this = *this + other;
	}
	// Subtraction
	Vector2 operator-(const Vector2& other)
	{
		return Vector2(other.x - x, other.y - y);
	}
	// Subtraction equals
	Vector2& operator-=(const Vector2& other)
	{
		return *this = *this - other;
	}
	// Multiplication
	Vector2 operator*(const Vector2& other)
	{
		return Vector2(other.x * x, other.y * y);
	}
	// Multiplication equals
	Vector2& operator*=(const Vector2& other)
	{
		return *this = *this * other;
	}
	// Multiply Vector2 by float
	Vector2 operator*(const float& scalar)
	{
		return Vector2(x * scalar, y * scalar);
	}
	// Multiplication equals Vector2 by float
	Vector2& operator*=(const float scalar)
	{
		return *this = *this * scalar;
	}
	// Division
	Vector2 operator/(const Vector2& other);
	// Division equals
	Vector2& operator/=(const Vector2& other);
	// Division Vector2 by float
	Vector2 operator/(const float& scalar);
	// Division equals Vector2 by float
	Vector2& operator/=(const float scalar);

	// Return an infinite negative vector, also known as invalid vector when dividing by zero
	static Vector2 NaN(); // NaN = Not a number

	// Get the squared length/magnitude/size of the Vector2, inaccurate by double the size but cheaper
	// Use this function for comparisons
	float LengthSqd() const
	{
		return x * x + y * y;
	}

	// Get the length/magnitude/size of the vector
	float Length() const;

	//Get the distance between two vectors, inaccurate by double the size but cheaper
	static float DistSqd(Vector2& v1, Vector2& v2)
	{
		Vector2 distanceVector = v1 - v2;

		// x2 + y2
		return distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y;
	}

	// Get the distance between two Vector2's
	static float Distance(Vector2 v1, Vector2& v2);

	// Change the vector2 to a normalised value
	Vector2& Normalise();

	// Return a normalised vector based on another vector
	static Vector2 Normalised(const Vector2& other);

	// Log x and y of the vector2 to the console
	void Log();

	// Log the length of the vector2 to the console
	void LogLength();

	float x, y;
};