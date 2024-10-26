#include "Screen.h"

Screen::Screen(short screenWidth, short screenHeight, short fontWidth, short fontHeight, const unsigned long* palette, const HANDLE* hConsoleOutput)
	: fontWidth_(fontWidth), fontHeight_(fontHeight), hConsoleOutput_(hConsoleOutput)
{
	xChars_ = screenWidth / fontWidth_;
	yChars_ = screenHeight / fontHeight_;

	width_ = xChars_;
	height_ = yChars_ * 2;

	consoleScreenBuffer_.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	consoleScreenBuffer_.dwSize = { xChars_, yChars_ };
	consoleScreenBuffer_.dwCursorPosition = { 0, 0 };
	consoleScreenBuffer_.wAttributes = 0 | 0;
	
	consoleScreenBuffer_.srWindow = { 0, 0, xChars_, yChars_ };
	consoleScreenBuffer_.dwMaximumWindowSize = { 10000, 10000 };
	consoleScreenBuffer_.wPopupAttributes = 0;
	consoleScreenBuffer_.bFullscreenSupported = FALSE;

	SetPalette(palette);

	pScreenBuffer_ = new CHAR_INFO[width_ * height_];
	CHAR_INFO charInfo = { ' ', 0 };

	for (int i = 0; i < width_ * height_; i++)
	{
		pScreenBuffer_[i] = charInfo;
	}

}

Screen::~Screen()
{
}

void Screen::SetPixel(short x, short y, unsigned char color, unsigned char chr)
{
}

void Screen::SetPixel(short x, short y, unsigned char color)
{
}

unsigned char Screen::GetPixelColor(short x, short y)
{
	return 0;
}

unsigned char Screen::GetPixelChar(short x, short y)
{
	return 0;
}

void Screen::WriteString(short x, short y, unsigned char color, const char* str)
{
}

void Screen::SetPalette(const unsigned long palette[])
{
	for (int i = 0; i < 16; i++)
	{
		consoleScreenBuffer_.ColorTable[i] = palette[i];
		this->palette_[i] = palette[i];
	}
}

const unsigned long* Screen::GetPalette()
{
	return nullptr;
}

void Screen::ClearFrame(unsigned char color)
{
}

void Screen::DrawFrame()
{
}

CONSOLE_SCREEN_BUFFER_INFOEX* Screen::GetConsoleScreenBuffer()
{
	return &consoleScreenBuffer_;
}
