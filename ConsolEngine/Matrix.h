#pragma once

class CMatrix
{
	int SizeX;
	int SizeY;
	int **Data;

	CMatrix() = delete;

public:
	CMatrix(int sizeX, int sizeY);

	~CMatrix();

	int GetSizeX();

	int GetSizeY();

	int ** GetData() const;

	void SetData(int x, int y, int value);

	const int GetValue(int x, int y) const;
};
