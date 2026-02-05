#pragma once
#include "Actor/Actor.h"

using namespace Wannabe;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor);

public:
	Player(const Vector2& pos);

	const Vector2 GetNextPos();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	Vector2 m_vNextPos; // 다음에 갈 위치값, 밀림처리
}

