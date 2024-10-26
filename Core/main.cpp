#include <stdio.h>
#include <Windows.h>
#include <stdint.h>

void SetSmallestFont(HANDLE* hConsoleOutput, uint8_t fontWidth, uint8_t fontHeight, const wchar_t* fontName);
void SetNormalFont(HANDLE* hConsoleOutput);

int main()
{
	/** OS로부터 콘솔 입력 핸들과 출력 핸들을 받아온다. */
	HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	/** OS로부터 콘솔 커서 정보의 bVisible의 값을 false로 설정한다. */
	CONSOLE_CURSOR_INFO lpConsoleCursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);
	lpConsoleCursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsoleOutput, &lpConsoleCursorInfo);

	SetConsoleTitle(TEXT("3D Core project"));

	int windth = 800;
	int height = 600;

	uint8_t fontWidth = 4;
	uint8_t fontHeight = 6;
	
	const unsigned long defaultPalette[16] = 
	{
		0x000000, 0x800000, 0x008000, 0x808000,
		0x000080, 0x800080, 0x008080, 0xC0C0C0,
		0x808080, 0xFF0000, 0x00FF00, 0xFFFF00,
		0x0000FF, 0xFF00FF, 0x00FFFF, 0xFFFFFF
	};

	const unsigned long* palette = defaultPalette;
	const wchar_t* fontName = L"Raster Fonts";

	SetSmallestFont(&hConsoleOutput, fontWidth, fontHeight, fontName);

	//printf_s("Hello World!");

	return 0;
}

void SetSmallestFont(HANDLE* hConsoleOutput, uint8_t fontWidth, uint8_t fontHeight, const wchar_t* fontName)
{
	COORD fontSize = { fontWidth, fontHeight };

	CONSOLE_FONT_INFOEX font;

	font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	font.dwFontSize = fontSize;
	font.FontFamily = 0;
	font.FontWeight = 0;
	wcscpy_s(font.FaceName, fontName);
	int isFontSetting =  SetCurrentConsoleFontEx(*hConsoleOutput, FALSE, &font);

	if (isFontSetting != 0)
	{
		printf_s("font setting is complete!!\n");
	}
	else
	{
		printf_s("font setting is failed!\n");
	}
}

void SetNormalFont(HANDLE* hConsoleOutput)
{

}