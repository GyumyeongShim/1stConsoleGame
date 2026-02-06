#pragma once

#include "Common/RTTI.h" 
#include "Math/Vector2.h"
#include "Math/Color.h"

namespace Wannabe
{
	class Level;
	//dll로 만들때 dll 밖에서 접근할때 필요한 선언 __declspec(dllexport)
	class WANNABE_API Actor : public RTTI 
	{
		RTTI_DECLARATIONS(Actor, RTTI); //RTTI 매크로 사용

		struct Status
		{
			int m_iLv = 1;
			int m_iExp = 0;
			int m_iMaxExp = 0;

			int m_iHp = 10;
			int m_iAtk = 1;
			int m_iDef = 1;

			int m_iTurnCnt = 1; // ++1 Max되면 공격 가능.
			int m_iMaxTurnCnt = 10;
		};

	public:
		Actor(const char* image = " ", const Vector2& pos = Vector2::Zero, Color color = Color::White);
		virtual ~Actor(); // 자식 클래스 소멸자 호출을 위해서 virtual 사용

		//게임 플레이 이벤트
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		// 삭제 요청 함수
		void Destroy();

		// 삭제가 될 때 호출될 이벤트 함수
		virtual void OnDestroy();
		
		//게임 종료 함수
		void QuitGame();

		// 충돌 여부 확인 함수
		bool TestIntersect(const Actor* const other);

		// 액터의 이미지 값 변경 함수
		void ChangeImage(const char* newImage);

		// 위치 변경 및 읽기 함수
		void SetPosition(const Vector2& pos);
		inline Vector2 GetPosition() const { return m_Pos; }

		//오너쉽 추가읽기 함수
		void SetOwner(Level* newlevel) { m_Owner = newlevel; }
		inline Level* GetOwner() const { return m_Owner; }

		//Getter
		inline bool HasBeganPlay() const { return m_bHasBeganPlay; }
		inline bool IsActive() const { return m_bIsActive && !m_bDestroyRequested; }
		inline bool IsDestroyRequested() const { return m_bDestroyRequested; }
		inline int GetSortingOrder() const { return m_SortingOrder; }
		inline int GetWidth() const { return m_iWidth; }

	public: // 어느 레벨에서든 접근 가능하게
		Status m_eStat;

	protected:
		bool m_bHasBeganPlay = false; // begin 이벤트 받았는지 여부
		bool m_bIsActive = true; //활성화 여부
		bool m_bDestroyRequested = false; //현재 프레임에 삭제 요청 받았는지

		// 그려질 문자(이미지 대용임)
		char* m_Image = nullptr;
		
		// 문자열 길이
		int m_iWidth = 0;

		Color m_Color = Color::White; // 색상

		//오너쉽 Ownership
		Level* m_Owner = nullptr;

		// 그리기 우선 순위
		int m_SortingOrder = 0;

		Vector2 m_Pos; // 위치

	};

}

