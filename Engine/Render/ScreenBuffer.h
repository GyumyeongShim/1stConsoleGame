#pragma once
#include "Math/Vector2.h"
#include <Windows.h>

namespace Wannabe
{
	//더블 버퍼링에 사용할 console output 핸들을 관리하는클래스.
	class ScreenBuffer
	{
	public:
		ScreenBuffer(const Vector2& screensize);
		~ScreenBuffer();

		void Clear();
		void Draw(CHAR_INFO* charInfo);
		inline HANDLE GetBuffer() const { return m_hBuffer; }

	private:
		HANDLE m_hBuffer = nullptr;
		Vector2 m_vScrrenSize;
	};
}

