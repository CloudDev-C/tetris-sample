#pragma once
#include "BaseApp.h"
#include "Shapes.h"
#include "PerformanceCounter.h"
#include "Matrix.h"

class Tetris : public BaseApp
{
	int score;
	float time_game;
	float time_wait;
	float time_option;
	ITEM_INFO currentShape;
	ITEM_INFO nextShape;
	CMatrix *matrix;
	bool GameStatus;
public:
	Tetris() = delete;
	Tetris(int SizeX, int SizeY);
	~Tetris();

	virtual void UpdateF(float deltaTime);
	void SetString(int x, int y, wchar_t *str);
	void KeyPressed(int btnCode);
	bool ShapeCheck(ITEM_INFO info, int x, int y, bool isNeedItemEnd);
	bool CheckLine();
	void DelLine(int index);
	void AddToSquare();
	void EndShape();
};

