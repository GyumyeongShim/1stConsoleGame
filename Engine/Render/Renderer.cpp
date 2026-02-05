#include "Renderer.h"
#include "ScreenBuffer.h"
#include "Util/Utill.h"

using namespace Wannabe;

Renderer::Frame::Frame(int bufferCount)
{
	//초기화
	m_charInfoArray = new CHAR_INFO[bufferCount];
	memset(m_charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);

	m_iSortingOrderArray = new int[bufferCount];
	memset(m_iSortingOrderArray, 0, sizeof(int) * bufferCount);
}

Renderer::Frame::~Frame()
{
	SafeDeleteArray(m_charInfoArray);
	SafeDelete(m_iSortingOrderArray);
}

void Renderer::Frame::Clear(const Vector2& screenSize)
{
	//2차원 배열로 다루는 1차원 배열을 순회하면서 빈문자를 설정
	const int width = screenSize.x;
	const int height = screenSize.y;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//배열 인덱스
			const int idx = (y * width) + x;

			CHAR_INFO& info = m_charInfoArray[idx];
			info.Char.AsciiChar = ' ';
			info.Attributes = 0;

			//그리기 우선순위 초기화
			m_iSortingOrderArray[idx] = -1;
		}
	}
}

// 정적 변수 초기화.
Renderer* Renderer::instance = nullptr;

Renderer::Renderer(const Vector2& screenSize)
	: m_vScreenSize(screenSize)
{
	instance = this;

	const int bufferCnt = screenSize.x * screenSize.y;
	frame = new Frame(bufferCnt);

	// 프레임 초기화
	frame->Clear(screenSize);

	//이중 버퍼 객체 생성
	m_ScreenBuffer[0] = new ScreenBuffer(screenSize);
	m_ScreenBuffer[0]->Clear();

	m_ScreenBuffer[1] = new ScreenBuffer(screenSize);
	m_ScreenBuffer[1]->Clear();

	// 활성화 버퍼 설정.
	Present();
}

Renderer::~Renderer()
{
	SafeDelete(frame);
	for (ScreenBuffer*& buffer : m_ScreenBuffer)
	{
		SafeDelete(buffer);
	}
}

void Renderer::Draw()
{
	//1화면 지우기
	Clear();

	//2렌더큐 순회하면서 그리기, 모든 액터가 렌더러에 submit 완료
	for (const RenderCommand& command : m_vecRenderQueue)
	{
		// 텍스트가 없으면 건너띔
		if (command.m_text == nullptr)
			continue;

		//세로 기준 화면 벗어났는지?
		if (command.m_pos.y < 0 || command.m_pos.y >= m_vScreenSize.y)
			continue;

		//화면에 그릴 문자열 길이
		const int length = static_cast<int>(strlen(command.m_text));
		// 안그려도 된다면 건너띔
		if (length <= 0)
			continue;

		const int startX = command.m_pos.x;
		const int endX = command.m_pos.x + length - 1;

		if (endX < 0 || startX >= m_vScreenSize.x)
			continue;

		//시작 위치
		const int visibleStart = startX < 0 ? 0 : startX;
		const int visibleEnd = endX >= m_vScreenSize.x ? m_vScreenSize.x - 1 : endX;

		//문자열 설정
		for (int x = visibleStart; x <= visibleEnd; ++x)
		{
			//문자열 안의 문자 인덱스
			const int sourceIdx = x - startX;
			const int idx = (command.m_pos.y * m_vScreenSize.x) + x;

			//그리기 우선순위 비교
			if (frame->m_iSortingOrderArray[idx] > command.m_iSortingOrder)
				continue;

			//데이터 기록
			frame->m_charInfoArray[idx].Char.AsciiChar = command.m_text[sourceIdx];
			frame->m_charInfoArray[idx].Attributes = (WORD)command.m_color;

			//우선 순위 업데이트
			frame->m_iSortingOrderArray[idx] = command.m_iSortingOrder;
		}
	}


	//3그리기
	GetCurBuffer()->Draw(frame->m_charInfoArray);

	//4버퍼 교환
	Present();

	//5렌더 큐 비우기
	m_vecRenderQueue.clear();
}

Renderer& Renderer::Get()
{
	if (!instance)
	{
		MessageBoxA(nullptr, "Error: Renderer::Get() instance is null", "Error", MB_OK);
		__debugbreak();
	}

	return *instance;
}

void Renderer::Clear()
{
	frame->Clear(m_vScreenSize);
	GetCurBuffer()->Clear(); //콘솔 버퍼 지우기
}

void Renderer::Submit(const char* txt, const Vector2& pos, Color color, int sortingOrder)
{
	//렌더 데이터 생성 후 큐에 추가
	RenderCommand command = {};
	command.m_text = txt;
	command.m_pos = pos;
	command.m_color = color;
	command.m_iSortingOrder = sortingOrder;

	m_vecRenderQueue.emplace_back(command);

}

void Renderer::Present()
{
	// 버퍼 교체
	SetConsoleActiveScreenBuffer(GetCurBuffer()->GetBuffer());

	//인덱스 교체 , (1-0)
	m_iCurBufferIdx = 1 - m_iCurBufferIdx;
}

ScreenBuffer* Renderer::GetCurBuffer()
{
	return m_ScreenBuffer[m_iCurBufferIdx];
}

