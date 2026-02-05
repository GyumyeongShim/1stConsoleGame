#include "Bush.h"

Bush::Bush(const Vector2& pos)
	:super("=", pos, Color::Green)
{
	m_SortingOrder = 1;
}

void Bush::OnCollison()
{
	// 충돌 받았을 경우 랜덤인카운터 발생 예정
}