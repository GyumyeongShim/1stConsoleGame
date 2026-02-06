#pragma once
#include "Actor\Actor.h"

using namespace Wannabe;

class UI_Btn : public Actor
{
	RTTI_DECLARATIONS(UI_Btn, Actor)
public:
	UI_Btn(const char* txt, const Vector2 pos, Color color);

	//virtual void BeginPlay() override;
	//virtual void Tick(float deltaTime) override;

private:
};

