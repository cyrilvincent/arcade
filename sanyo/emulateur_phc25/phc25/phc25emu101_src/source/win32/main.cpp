//============================================================================
//  main.cpp 「メインルーチン」
//----------------------------------------------------------------------------
//													Programmed by 多胡圭一
//============================================================================
#include "main.h"
#include "../common/debug.h"
#include "system.h"

void InitMain( void )
{
	InitRender();
	Clear();
}

void ReleaseMain( void )
{
	ReleaseRender();
}

// Out  : false = 継続, true = 終了
bool Main( void )
{
	Flip();
	Clear();
	RunCPU();
	return false;
}
