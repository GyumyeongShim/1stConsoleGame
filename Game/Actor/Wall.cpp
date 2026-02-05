#include "Wall.h"

Wall::Wall(const Vector2& pos)
	:super("@", pos, Color::RightRed)
{
	m_SortingOrder = 0;
}
