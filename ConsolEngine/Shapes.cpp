#include "Shapes.h"

Shapes cShape;

Shapes::Shapes() : WIDTH(SHAPE_WIDTH), HEIGHT(SHAPE_HEIGHT)
{
	this->Init(shape1, 0);
	this->Init(shape2, 1);
	this->Init(shape3, 2);
	this->Init(shape4, 3);
	this->Init(shape5, 4);
	this->Init(shape6, 5);
	this->Init(shape7, 6);
}

void Shapes::Init(const int temp[SHAPE_HEIGHT][SHAPE_WIDTH], int id)
{
	for (size_t i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (size_t j = 0; j < SHAPE_WIDTH; j++)
		{
			data[id].value[i][j] = temp[i][j];
		}
	}

	getItemValues(data[id]);
}

ITEM_INFO Shapes::createItem(int posX, int posY)
{
	int type = rand() % SHAPE_COUNT;

	ITEM_INFO info;
	info.itemFigure = this->data[type];
	info.x = posX;
	info.y = posY;
	info.type = type;
	return info;
}

void Shapes::getItemValues(sShape& ItemFigure)
{
	int width = 0;
	int height = 0;

	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WIDTH; j++)
		{
			if (ItemFigure.value[i][j] != 0)
			{
				height++;
				break;
			}
		}
	}


	for (int j = 0; j < SHAPE_HEIGHT; j++)
	{
		for (int i = 0; i < SHAPE_WIDTH; i++)
		{
			if (ItemFigure.value[i][j] != 0)
			{
				width++;
				break;
			}
		}
	}

	ItemFigure.width = width;
	ItemFigure.height = height;
}

ITEM_INFO Shapes::rotateShape(const ITEM_INFO &shape)
{
	ITEM_INFO tempItem = shape;

	int temp[SHAPE_HEIGHT][SHAPE_WIDTH] = {};

	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WIDTH; j++)
		{
			temp[i][j] = tempItem.itemFigure.value[j][(SHAPE_HEIGHT - 1) - i];
		}
	}

	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		for (int j = 0; j < SHAPE_WIDTH; j++)
		{
			tempItem.itemFigure.value[i][j] = temp[i][j];
			temp[i][j] = 0;
		}
	}

	while (!checkEmptySpace(tempItem))
	{
		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WIDTH; j++)
			{
				if (tempItem.itemFigure.value[i][j] == 1)
				{
					temp[i][j - 1] = tempItem.itemFigure.value[i][j];
				}
			}
		}

		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WIDTH; j++)
			{
				tempItem.itemFigure.value[i][j] = temp[i][j];
				temp[i][j] = 0;
			}
		}
	}

	while (!checkEmptySpace1(tempItem))
	{
		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WIDTH; j++)
			{
				if (tempItem.itemFigure.value[i][j] == 1)
				{
					temp[i - 1][j] = tempItem.itemFigure.value[i][j];
				}
			}
		}

		for (int i = 0; i < SHAPE_HEIGHT; i++)
		{
			for (int j = 0; j < SHAPE_WIDTH; j++)
			{
				tempItem.itemFigure.value[i][j] = temp[i][j];
				temp[i][j] = 0;
			}
		}
	}

	double x0 = shape.x-1 + shape.itemFigure.width / 2;
	double y0 = shape.y-1 + shape.itemFigure.height / 2;

	double X = x0 + (shape.x - x0) * cos(90) - (shape.y - y0) * sin(90);
	double Y = y0 + (shape.y - y0) * cos(90) + (shape.x - x0) * sin(90);


	tempItem.x = round(X);
	tempItem.y = round(Y);

	this->getItemValues(tempItem.itemFigure);

	return tempItem;
}

bool Shapes::checkEmptySpace(ITEM_INFO info)
{
	int tmp = 0;

	for (int i = 0; i < SHAPE_HEIGHT; i++)
	{
		if (info.itemFigure.value[i][0] > tmp)
		{
			tmp = info.itemFigure.value[i][0];
		}
	}

	return tmp > 0 ? true : false;
}

bool Shapes::checkEmptySpace1(ITEM_INFO info)
{
	int tmp = 0;

	for (int i = 0; i < SHAPE_WIDTH; i++)
	{
		if (info.itemFigure.value[0][i] > tmp)
		{
			tmp = info.itemFigure.value[0][i];
		}
	}

	return tmp > 0 ? true : false;
}