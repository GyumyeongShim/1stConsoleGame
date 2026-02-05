#include "Game.h"
#include "Level/TitleLevel.h"
#include "Level/MainLevel.h"

#include <iostream>

//정적 변수 초기화
Game* Game::instance = nullptr;

Game::Game()
{
	instance = this;
	//m_vecLevels.emplace_back(new TitleLevel());
	m_vecLevels.emplace_back(new MainLevel());

	m_MainLevel = m_vecLevels[0]; //todo 임시로 메인구성만할것
}

Game::~Game()
{
	m_MainLevel = nullptr;
	for (Level*& level : m_vecLevels)
	{
		delete level;
		level = nullptr;
	}

	m_vecLevels.clear();
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
