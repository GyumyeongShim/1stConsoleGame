#include "UI_Dialogue.h"

UI_Dialogue::UI_Dialogue(const char* txt, const Vector2 pos, Color color)
	:super(txt, pos, color)
{
}

void UI_Dialogue::BeginPlay()
{
	Checktxt();
}

void UI_Dialogue::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

void UI_Dialogue::Checktxt()
{
	//txt 중 데미지, 경험치 등등 중요 텍스트 컬러 변경하는 것;
}
