#include "Screen.h"

Screen::Screen(short screenWidth, short screenHeight, short fontWidth, short fontHeight, const unsigned long* palette, const HANDLE* hConsoleOutput)
{
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
	return nullptr;
}
