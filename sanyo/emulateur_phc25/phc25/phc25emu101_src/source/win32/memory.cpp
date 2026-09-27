//============================================================================
//  memory.cpp 「メモリ制御」 Win32 版
//----------------------------------------------------------------------------
//													Programmed by たご
//============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "../common/debug.h"
#include "memory.h"

#if 0 == MEMORY_MODE

// 変数定義
static int MallocHandle;
static const void *MallocAddress[ MEMORY_MAX ];
static const char *MallocFile[ MEMORY_MAX ];
static int MallocLine[ MEMORY_MAX ];
static size_t MallocSize[ MEMORY_MAX ];

//============================================================================
//	メモリ管理初期化
//============================================================================
void InitMemory( void )
{
}

//============================================================================
//	メモリ確保
//----------------------------------------------------------------------------
//In  : size = 確保するバイト数
//    : file = メモリ確保しているファイル名
//    : line = メモリ確保している行
//============================================================================
void* AllocateMemory( size_t size, const char *file, int line )
{
	void *memory;
	memory = malloc( size );
	MallocAddress[ MallocHandle ] = memory;
	MallocSize[ MallocHandle ] = size;
	MallocFile[ MallocHandle ] = file;
	MallocLine[ MallocHandle ] = line;
	MallocHandle++;
	if ( MallocHandle > MEMORY_MAX )
	{
		MallocHandle = 0;
	}
	return( memory );
}

//============================================================================
//	メモリ開放
//============================================================================
void FreeMemory( void *memory, const char *file, int line )
{
	int i;
	for ( i = 0; i < MEMORY_MAX; i ++ )
	{
		if ( MallocAddress[ i ] == memory )
		{
			MallocAddress[ i ] = NULL;
			break;
		}
	}
	free( memory );
}

//============================================================================
//	メモリ管理のチェック
// ※) ファイル名やパス名に \ を含む漢字がある場合は動作しません.
//============================================================================
void DisplayMemory( const char *file, int line )
{
	int i;
	size_t sum = 0;
	DEBUGOUT( "■メモリの開放状況\n" );
	DEBUGOUT( "file=%s\n", file );
	DEBUGOUT( "line=%d\n", line );
	for ( i = 0; i < MEMORY_MAX; i ++ )
	{
		if ( NULL == MallocAddress[ i ] )
		{
			continue;
		}
		char file[ 1024 ];
		bool find = false;
		int srcindex = (int)strlen( MallocFile[ i ] ) - 1;
		while( 0 <= srcindex -- )
		{
			if ( ( '\\' == MallocFile[ i ][ srcindex ] ) ||
				 ( '/' == MallocFile[ i ][ srcindex ] ) )
			{
				find = true;
				srcindex ++;
				break;
			}
		}
		if ( find )
		{
			strcpy( file, &MallocFile[ i ][ srcindex ] );
		}
		else
		{
			strcpy( file, MallocFile[ i ] );
		}
		DEBUGOUT( "%s の %d 行目で確保された %d バイト(%p) は未開放です.\n",
				 file,
				 MallocLine[ i ],
				 MallocSize[ i ],
				 MallocAddress[ i ] );
		sum += MallocSize[ i ];
	}
	DEBUGOUT( "開放していないメモリは %d バイトです.\n", sum );
}
#endif
