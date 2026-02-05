#pragma once

#include "Math/Color.h"
#include "Math/Vector2.h"

#include <iostream>
#include <vector>

namespace Wannabe
{
	//콘솔 버퍼를 관리하는 클래스
	class ScreenBuffer;

	//더블 버퍼링을 지원하는 렌더러 클래스
	class WANNABE_API Renderer
	{
		struct Frame
		{
			Frame(int bufferCount);
			~Frame();

			void Clear(const Vector2& screenSize);
			//글자 값과글자의 색상을 갖는 타입
			CHAR_INFO* m_charInfoArray = nullptr;

			// 그리기 우선순위 배열
			int* m_iSortingOrderArray = nullptr;
		};

		struct  RenderCommand //렌더링할 데이터
		{
			const char* m_text = nullptr; // 화면에 보여줄 문자열 값.
			Vector2 m_pos; //좌표
			Color m_color = Color::White; // 색상
			int m_iSortingOrder = 0; // 그리기 우선순위
		};

		public:
			Renderer(const Vector2& screenSize);
			~Renderer();

			void Draw();
			// 그리는데 필요한 데이터를 제출
			void Submit(const char* txt, const Vector2& pos, Color color = Color::White, int sortingOrder = 0);

			static Renderer& Get();

	private:
		void Clear(); //화면 지우기

		void Present(); //더블 버퍼링을 활용해 활성화 버퍼를 교환하는 함수

		ScreenBuffer* GetCurBuffer(); //현재 사용할 버퍼를 반환하는 함수 getter

	private:
		Vector2 m_vScreenSize; // 화면 크기
		Frame* frame = nullptr; //관리할 프레임 객체
		ScreenBuffer* m_ScreenBuffer[2] = {}; //이중 버퍼 배열

		int m_iCurBufferIdx = 0; // 현재 활성화된 버퍼 인덱스
		std::vector<RenderCommand> m_vecRenderQueue; // 렌더 큐 (씬의 모든 그리기 명령을 모아두는 배열)

		static Renderer* instance; //싱글톤 구현을 위한
	};
}

