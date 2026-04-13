#include "Vector3.h"
#include <DxLib.h>
#include <cassert>
#include <cmath>

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x * scale, y * scale, z * scale);
}

Vector3 Vector3::operator/(float scale) const
{
	if (scale == 0)
	{
		assert(false && "Vector3：0除算が行われました");
		return Vector3();
	}

	return Vector3(x / scale, y / scale, z / scale);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

Vector3& Vector3::operator*=(float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;

	return *this;
}

Vector3& Vector3::operator/=(float scale)
{
	if (scale == 0)
	{
		assert(false && "Vector3：0除算が行われました");
	}

	x /= scale;
	y /= scale;
	z /= scale;

	return *this;
}

bool Vector3::operator==(const Vector3& vec) const
{
	return x == vec.x && y == vec.y && z == vec.z;
}

bool Vector3::operator!=(const Vector3& vec) const
{
	return x != vec.x || y != vec.y || z != vec.z;;
}

float Vector3::GetLength() const
{
	return sqrtf(GetSqLength());
}

float Vector3::GetSqLength() const
{
	float length = x * x + y * y + z * z;
	return length;
}

Vector3 Vector3::GetNormalize() const
{
	Vector3 res;

	// ゼロベクトルかチェック
	float size = this->GetSqLength();
	if (size == 0.0f)
	{
		assert(false && "Vector3：0除算が行われました");
		return Vector3();
	}

	size = this->GetLength();

	res.x = x / size;
	res.y = y / size;
	res.z = z / size;

	return res;
}

VECTOR Vector3::ToVECTOR() const
{
	VECTOR vec = VGet(0, 0, 0);

	vec.x = x;
	vec.y = y;
	vec.z = z;

	return vec;
}
