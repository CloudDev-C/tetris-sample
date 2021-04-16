#pragma once
#include <Windows.h>

class CConsoleParam
{
	CConsoleParam() = delete;
	CConsoleParam(CConsoleParam &obj) = delete;
	CConsoleParam(CConsoleParam &&obj) = delete;
	~CConsoleParam() = delete;

public:
	static void SetFontSize(SHORT width, SHORT height, LPCWSTR faceName);
};
