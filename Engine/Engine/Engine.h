#pragma once

#include "Common/Common.h"

namespace Wannabe
{
	//전방선언
	class Input;
	class Renderer;

	//메인 게임 엔진 클래스임
	class WANNABE_API Engine
	{
		//엔진 설정 구조체
		struct EngineSetting
		{
			// 프레임 속도
			float framerate = 0.0f;

			// 화면 너비
			int width = 0;

			// 화면 높이
			int height = 0;
		};

	public:
		Engine();
		virtual ~Engine();

		//엔진 루프
		void Run();
		
		//엔진 종료
		void QuitEngine();
		
		//레벨관련 함수
		void SetNewLevel(class Level* newLevel);

		// 전역 접근 함수
		static Engine& Get();

		//화면 너비,높이 반환 함수
		inline int GetWidth() const { return m_EngineSetting.width; }
		inline int GetHeight() const { return m_EngineSetting.height; }

	protected:
		// 정리 함수
		void Shutdown();

		// 설정 파일 로드 함수
		void LoadEngineSetting();
		// 게임 플레이 시작 함수
		// unity는 start/awake
		void BeginPlay();
		void Tick(float deltaTime); //업데이트
		void Draw(); //그리기

	protected:
		bool m_bisQuit = false; // 엔진 종료 플래그

		EngineSetting m_EngineSetting; //엔진 설정 구조체

		// 입력 관리자
		Input* m_Input = nullptr;

		//렌더러 객체
		Renderer* m_Renderer = nullptr;
		// 메인 레벨
		class Level* m_MainLevel = nullptr;
		// 전역 변수
		static Engine* instance;
	};
}


