#include "Vector2.h"
#include <iostream>

namespace Wannabe
{
	Vector2 Vector2::Zero(0,0);
	Vector2 Vector2::One(1,1);
	Vector2 Vector2::Up(0,1);
	Vector2 Vector2::Down(1,0);

	Vector2::Vector2()
	{
	}

	Vector2::Vector2(int a, int b)
		:x(a), y(b)
	{
	}

	Vector2::~Vector2()
	{
		if (string != nullptr)
		{
			delete[] string;
			string = nullptr;
		}
	}

	const char* Vector2::ToString()
	{
		// 기존 문자열이 있다면 제거.
		if (string != nullptr)
		{
			delete[] string;
			string = nullptr;
		}

		string = new char[128];
		memset(string, 0, sizeof(char) * 128);
		sprintf_s(string, 128, "(%d, %d)", x, y);
		return nullptr;
	}

	Vector2 Vector2::operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 Vector2::operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	bool Vector2::operator==(const Vector2& v) const
	{
		return (x == v.x) && (y == v.y);
	}

	bool Vector2::operator!=(const Vector2& v) const
	{
		return !(*this == v);
	}

	Vector2::operator COORD() const
	{
		COORD coord = {};
		coord.X = static_cast<short>(x);
		coord.Y = static_cast<short>(y);

		return coord;
	}

}
