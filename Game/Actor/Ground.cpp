#include "Ground.h"

Ground::Ground(const Vector2& pos)
	:super(".", pos, Color::Blue)
{
	m_SortingOrder = 0;
}

