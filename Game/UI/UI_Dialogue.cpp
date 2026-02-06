#include "UI_Dialogue.h"

UI_Dialogue::UI_Dialogue(const char* txt, const Vector2 pos, Color color)
	:super(txt, pos, color)
{
}

void UI_Dialogue::BeginPlay()
{
}

void UI_Dialogue::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	Checktxt();
}

void UI_Dialogue::Checktxt()
{
	//현재 입력된 txt에서 데미지, 경험치 등등 중요 텍스트 컬러 변경하는 것;
}

//Actor ChangeImage를 통해서 메시지를 변경할 것