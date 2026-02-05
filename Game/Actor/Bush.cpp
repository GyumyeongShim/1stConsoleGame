#include "Bush.h"

Bush::Bush(const Vector2& pos)
	:super("=", pos, Color::Green)
{
	m_SortingOrder = 1;
}

void Bush::OnDamaged()
{
}
