#pragma once
#include "Common/Common.h"
#include <Windows.h>

namespace Wannabe
{
	class WANNABE_API Vector2
	{
	public:
		Vector2();
		Vector2(int a, int b);
		~Vector2();

		// 문자열로 변환해서 반환하는 함수
		const char* ToString();

		Vector2 operator+(const Vector2& v) const;
		Vector2 operator-(const Vector2& v) const;
		//Vector2 operator*(const Vector2& v) const; // 스칼라 곱셈 필요시 구현
		//Vector2 operator/(const Vector2& v) const;

		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;

		//형변환 연산자 오버로딩
		operator COORD() const;

		//벡터 기본 값
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Up;
		static Vector2 Down;
		
	public:
		// x,y 좌표
		int x = 0;
		int y = 0;

	private:
		//벡터 값을 문자열로 변환할때 사용할 변수
		char* string = nullptr;
	};
}

