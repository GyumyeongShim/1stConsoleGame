#pragma once
#include "Actor/Actor.h"
#include "Interface/ICanPlayerMove.h"

using namespace Wannabe;

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)

public:
	Player(const Vector2& pos);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

private:
	void Initialize();

private:
	ICanPlayerMove* canPlayerMoveInterface = nullptr;
};
