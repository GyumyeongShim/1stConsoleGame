#include "Bush.h"
#include "Level/Level.h"

Bush::Bush(const Vector2& pos)
	:super("=", pos, Color::Green)
{
	m_SortingOrder = 1;
}

void Bush::OnCollison()
{
	//todo 충돌 받았을 경우 랜덤인카운터
	// 현재 내가 포함된 레벨에 전투 진행요청
}