#include "Game.h"
#include "Level/TitleLevel.h"
#include "Level/MainLevel.h"
#include "Level/BattleLevel.h"

#include <iostream>
#include <vector>

//정적 변수 초기화
Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
	//m_vecLevels.emplace_back(new TitleLevel());
	m_pMainLevel = new MainLevel();
	m_pBattleLevel = new BattleLevel();
	m_vecLevels.emplace_back(m_pMainLevel);
	m_vecLevels.emplace_back(m_pBattleLevel);

	//todo test를 위해 battlelevel 진행
	m_pCurLevel = m_vecLevels[1];
	Engine::Get().SetNewLevel(m_pCurLevel);
}

Game::~Game()
{
	m_pCurLevel = nullptr;
	for (Level*& level : m_vecLevels)
	{
		delete level;
		level = nullptr;
	}

	m_vecLevels.clear();
}

void Game::ToggleMenu()
{
	//화면 지우기.
	system("cls");

	//변경할 인덱스 계산
	//현재 활성 레벨 인덱스가 1이면 0으로
	//현재 활성 레벨 인덱스가 0이면 1으로
	// (1-x)
	int stateIndex = static_cast<int>(state);
	int Nextstate = 1 - stateIndex;
	state = (State)Nextstate;

	m_MainLevel = m_vecLevels[static_cast<int>(state)];
}

void Game::BattleStart(std::vector<Actor*> vecPlayerParty, std::vector<Actor*> vecEnemyParty)
{
	m_pBattleLevel->SetupBattle(vecPlayerParty, vecEnemyParty);

	m_pCurLevel = m_pBattleLevel;
	Engine::Get().SetNewLevel(m_pCurLevel);
}

void Game::BattleEnd()
{
	m_pCurLevel = m_MainLevel;
	Engine::Get().SetNewLevel(m_pCurLevel);
}

Game& Game::Get()
{
	if (!instance)
	{
		std::cerr << "Game::Get() instance is Null\n";
		__debugbreak();
	}

	return *instance;
}
