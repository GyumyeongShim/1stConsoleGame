#include "Monster.h"
#include "Util/Utill.h"

Monster::Monster()
	:super("M",Vector2::Zero,Color::Magenta)
{
	m_eTeam = Team::Enemy;
}

Monster::~Monster()
{
}

void Monster::BeginPlay()
{
	//todo ½ºÅÈ¼³Á¤
}

void Monster::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	m_pStatComponent->Update(deltaTime);
}
