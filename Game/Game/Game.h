#pragma once
#include "Engine/Engine.h"
#include <vector>

using namespace Wannabe;

//레벨 관리에 사용할 열거형.
enum class State
{
	None = -1,
	Title = 0,
	GamePlay = 1,
};

class Game : public Engine // 모든 레벨을 관리하는 총괄 매니저 느낌
{
public:
	Game();
	~Game();

	void ToggleMenu();

	static Game& Get();

private:
	std::vector<Level*> m_vecLevels; // 게임에서 관리하는 레벨을 저장할 배열

	State state = State::GamePlay; // 현재 활성화된 레벨을 나타내는 상태 변수

	static Game* instance; // 싱글톤
};

