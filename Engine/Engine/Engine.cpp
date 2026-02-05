#include "Engine.h"
#include "Level/Level.h"
#include "Core/Input.h"
#include "Util/Utill.h"
#include "Render/Renderer.h"

#include <iostream>
#include <Windows.h> //입력처리를 위해

namespace Wannabe
{
	// 전역 변수 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		// 전역 변수 값 초기화
		instance = this;
		// 입력 관리자 추가
		m_Input = new Input();

		// 설정 파일 로드
		LoadEngineSetting();

		// 렌더러 객체 생성
		m_Renderer = new Renderer(Vector2(m_EngineSetting.width, m_EngineSetting.height));

		//커서 끄기
		Util::TurnOffCursor();
		Util::SetRandomSeed();
	}

	Engine::~Engine()
	{
		if (m_MainLevel)
		{
			delete m_MainLevel;
			m_MainLevel = nullptr;
		}

		if (m_Input)
		{
			delete m_Input;
			m_Input = nullptr;
		}

		SafeDelete(m_Renderer);
	}

	void Engine::Run()
	{
		//시계의 정밀도
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);

		//프레임 계산용 변수
		int64_t CurrentTime = 0;
		int64_t PreviousTime = 0;

		LARGE_INTEGER time;
		QueryPerformanceCounter(&time); //단위가 하드웨어의 클락으로 표기됨

		//엔진 시작 직전 두 시간값을 같게 맞춤, 프레임 초기화
		CurrentTime = time.QuadPart;
		PreviousTime = CurrentTime;

		//기준 프레임 설정 (초 단위)
		//float targetFrameRate = 120.0f;
		//float oneFrameTime = 1.0f / targetFrameRate;
		m_EngineSetting.framerate = m_EngineSetting.framerate == 0.0f ? 60.0f : m_EngineSetting.framerate;
		float oneFrameTime = 1.0f / m_EngineSetting.framerate;

		while (!m_bisQuit)
		{
			//현재 시간 구하기
			QueryPerformanceCounter(&time);
			CurrentTime = time.QuadPart;

			//프레임 시간 계산
			float deltaTime = static_cast<float>(CurrentTime - PreviousTime);
			//초 단위 변환
			deltaTime = deltaTime / static_cast<float>(frequency.QuadPart);

			if (deltaTime >= oneFrameTime)
			{
				m_Input->ProcessInput();

				//프레임 처리
				BeginPlay();
				Tick(deltaTime);
				Draw();

				// 이전 시간 값 갱신
				PreviousTime = CurrentTime;

				m_Input->SavePreviousInputStates();
				
				//레벨에 요청된 추가/제거 처리
				if(m_MainLevel)
				{
					m_MainLevel->ProcessAddAndDestroyActors();
				}
			}
		}

		Shutdown();
	}
	
	void Engine::QuitEngine()
	{
		m_bisQuit = true;
	}

	void Engine::SetNewLevel(Level* newLevel)
	{
		if(m_MainLevel)
		{
			//todo 임시, 지금은 당장 삭제함, 추후에 잘 작성할 예정
			delete m_MainLevel;
			m_MainLevel = nullptr;
		}

		//레벨 설정
		m_MainLevel = newLevel;
	}

	Engine& Engine::Get()
	{
		//예외처리
		if (!instance)
		{
			// Silent is vioent
			std::cout << "Error: Engine::Get() instance is null\n";
			__debugbreak();
		}

		return *instance;
	}

	void Engine::Shutdown()
	{
		system("cls");
		// 정리 작업
		std::cout << "Game END" << "\n"; //종료 문구

		//커서 켜기
		Util::TurnOnCursor();
	}

	void Engine::LoadEngineSetting()
	{
		FILE* file = nullptr;
		fopen_s(&file, "../Config/Setting.txt", "rt");

		//예외처리
		if(!file)
		{
			std::cout << "Engine Setting File Open Failed.\n";
			__debugbreak();
			return;
		}

		//파일 읽은 데이터 버퍼
		char buffer[2048] = {};

		//읽기
		size_t readSize = fread_s(buffer, sizeof(buffer), sizeof(char), 2048, file);

		//문자열 자르기 (파싱), 첫번째 문자열 분리할때는 첫 파라미터 전달
		char* context = nullptr;
		char* token = nullptr;
		token = strtok_s(buffer, "\n", &context);

		while (token)
		{
			//설정 텍스트에서 파라미터 이름만 읽기.
			char header[10] = {};

			//문자열 읽기 함수 활용 %s로 읽으면 스페이스가 있으면 거기까지 읽음
			sscanf_s(token, "%s", header,10);

			//문자열 비교 및 값 읽기
			if(strcmp(header,"framerate") == 0)
				sscanf_s(token, "framerate = %f", &m_EngineSetting.framerate);

			else if (strcmp(header, "width") == 0)
				sscanf_s(token, "width = %d", &m_EngineSetting.width);

			else if (strcmp(header, "height") == 0)
				sscanf_s(token, "height = %d", &m_EngineSetting.height);

			// 개행 문자로 문자열 분리.
			token = strtok_s(nullptr, "\n", &context);
		}
		//파일 닫기
		fclose(file);
	}

	void Engine::BeginPlay()
	{
		// 레벨 유효한지 체크
		if (!m_MainLevel)
		{
			//로그 남기기 위해 이런식으로 코드 작성
			std::cout << "MainLevel Is Empty.\n";
			return;
		}

		m_MainLevel->BeginPlay();
	}

	void Engine::Tick(float deltaTime)
	{
		//프레임 체크가 필요하면 주석 해제
		//std::cout << "DeltaTime: " << deltaTime << ", FPS: " << (1.0f / deltaTime) << "\n";

		if (!m_MainLevel)
		{
			std::cout << "MainLevel Tick() mainLevel Is Empty.\n";
			return;
		}

		m_MainLevel->Tick(deltaTime);
	}

	void Engine::Draw()
	{
		if (!m_MainLevel)
		{
			std::cout << "MainLevel Draw() Is Empty.\n";
			return;
		}

		// 레벨의 모든 액터가 렌더 데이터를 제출.
		m_MainLevel->Draw();

		// 렌더러에 그리기 명령 전달.
		m_Renderer->Draw();
	}
}