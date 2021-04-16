#include "CConsoleParam.h"

void CConsoleParam::SetFontSize(SHORT width, SHORT height, LPCWSTR faceName)
{
	CONSOLE_FONT_INFOEX font = {};
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font);
	font.dwFontSize = { width, height };
	font.cbSize = sizeof(font);
	lstrcpyW(font.FaceName, faceName);
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &font);
}