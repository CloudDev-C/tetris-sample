#include "Tetris.h"
#include <time.h>
#include "CConsoleParam.h"
#include <conio.h>

#define MY_PERFORMENCE_COUNTER

Tetris::Tetris(int SizeX, int SizeY) : BaseApp(SizeX + 11, SizeY + 5)
{
	CConsoleParam::SetFontSize(8, 12, L"Terminal");

	this->matrix = new CMatrix(SizeX, SizeY);

	this->score = 0;

	this->time_wait = 0.6f;

	this->time_game = 0;

	this->GameStatus = true;

	this->currentShape = cShape.createItem(this->matrix->GetSizeX() / 2 - 1, 0);
	this->nextShape = cShape.createItem(this->matrix->GetSizeX() / 2 - 1, 0);
}


Tetris::~Tetris()
{
	delete matrix;
}

void Tetris::SetString(int x, int y, wchar_t *str)
{
	for (size_t i = 0; i < wcslen(str); i++)
	{
		SetChar(x+i, y, str[i]);
	}
}

void Tetris::KeyPressed(int btnCode)
{
	if (btnCode == 32 && time_wait != 0.05f) //w
	{
		ITEM_INFO tmp = cShape.rotateShape(this->currentShape);

		if(!this->ShapeCheck(tmp, tmp.x, tmp.y, false))
		{
			return;
		}

		this->currentShape = tmp;
	}

	if (btnCode == 224)
	{
		int key = _getch();

		if (key == 75)
		{
			if (this->ShapeCheck(this->currentShape, this->currentShape.x - 1, this->currentShape.y, false) && this->time_wait != 0.05f)
			{
				this->currentShape.x--;
			}
		}
		
		if (key == 77)
		{
			if (this->ShapeCheck(this->currentShape, this->currentShape.x + 1, this->currentShape.y, false) && this->time_wait != 0.05f)
			{
				this->currentShape.x++;
			}
		}

		if (key == 80)
		{
			this->time_wait = 0.05f;
		}
	}
}

void Tetris::UpdateF(float deltaTime)
{
	if (!GameStatus)
	{
		system("cls");
		ExitProcess(0);
	}

	for (int i = 0; i <= this->Y_SIZE; i++)
	{
		for (int j = 0; j <= this->X_SIZE; j++)
		{
			if (i == 0 || j == 0 || j == this->matrix->GetSizeX() +1 && i <= this->matrix->GetSizeY() + 1 || j == this->X_SIZE || i == this->Y_SIZE || i == this->matrix->GetSizeY() + 1 )
			{
				this->SetChar(j, i, L'#');
			}
			else
			{
				SetChar(j, i, L' ');
			}
		}
	}

	for (int i = 0; i < this->matrix->GetSizeY(); i++)
	{
		for (int j = 0; j < this->matrix->GetSizeX(); j++)
		{
			if (matrix->GetValue(j, i) == 0)
			{
				SetChar(j+1, i+1, L'.');
			}
			else
			{
				SetChar(j + 1, i + 1, L'◙');
			}
		}
	}

	for (int i = 0; i < cShape.GetFullHeight(); i++)
	{
		for (int j = 0; j < cShape.GetFullWidth(); j++)
		{
			if (this->nextShape.itemFigure.value[i][j])  //Next Shape
			{
				SetChar((this->X_SIZE - this->matrix->GetSizeX()) / 2 + j + this->matrix->GetSizeX(), 2+i, L'◙');
			}

			if (this->currentShape.itemFigure.value[i][j]) //Current Shape
			{
				SetChar(this->currentShape.x + j + 1, this->currentShape.y + i + 1, L'◙');
			}
		}
	}

	this->time_game += deltaTime;

	if (this->time_game > this->time_wait)
	{
		if (this->ShapeCheck(this->currentShape, this->currentShape.x, this->currentShape.y + 1, true))
		{
			this->currentShape.y++;
		}

		this->time_game = this->time_game - this->time_wait;
	}

	wchar_t Buff[MAX_PATH] = {};

	swprintf_s(Buff, L"> Score: %d", this->score);

	SetString(3, this->Y_SIZE-2, Buff);
}

void Tetris::AddToSquare()
{
	for (int i = 0; i < this->currentShape.itemFigure.height; i++)
	{
		for (int j = 0; j < this->currentShape.itemFigure.width; j++)
		{
			if (this->currentShape.itemFigure.value[i][j] == 1)
			{
				this->matrix->SetData(this->currentShape.x + j, this->currentShape.y + i, 1);
			}
		}
	}
}

bool Tetris::ShapeCheck(ITEM_INFO info, int x, int y, bool isNeedItemEnd)
{
	if (x < 0 || x + this->currentShape.itemFigure.width - 1 > this->matrix->GetSizeX())
	{
		return false;
	}

	for (int i = 0; i < info.itemFigure.height; i++)
	{
		for (int j = 0; j < info.itemFigure.width; j++)
		{
			if (y < 0 || y + this->currentShape.itemFigure.height - 1 >= this->matrix->GetSizeY())
			{
				if (isNeedItemEnd)
				{
					this->EndShape();
				}

				return false;
			}
			else if (this->matrix->GetValue(x + j, y + i) && info.itemFigure.value[i][j] == 1)
			{
				if (isNeedItemEnd)
				{
					this->EndShape();
				}

				return false;
			}
		}
	}

	return true;
}

void Tetris::DelLine(int index)
{
	if (index >= 0 && index < this->matrix->GetSizeY())
	{
		for (int i = 0; i < this->matrix->GetSizeX(); i++)
		{
			this->matrix->SetData(i, index, 0);
		}
	}

	for (int i = index - 1; i != 0 ; i--)
	{
		for (int j = 0; j < this->matrix->GetSizeX(); j++)
		{
			this->matrix->SetData(j, i + 1, this->matrix->GetValue(j, i));
		}
	}
}

bool Tetris::CheckLine()
{
	for (int i = 0; i < this->matrix->GetSizeY(); i++)
	{
		int count = 0;

		for (int j = 0; j < this->matrix->GetSizeX(); j++)
		{
			if (this->matrix->GetValue(j, i))
			{
				count++;
			}
		}

		if (count == this->matrix->GetSizeX())
		{
			this->score += 100;
			DelLine(i);
			CheckLine();
			return true;
		}
	}

	return false;
}

void Tetris::EndShape()
{
	this->AddToSquare();

	this->currentShape = this->nextShape;
	this->nextShape = cShape.createItem(this->matrix->GetSizeX() / 2 - 1, 0);

	this->time_wait = 0.6f;

	this->CheckLine();

	if (!this->ShapeCheck(currentShape, currentShape.x, currentShape.y, false))
	{
		this->GameStatus = false;
	}
}