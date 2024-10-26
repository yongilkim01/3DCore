#pragma once

#include <Windows.h>
#include <stdint.h>
#include <uchar.h>

class Screen
{
public:
	Screen(short screenWidth, short screenHeight, short fontWidth, short fontHeight, const unsigned long* palette, const HANDLE* hConsoleOutput);
	~Screen();

	inline void SetWidth(short width) { width_ = width; }
	inline short GetWidth() { return width_; }

	inline void SetHeight(short height) { height_ = height; }
	inline short GetHeight() { return height_; }

	inline void SetFontWidth(short fontWidth) { fontWidth_ = fontWidth; }
	inline short GetFontWidth() { return fontWidth_; }

	inline void SetFontHeight(short fontHeight) { fontHeight_ = fontHeight; }
	inline short GetFontHeight() { return fontHeight_; }

	void SetPixel(short x, short y, unsigned char color, unsigned char chr);
	void SetPixel(short x, short y, unsigned char color);

	unsigned char GetPixelColor(short x, short y);
	unsigned char GetPixelChar(short x, short y);

	void WriteString(short x, short y, unsigned char color, const char* str);

	void SetPalette(const unsigned long palette[]);
	const unsigned long* GetPalette();

	void ClearFrame(unsigned char color);
	void DrawFrame();

	CONSOLE_SCREEN_BUFFER_INFOEX* GetConsoleScreenBuffer();

protected:

private:
	short xChars_ = 0;
	short yChars_ = 0;
	short width_ = 0;
	short height_ = 0;
	short fontWidth_ = 0;
	short fontHeight_ = 0;

	const HANDLE* hConsoleOutput_ = nullptr;

	CONSOLE_SCREEN_BUFFER_INFOEX consoleScreenBuffer_;
	CHAR_INFO* pScreenBuffer_ = nullptr;

	unsigned long palette_[16] = { 0 };

	int triangles_ = 0;
};