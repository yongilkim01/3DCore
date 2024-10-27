#include "Screen.h"

#include <string.h>
#include <math.h>

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
	delete[] pScreenBuffer_;
}

void Screen::SetPixel(short x, short y, unsigned char color, unsigned char chr)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

	pScreenBuffer_[x + y * width_].Attributes = static_cast<unsigned short>(color);
	pScreenBuffer_[x + y * width_].Char.AsciiChar = chr;
}

void Screen::SetPixel(short x, short y, unsigned char color)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

	bool pair = y % 2 == 0;

	short mody = (short)round((y / 2.0));
	y -= mody;

	CHAR_INFO* pixel = &pScreenBuffer_[x + y * width_];

	uint8_t oldfg = pixel->Attributes & 0x0F;
	uint8_t oldbg = pixel->Attributes & 0xF0;

	if (pair) color = oldbg | color;
	else color = color << 4 | oldfg;

	pixel->Attributes = color;

}

unsigned char Screen::GetPixelColor(short x, short y)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_) return -1;

	return static_cast<unsigned char>(pScreenBuffer_[x + y * width_].Attributes);
}

unsigned char Screen::GetPixelChar(short x, short y)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_) return '\0';

	return pScreenBuffer_[x + y * width_].Char.AsciiChar;
}

void Screen::WriteString(short x, short y, unsigned char color, const char* str)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_) return;

	for (int i = 0; str[i] != '\0'; i++)
	{
		pScreenBuffer_[x + y * width_ + i].Attributes = color;
		pScreenBuffer_[x + y * width_ + i].Char.AsciiChar = str[i];
	}
}

void Screen::SetPalette(const unsigned long palette[])
{
	for (int i = 0; i < 16; i++)
	{
		consoleScreenBuffer_.ColorTable[i] = palette[i];
		palette_[i] = palette[i];
	}
}

const unsigned long* Screen::GetPalette()
{
	return consoleScreenBuffer_.ColorTable;
}

void Screen::ClearFrame(unsigned char color)
{
	for (int y = 0; y < yChars_; y++)
	{
		for (int x = 0; x < xChars_; x++)
		{
			pScreenBuffer_[x + y * width_].Attributes = 0;
			pScreenBuffer_[x + y * width_].Char.AsciiChar = (byte)223;
		}
	}
}

void Screen::DrawFrame()
{
	COORD screenBufferSize = { xChars_, yChars_ };
	COORD screenBufferCoord = { 0, 0 };

	SMALL_RECT consoleCoords = { 0, 0, xChars_, yChars_ };
	WriteConsoleOutputA(*hConsoleOutput_, pScreenBuffer_, screenBufferSize, screenBufferCoord, &consoleCoords);
}

CONSOLE_SCREEN_BUFFER_INFOEX* Screen::GetConsoleScreenBuffer()
{
	return &consoleScreenBuffer_;
}
