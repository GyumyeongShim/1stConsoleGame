#include "BattleManager.h"
#include "Actor/Actor.h"
#include "Util/Utill.h"
#include "Render/Renderer.h"

#include <string>
#include <thread>
#include <chrono> 

using namespace Wannabe;

BattleManager::BattleManager()
    :m_eBattleState(BattleState::Start)
{
}

BattleManager::BattleManager(std::vector<Actor*> vecPlayer, std::vector<Actor*> vecEnemy)
	:m_eBattleState(BattleState::Start), m_vecPlayerParty(vecPlayer), m_vecEnemyParty(vecEnemy)
{
	Initialize();
}

BattleManager::~BattleManager()
{
	if (m_vecPlayerParty.empty() == false)
	{
		for (Actor* actor : m_vecPlayerParty)
			delete actor;

		m_vecPlayerParty.clear();
	}

	if (m_vecEnemyParty.empty() == false)
	{
		for (Actor* actor : m_vecEnemyParty)
			delete actor;

		m_vecEnemyParty.clear();
	}
}

void BattleManager::Start()
{
    PlayAni();
}

void BattleManager::Initialize()
{
}

void BattleManager::PlayAni()
{
	//Util::TurnOffCursor();
	//Util::ClearScreen();

    int iWidth = Renderer::Get().GetScreenSize().x;
    int iHeight = Renderer::Get().GetScreenSize().y;

    for (int y = 0; y < iHeight; ++y)
    {
        for (int x = 0; x < iWidth / 2; ++x)
        {
            // 좌우 대칭
            int mirroredX = x;

            // 그라데이션 색상 설정
            Color color;
            float ratio = static_cast<float>(y) / iHeight;
            if (ratio < 0.33f) color = Color::RightGray;           // 밝은 영역
            else if (ratio < 0.66f) color = Color::Blue;           // 중간
            else color = Color::RightBlue;       // 어두운 영역

            // 좌측
            Renderer::Get().Submit("W", Vector2(mirroredX, y), color, 0);

            // 우측 (좌우 대칭)
            Renderer::Get().Submit("0", Vector2(iWidth - 1 - mirroredX, y), color, 0);
        }
        
        Renderer::Get().Draw();

        float t = static_cast<float>(y) / iHeight;

        // ease-out 느낌
        int delay = static_cast<int>(20 + 80 * t * t);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void BattleManager::Input()
{

}

void BattleManager::Update(float deltaTime)
{

}

void BattleManager::Draw()
{

}