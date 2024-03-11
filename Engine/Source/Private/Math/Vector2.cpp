#include "Math/Vector2.h"
#include <iostream>
#include "Debug.h"

#define MINNORMAL 0.00001f

Vector2 Vector2::operator/(const Vector2& other)
{
	Vector2 newVector(NaN());

	if (other.x == 0.0f)
	{
		EE_LOG("Vector2", "Cannot divide by zero, returning with NaN x.");
	}
	else
	{
		newVector.x = x / other.x;
	}
	if (other.y == 0.0f)
	{
		EE_LOG("Vector2", "Cannot divide by zero, returning with NaN y.");
	}
	else
	{
		newVector.y = y / other.y;
	}

	return newVector;
}
Vector2& Vector2::operator/=(const Vector2& other)
{
	return *this = *this / other;
}
Vector2 Vector2::operator/(const float& scalar)
{
	if (scalar == 0)
	{
		EE_LOG("Vector2", "Cannot divide by zero, returning with NaN Vector2.");
		return Vector2::NaN();
	}

	return Vector2(x / scalar, y / scalar);

}
Vector2& Vector2::operator/=(const float scalar)
{
	return *this = *this / scalar;
}
Vector2 Vector2::NaN()
{
	return Vector2(std::numeric_limits<float>::quiet_NaN());
}

float Vector2::Length() const
{
	// sqrtf (Square root float) = (x2 + y2)
	return std::sqrtf(LengthSqd());
}

float Vector2::Distance(Vector2 v1, Vector2& v2)
{
	// sqrtf (Square root float) = (x2 + y2)
	return sqrtf(DistSqd(v1, v2));
}

Vector2& Vector2::Normalise()
{
	if (Length() > MINNORMAL)
	{
		*this /= Length();
	}
	else
	{
		*this = Vector2();
	}

	return *this;
}

Vector2 Vector2::Normalised(const Vector2& other)
{
	if (other.Length() > MINNORMAL)
	{
		return Vector2(other.x / other.Length(), other.y / other.Length());
	}

	return Vector2();
}

void Vector2::Log()
{
	EE_LOG("Vector2", x << ", " << y);
}

void Vector2::LogLength()
{
	EE_LOG("Vector2", Length());
}
