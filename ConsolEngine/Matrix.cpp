#include "Matrix.h"

CMatrix::CMatrix(int sizeX, int sizeY)
{
	this->SizeX = sizeX;
	this->SizeY = sizeY;

	this->Data = new int*[this->SizeY];

	for (int i = 0; i < this->SizeY; i++)
	{
		this->Data[i] = new int[this->SizeX]{};
	}
}

CMatrix::~CMatrix()
{
	for (int i = 0; i < this->SizeY; i++)
	{
		delete[] this->Data[i];
	}

	delete[] this->Data;
}

int CMatrix::GetSizeX()
{
	return this->SizeX;
}

int CMatrix::GetSizeY()
{
	return this->SizeY;
}

int ** CMatrix::GetData() const
{
	return Data;
}

void CMatrix::SetData(int x, int y, int value)
{
	if (x >= 0 && x < this->SizeX && y >= 0 && y < this->SizeY)
	{
		this->Data[y][x] = value;
	}
}

const int CMatrix::GetValue(int x, int y) const
{
	if (x >= 0 && x < this->SizeX && y >= 0 && y < this->SizeY)
	{
		return this->Data[y][x];
	}

	return -1;
}
