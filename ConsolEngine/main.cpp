// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

//#include "TestApp.h"
#include "Tetris.h"
#include <time.h>

void main ()
{
	srand((UINT)time(NULL));

	rand();

	Tetris app(15, 20);

	app.Run();
}
