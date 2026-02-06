#include "BattleLevel.h"
#include "Actor/Actor.h"
#include "Util/Utill.h"
#include "Core/Input.h"
#include "Render/Renderer.h"

#include "Actor/Player.h"
#include "Actor/Monster.h"
#include "Game/Game.h"

#include <string>
#include <algorithm>

using namespace Wannabe;

BattleLevel::BattleLevel()
    :m_eBattleState(BattleState::Start)
{
}

BattleLevel::~BattleLevel()
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

void BattleLevel::SetupBattle(std::vector<Actor*> vecPlayer, std::vector<Actor*> vecEnemy)
{
    m_vecPlayerParty = vecPlayer;
    m_vecEnemyParty = vecEnemy;

    m_eBattleState = BattleState::Start;
}

void BattleLevel::Initialize()
{
}

void BattleLevel::PlayAni()
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

        //float t = static_cast<float>(y) / iHeight;

        // ease-out 느낌
        //int delay = static_cast<int>(20 + 80 * t * t);
        //std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void BattleLevel::Input()
{
    if (Input::Get().GetKeyDown('1')) // '1' 키가 공격이면
    {
        // 플레이어의 선택 저장 (예: PlayerAction = Attack)
        m_eBattleState = BattleState::TurnCheck;
    }
    else if (Input::Get().GetKeyDown('2')) // '2' 키가 도망이면
    {
        //Game에서 해당 레벨을 지우는쪽으로 진행할것.
        return;
    }
}

void BattleLevel::Tick(float deltaTime)
{
    super::Tick(deltaTime);

    //실시간 로직 처리.
    switch (m_eBattleState)
    {
    case BattleLevel::BattleState::Start:
        Phase_Start();
        break;
    case BattleLevel::BattleState::CommandSelect:
        Phase_CommandSelect();
        break;
    case BattleLevel::BattleState::TurnCheck:
        Phase_TurnCheck();
        break;
    case BattleLevel::BattleState::Animation:
        Phase_Animation();
        break;
    case BattleLevel::BattleState::Result:
        Phase_Result();
        break;
    default:
        break;
    }
}

void BattleLevel::Draw()
{
    super::Draw(); //액터 그리기
    Draw_OutLine(); //테두리 그리기

    //전투 UI 그리기
    if (m_eBattleState == BattleState::CommandSelect)
    {
        Renderer::Get().Submit("atk: [1] Run: [2]", Vector2(20, 20), Color::White);
    }
}

void BattleLevel::Draw_OutLine()
{
    // 배틀로직에서 사용될 테두리를 그립니다.
    const int width = 80;
    const int height = 25;

    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            if (y == 0 || y == height - 1 ||
                x == 0 || x == width - 1) 
            {
                Renderer::Get().Submit("@", Vector2(20, 20), Color::White);
            }
            else 
            {
                Renderer::Get().Submit(" ", Vector2(20, 20), Color::White);
            }

        }
    }
}

void BattleLevel::Phase_Start()
{
    // 시작 연출
    // UI Actor를 추가할것.
}

void BattleLevel::Phase_CommandSelect()
{
    //Input을 받아서 뭘 선택할지 진행할 것
}

void BattleLevel::Phase_TurnCheck()
{
    for (Actor* actor : m_vecPlayerParty)
    {
        actor->m_eStat.m_iTurnCnt + 1;
        if (actor->m_eStat.m_iTurnCnt >= actor->m_eStat.m_iTurnCnt)
            m_vecTurnOrder.emplace_back(actor);
    }

    for (Actor* enemyActor : m_vecEnemyParty)
    {
        enemyActor->m_eStat.m_iTurnCnt + 1;
        if (enemyActor->m_eStat.m_iTurnCnt >= enemyActor->m_eStat.m_iTurnCnt)
            m_vecTurnOrder.emplace_back(enemyActor);
    }

    // 속도(agility) 기준 정렬 예시
    // 현재는 turncnt, player/monster 순서로 정렬함
    // 추후에는 확장 가능성 있음
    //std::sort(m_vecTurnOrder.begin(), m_vecTurnOrder.end(),
    //    [](Actor* a, Actor* b) { return a->m_eStat.m_isp > b->m_eStat.m_iSpeed; });

    m_eBattleState = BattleState::Animation;
}

void BattleLevel::Phase_Animation()
{
    // 스킬 이펙트, hp 감소연출, 상태 이상 표시   
    for(Actor* actor : m_vecTurnOrder)
    for (Actor* actor : m_vecTurnOrder) 
    {
        if (!actor->IsAlive()) continue;

        switch (actor->chosenAction) 
        {
        case Actor::Action::Attack: 
        {
            Actor* target = ChooseTarget(actor); // 타겟 선택 BattleLevel 담당
            std::cout << actor->GetName() << " 공격!" << target->GetName() << "\n";
            target->ReceiveDamage(actor->GetAttackPower());
            break;
        }
        case Actor::Action::Run:
            std::cout << actor->GetName() << " 도망!" << "\n";
            break;
        }

        actor->chosenAction = Actor::Action::None; // 턴 종료
    }

m_eBattleState = BattleState::CommandSelect; // 다음 턴 준비
}

void BattleLevel::Phase_Result()
{
    //쓰러짐, 경험치, 배틀 종료 여부
    Game::Get().BattleEnd();
}

bool BattleLevel::IsFinishBattle()
{
    bool bFinished = false;
    if (m_vecPlayerParty.empty() == true)
        bFinished = true;

    if (m_vecEnemyParty.empty() == true)
        bFinished = true;

    return bFinished;
}
