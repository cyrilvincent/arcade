//============================================================================
//  debug.cpp 「デバッグ制御」 PS2EE/Win32 版
//----------------------------------------------------------------------------
//													Programmed by たご
//============================================================================
#include <stdarg.h>
#include <stdlib.h>
#include "debug.h"
#if defined _WIN32
#include <stdio.h>
#include <windows.h>
#if DEBUG_DIRECTX == 8
#include <dxerr8.h>
#elif DEBUG_DIRECTX == 9
#include <dxerr9.h>
#endif
#elif defined R5900
#include <stdio.h>
#include <sifdev.h>
#elif defined GBA
#include <stdio.h>
#include <string.h>
#include "gbaprint.h"
#elif defined SDK_ARM9
#ifndef CODE32
#define CODE32
#endif
#include <nitro.h>
#include <string.h>
#endif
#include "generic.h"

// -------------------- デバッグする場合のみコンパイルする
#if DEBUG_MODE != 0

// -------------------- 定義を解除する
#if DEBUG_NEWDELETE == 1
#undef new
#endif
#undef malloc
#undef free

// -------------------- スタティック領域
cDebug DebugMacro( DEBUG_OUTPUT );

#if DEBUG_NEWDELETE == 1
//===========================================================================
//  new
// 注) 例外は返しません
//===========================================================================
void* operator new( size_t size, const char* file, int line )
{
	void* ptr = DebugMacro.Malloc( size, file, line );
//	if ( NULL == ptr )
//	{
//		throw 1;
//	}
	return ptr;
}

//===========================================================================
//  new[]
// 注) 例外は返しません
//===========================================================================
void* operator new[]( size_t size, const char* file, int line )
{
	void* ptr = DebugMacro.Malloc( size, file, line );
//	if ( NULL == ptr )
//	{
//		throw 1;
//	}
	return ptr;
}

//===========================================================================
//  delete
//===========================================================================
void operator delete( void* ptr )
{
	DebugMacro.Free( ptr );
}

//===========================================================================
//  delete[]
//===========================================================================
void operator delete[]( void* ptr )
{
	DebugMacro.Free( ptr );
}
#endif

//===========================================================================
//  cDebug クラス
//===========================================================================

// -------------------- スタティック変数
int cDebug::StatCount = 0;
int cDebug::MallocHandle = 0;

#if DEBUG_MODE != 2
const void *cDebug::MallocAddress[ DEBUG_MEMORY_MAX ];
const char *cDebug::MallocFile[ DEBUG_MEMORY_MAX ];
int cDebug::MallocLine[ DEBUG_MEMORY_MAX ];
size_t cDebug::MallocSize[ DEBUG_MEMORY_MAX ];
#endif

//===========================================================================
//  コンストラクタ
//===========================================================================
cDebug::cDebug()
:OutputType( 0 )
{
	StatCount ++;
}

//===========================================================================
//  コンストラクタ
//---------------------------------------------------------------------------
// In  : type
//     :   0 = 標準出力(PS2), デバッグウインドウ(Win32)
//     :   1 = ファイル
//===========================================================================
cDebug::cDebug( int type )
:OutputType( type )
{
	if ( 0 == StatCount )
	{
		DeleteFile();
	}
	StatCount ++;
}

//===========================================================================
//  デストラクタ
//===========================================================================
cDebug::~cDebug()
{
	StatCount --;
}

//===========================================================================
//  出力先を選択する
//---------------------------------------------------------------------------
// In  : type
//     :   0 = 標準出力(PS2), デバッグウインドウ(Win32)
//     :   1 = ファイル
//===========================================================================
void cDebug::SetOutputType( int type )
{
	OutputType = type;
}

//===========================================================================
//  デバッグファイルを削除する
//===========================================================================
void cDebug::DeleteFile( void )
{
	#if defined _WIN32
		#if DEBUG_OUTPUT == 1
			char path[ _MAX_PATH ];
			if( GetModuleFileName( NULL, path, sizeof( path ) ) != 0 )
			{
				char drive[ _MAX_DRIVE ];
				char dir[ _MAX_DIR ];
				_splitpath( path, drive, dir, NULL, NULL );
				strcpy( path, drive );
				strcat( path, dir );
				strcat( path, DEBUG_FILE );
			}
			else
			{
				strcpy( path, DEBUG_FILE );
			}
			unlink( path );
		#endif
	#endif
}

//============================================================================
//	デバッグメッセージを出力する
//----------------------------------------------------------------------------
//In  : outputstring = 出力文字列
//============================================================================
void cDebug::Output( const char* outputstring, ... ) const
{
	char str[ 1000 ];
	va_list arglist;
	va_start( arglist, outputstring );
	(void)vsprintf( str, outputstring, arglist );
	va_end( arglist );
	if ( 0 == OutputType )
	{
		#if defined _WIN32
			OutputDebugString( (LPCTSTR)str );
		#elif defined GBA
			gbaprint( str );
		#elif defined SDK_ARM9
			OS_Printf( str );
		#else
			printf( str );
		#endif
	}
	else if ( 1 == OutputType )
	{
		#if defined R5900
			int fp;
			fp = sceOpen( DEBUG_FILE, ( SCE_CREAT | SCE_WRONLY ), 0777 );
			if ( fp >= 0 )
			{
				sceLseek( fp, 0, SCE_SEEK_END );
				sceWrite( fp, str, strlen( str ) + 1 );
				sceClose( fp );
			}
		#elif defined _WIN32
			FILE *fp;
			char path[ _MAX_PATH ];
			if( GetModuleFileName( NULL, path, sizeof( path ) ) != 0 )
			{
				char drive[ _MAX_DRIVE ];
				char dir[ _MAX_DIR ];
				_splitpath( path, drive, dir, NULL, NULL );
				strcpy( path, drive );
				strcat( path, dir );
				strcat( path, DEBUG_FILE );
			}
			else
			{
				strcpy( path, DEBUG_FILE );
			}
			// ファイルオープン
			fp = fopen( path, "r+" );
			if ( NULL == fp ) {
				// ファイル作成
				fp = fopen( path, "w+" );
			}
			if ( fp != NULL ) {
				fseek( fp, 0L, SEEK_END );
				fwrite( str, strlen( str ), 1, fp );
				fclose( fp );
			}
		#elif defined GBA
			gbaprint( str );
		#elif defined SDK_ARM9
			OS_Printf( str );
		#else
			FILE *fp;
			// ファイルオープン
			fp = fopen( DEBUG_FILE, "r+" );
			if ( NULL == fp )
			{
				// ファイル作成
				fp = fopen( DEBUG_FILE, "w+" );
			}
			if ( fp != NULL )
			{
				fseek( fp, 0L, SEEK_END );
				fwrite( str, strlen( str ), 1, fp );
				fclose( fp );
			}
		#endif
	}
}

//============================================================================
//	メモリをダンプ出力する
//----------------------------------------------------------------------------
//In  : mode
//    :   DEBUG_DUMP8  1 バイト表示
//    :   DEBUG_DUMP16 2 バイト表示
//    :   DEBUG_DUMP32 4 バイト表示
//============================================================================
void cDebug::OutputDump( const void *address, int width, int height, U32 mode ) const
{
	int x, y;
	const U8 *dump_address = (U8*)address;
	for ( y = 0; y < height; y ++ )
	{
		Output( "%08X", dump_address );
		Output( " : " );
		for ( x = 0; x < width; x++ )
		{
			if ( mode & DEBUG_DUMP8 )
			{
				Output( "%02X", *(U8*)dump_address );
				dump_address++;
			}
			else if ( mode & DEBUG_DUMP16 )
			{
				Output( "%04X", *(U16*)dump_address );
				dump_address += 2;
			}
			else
			{
				Output( "%08X", *(U32*)dump_address );
				dump_address += 4;
			}
			if ( x != width - 1 )
			{
				Output( " " );
			}
		}
		Output( "\n" );
	}
}

//============================================================================
//	DirectX のエラーを出力する
//----------------------------------------------------------------------------
//In  : result = DirectX のエラーコードへのポインタ
//============================================================================
void cDebug::OutputDxResult( void *result ) const
{
	#if defined _WIN32
	#if DEBUG_DIRECTX != 0
	char *str;
	char strtemp[ 1000 ];
	#if DEBUG_DIRECTX == 8
	str = (char*)DXGetErrorString8( *(HRESULT*)result );
	#elif DEBUG_DIRECTX == 9
	str = (char*)DXGetErrorString9( *(HRESULT*)result );
	#endif
	sprintf( strtemp, "戻り値 = 0x%08X (", (U64)*(HRESULT*)result );
	strcat( strtemp, str );
	strcat( strtemp, ")\n" );
	Output( strtemp );
	#endif
	#else
	void *temp;
	temp = result;
	#endif
}

#if DEBUG_MODE != 2
//============================================================================
//	メモリ確保 malloc 互換
//----------------------------------------------------------------------------
//In  : size = 確保するバイト数
//    : file = メモリ確保しているファイル名
//    : line = メモリ確保している行
//============================================================================
void* cDebug::Malloc( size_t size, const char *file, int line )
{
	void *memory;
	memory = malloc( size );
	MallocAddress[ MallocHandle ] = memory;
	MallocSize[ MallocHandle ] = size;
	MallocFile[ MallocHandle ] = file;
	MallocLine[ MallocHandle ] = line;
	MallocHandle ++;
	if ( MallocHandle > DEBUG_MEMORY_MAX )
	{
		MallocHandle = 0;
	}
	return( memory );
}

//============================================================================
//	メモリ開放 free 互換
//============================================================================
void cDebug::Free( void *memblock )
{
	int i;
	for ( i = 0; i < DEBUG_MEMORY_MAX; i ++ )
	{
		if ( MallocAddress[ i ] == memblock )
		{
			MallocAddress[ i ] = NULL;
			break;
		}
	}
	free( memblock );
}

//============================================================================
//	メモリ管理のチェック
// ※) ファイル名やパス名に \ を含む漢字がある場合は動作しません.
//============================================================================
void cDebug::MemoryStatus( void )
{
	char str[ 1024 ];
	int i;
	size_t sum = 0;
	Output( "■メモリの開放状況\n" );
	for ( i = 0; i < DEBUG_MEMORY_MAX; i ++ )
	{
		if( MallocAddress[ i ] != NULL )
		{
			char file[ 1024 ];
			bool find = false;
			int srcindex = (int)strlen( MallocFile[ i ] ) - 1;
			while( 0 <= srcindex-- )
			{
				if( ( '\\' == MallocFile[ i ][ srcindex ] ) ||
					 ( '/' == MallocFile[ i ][ srcindex ] ) )
				{
					find = true;
					srcindex++;
					break;
				}
			}
			if( find )
			{
				strcpy( file, &MallocFile[ i ][ srcindex ] );
			}
			else
			{
				strcpy( file, MallocFile[ i ] );
			}
			sprintf( str, "%s の %d 行目で確保された %d バイト(%p) は未開放です.\n",
					 file,
					 MallocLine[ i ],
					 MallocSize[ i ],
					 MallocAddress[ i ] );
			sum += MallocSize[ i ];
			Output( str );
		}
	}
	sprintf( str, "開放していないメモリは %d バイトです.\n", sum );
	Output( str );
}
#endif

// -------------------- デバッグする場合のみコンパイルする
#endif
