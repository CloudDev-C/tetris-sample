#pragma once
#include <Windows.h>
#include <vector>
#include <math.h>

#define SHAPE_HEIGHT 4
#define SHAPE_WIDTH 4
#define START_POS_X 6
#define SHAPE_COUNT 7

#define M_PI           3.14159265358979323846

const int shape1[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape2[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,1,0 },{ 1,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape3[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape4[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape5[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape6[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 1,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } };
const int shape7[SHAPE_HEIGHT][SHAPE_WIDTH] = { { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } };

struct sShape
{
	int value[SHAPE_HEIGHT][SHAPE_WIDTH];
	int height;
	int width;
};

struct ITEM_INFO
{
	int x;
	int y;
	int type;
	sShape itemFigure;
};

class Shapes
{
	sShape data[SHAPE_COUNT];

	const int WIDTH;
	const int HEIGHT;

	void Init(const int temp[SHAPE_HEIGHT][SHAPE_WIDTH], int id);
public:
	Shapes();

	int GetFullWidth(){ return this->WIDTH; }
	int GetFullHeight(){ return this->HEIGHT; }
	ITEM_INFO createItem(int posX, int posY);
	void getItemValues(sShape& ItemFigure);
	ITEM_INFO rotateShape(const ITEM_INFO &shape);
	bool checkEmptySpace(ITEM_INFO info);
	bool checkEmptySpace1(ITEM_INFO info);
};

extern Shapes cShape;