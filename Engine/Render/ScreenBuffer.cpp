#include "ScreenBuffer.h"
#include "Renderer.h"

#include <iostream>

using namespace Wannabe;

ScreenBuffer::ScreenBuffer(const Vector2& screenSize)
	:m_vScrrenSize(screenSize)
{
	// Console Output 생성.
	m_hBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		CONSOLE_TEXTMODE_BUFFER,
		nullptr
	);

	// 예외 처리.
	if (m_hBuffer == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(nullptr, "BufferCreate Error", "Error", MB_OK);
		__debugbreak();
	}

	// 콘솔 창 크기 지정
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = static_cast<int>(screenSize.x - 1);
	rect.Bottom = static_cast<int>(screenSize.y - 1);

	if (!SetConsoleWindowInfo(m_hBuffer, true, &rect))
	{
		//DWORD errorCode = GetLastError();
		std::cerr << "Failed to set console window info.\n";
		__debugbreak();
	}

	// 버퍼 크기 설정.
	if (!SetConsoleScreenBufferSize(m_hBuffer, screenSize))
	{
		std::cerr << "Failed to set console buffer size.\n";
		__debugbreak();
	}

	// 커서 끄기.
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(m_hBuffer, &info);

	// 끄도록 설정.
	info.bVisible = false;
	SetConsoleCursorInfo(m_hBuffer, &info);
}

ScreenBuffer::~ScreenBuffer()
{
	if (m_hBuffer)
	{
		CloseHandle(m_hBuffer);
	}
}

void ScreenBuffer::Clear()
{
	//콘솔 버퍼에 있는 화면 지우기
	//그래픽스 -> 지우기 == 한 색상 또는 값 으로 덮어쓰기
	DWORD writetenCount = 0;
	FillConsoleOutputCharacterA(m_hBuffer, ' ', m_vScrrenSize.x * m_vScrrenSize.y, Vector2::Zero, &writetenCount);
}

void ScreenBuffer::Draw(CHAR_INFO* charInfo)
{
	SMALL_RECT writeRegion = {};
	writeRegion.Left = 0;
	writeRegion.Top = 0;
	writeRegion.Right = static_cast<short>(m_vScrrenSize.x - 1);
	writeRegion.Bottom = static_cast<short>(m_vScrrenSize.y - 1);

	WriteConsoleOutputA(m_hBuffer, charInfo, m_vScrrenSize, Vector2::Zero, &writeRegion);
}
