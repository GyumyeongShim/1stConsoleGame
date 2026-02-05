#include "MainLevel.h"
#include "Engine/Engine.h"
#include "Core/Input.h"
#include "Util/Utill.h"

#include "Actor/Player.h"
#include "Actor/Wall.h"
#include "Actor/Bush.h"
#include "Actor/Ground.h"

#include <iostream>

MainLevel::MainLevel()
{
	Initialize();
	LoadMap("map.txt");
}

MainLevel::~MainLevel()
{
}

void MainLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//todo 여기서 수풀하고 충돌체크를 하자.
	CheckCollision();
}

void MainLevel::Draw()
{
	super::Draw();
}

void MainLevel::Initialize()
{
	 //변수 초기화 이외에 생성자에서 처리하면 좋을 것들
	//월드 생성, player 생성/초기위치,
	LoadMap("map.txt");
	AddNewActor(new Player(m_vPlayerStartPos));
}

void MainLevel::LoadMap(const char* filename)
{
	// 파일 로드.
	// 최종 파일 경로 만들기. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외 처리.
	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file.\n";

		// 디버그 모드에서 중단점으로 중단해주는 기능.
		__debugbreak();
	}

	// 맵 읽기.
	// 맵 크기 파악: File Position 포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱-Parsing)해서 출력.
	// 인덱스를 사용해 한문자씩 읽기.
	int index = 0;

	//객체를 생성할 위치
	Vector2 Pos;

	while (true)
	{
		// 종료 조건.
		if (index >= fileSize)
			break;

		// 캐릭터 읽기
		char mapCharacter = data[index];
		++index;

		// 개행 문자 처리.
		if (mapCharacter == '\n')
		{
			++Pos.y;
			Pos.x = 0;
			continue;
		}

		/*
		@: 벽
		=: 수풀
		.: 바닥(Ground)
		p: 플레이어(Player)
		b: 박스(Box)
		t: 타겟(Target)
		*/
		// 한문자씩 처리.
		switch (mapCharacter)
		{
		case '@':
			AddNewActor(new Wall(Pos));
			break;
		case '=':
			AddNewActor(new Bush(Pos));
			break;
		case '.':
			AddNewActor(new Ground(Pos));
			break;
		case 'p':
			m_vPlayerStartPos = Pos;
			break;
		}

		++Pos.x;
	}

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

void MainLevel::CheckCollision()
{
	std::vector<Actor*> Players; // todo 현재는 1명
	std::vector<Wall*> Walls; // 밀림처리
	std::vector<Bush*> Bushes; // 랜덤 인카운터

	//액터 찾아두기
	for (Actor* const actor : m_vecActors) //전체 오브젝트를 순회
	{
		if (actor->IsTypeOf<Player>() == true)
		{
			Players.emplace_back(actor);
			continue;
		}

		if (actor->IsTypeOf<Wall>() == true)
		{
			Walls.emplace_back(actor);
			continue;
		}

		if (actor->IsTypeOf<Bush>() == true)
		{
			Bushes.emplace_back(actor);
			continue;
		}
	}

	//밀림처리
	//판정 안해도 되는지 확인
	//if (bullets.size() == 0 || enemies.size() == 0)
	//	return;

	////충돌 판정
	//for (Actor* const Player : Players)
	//{
	//	for (Wall* const wall : Walls)
	//	{
	//		// AABB 겹침 판정.
	//		if()
	//		if (bullet->TestIntersect(enemy))
	//		{
	//			enemy->OnDamaged();
	//			bullet->Destroy();

	//			// Todo: 점수 추가.
	//			continue;
	//		}
	//	}
	// }

	return;
}

//void MainLevel::CheckCollision(const Vector2& playerPos, const Vector2& nextPos)
//{
//	std::vector<Actor*> bullets;
//	std::vector<Bush*> enemies;
//
//	// 액터 필터링.
//	for (Actor* const actor : m_vecActors)
//	{
//		if (actor->IsTypeOf<Player>())
//		{
//			bullets.emplace_back(actor);
//			continue;
//		}
//
//		if (actor->IsTypeOf<Bush>())
//		{
//			enemies.emplace_back(actor->As<Bush>());
//		}
//	}
//
//	//판정 안해도 되는지 확인
//	if (bullets.size() == 0 || enemies.size() == 0)
//		return;
//
//	//충돌 판정
//	for (Actor* const bullet : bullets)
//	{
//		for (Bush* const enemy : enemies)
//		{
//			// AABB 겹침 판정.
//			if (bullet->TestIntersect(enemy))
//			{
//				enemy->OnDamaged();
//				bullet->Destroy();
//
//				// Todo: 점수 추가.
//				continue;
//			}
//		}
//	}
//
//	return;
//}
