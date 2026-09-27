//============================================================================
//  debug.h 「デバッグ制御ヘッダファイル」 PS2/Win32/GBA/NDS 版
//----------------------------------------------------------------------------
//													Programmed by たご
//----------------------------------------------------------------------------
// 2004.06.29 Ver.1.12 NDS でワーニングが出るのを修正した。
// 2004.06.14 Ver.1.11 出力ファイル名を report.txt に変更した.
//                     DEBUGFILECLEAR() を追加した。
// 2004.05.28 Ver.1.10 下記の修正に機種依存があったので修正した.
// 2004.05.26 Ver.1.09 DEBUG.TXT が実行ファイルと同じ場所になるように修正した.
// 2004.02.23 Ver.1.08 malloc のサイズを int から size_t に変更した.
// 2004.02.18 Ver.1.07 DirectX のエラー文字列がおかしかったので修正した.
// 2003.07.11 Ver.1.06 1.05 が VC.NET でコンパイルできないので修正した.
// 2003.07.10 Ver.1.05 1.04 が GBA でコンパイルできないので修正した.
// 2003.06.26 Ver.1.04 VC でコンパイルするとワーニングが出るのを修正した.
// 2003.05.28 Ver.1.03 new/delete はデフォルトでオーバーロードしない.
//                     (new/delete の使い方自体間違っている.これらはオーバーロ
//                     ードしてはいけない)
//                     GBA に対応した.GBA コンパイルは -DGBA オプション必須.
// 2003.05.06 Ver.1.02 PS2EE でファイル書き込みに対応した.
// 2003.02.21 Ver.1.01 内部カウンタが 0 の時だけファイルを削除するようにした.
//                     メモリ関係のデバッグ用にファイル名と行数を記憶した.
//                     new/delete をオーバーロードした.
// 2003.02.20 Ver.1.00 作成開始.
//============================================================================
#ifndef DEBUG_H
#define DEBUG_H

// -------------------- ヘッダファイル登録
#if defined R5900
#include <stdio.h>
#endif
#include "generic.h"

// デバッグ (0=しない,1=する,2=出力のみ)
#define DEBUG_MODE 2
// 出力先 (0=標準出力(PS2),デバッグウインドウ(Win32),1=ファイル)
#define DEBUG_OUTPUT 0
// DirectX のバージョン (0=デバッグしない,8 と 9 のみ指定可能)
#define DEBUG_DIRECTX 0
// New/delete をオーバーロード (0=しない, 1=する)
#define DEBUG_NEWDELETE 0

// -------------------- リンクライブラリの指定
#if defined _WIN32
#if DEBUG_DIRECTX == 8
#pragma comment( lib, "dxerr8.lib" )
#elif DEBUG_DIRECTX == 9
#pragma comment( lib, "dxerr9.lib" )
#endif
#endif

// -------------------- 定数定義
#if defined GBA
static const int DEBUG_MEMORY_MAX = 256;					// メモリ確保監視最大数 GBA
#else
static const int DEBUG_MEMORY_MAX = 65536;					// メモリ確保監視最大数 Win32/PS2
#endif

#if defined R5900
static const char* const DEBUG_FILE = "host0:report.txt";	// PS2EE デバッグ出力時のファイル名
#else
static const char* const DEBUG_FILE = "report.txt";			// デバッグ出力時のファイル名
#endif
static const U32 DEBUG_10 = 0;
static const U32 DEBUG_16 = 1;
static const U32 DEBUG_DUMP8  = 0x00000001;
static const U32 DEBUG_DUMP16 = 0x00000002;
static const U32 DEBUG_DUMP32 = 0x00000004;

#if DEBUG_MODE == 1
#if DEBUG_NEWDELETE == 1
// -------------------- オーバーライド
void* operator new( size_t size, const char* file, int line );
void* operator new[]( size_t size, const char* file, int line );
void operator delete( void* ptr );
void operator delete[]( void* ptr );
#endif
#endif

#if DEBUG_MODE != 0
// -------------------- クラス定義
class cDebug {
	public:
		cDebug( void );
		cDebug( int type );
		~cDebug( void );
		// デバッグ出力
		void DeleteFile( void );
		void SetOutputType( int type );
		void Output( const char* outputstring, ... ) const;
		void OutputDump( const void *address, int width, int height, U32 mode ) const;
		// DirectX
		void OutputDxResult( void *result ) const;
		// メモリ管理
		void* Malloc( size_t size, const char *file, int line );
		void Free( void *memblock );
		void MemoryStatus( void );
	private:
		// 常駐回数
		static int StatCount;
		// 出力
		int OutputType;
		// メモリ管理
		static int MallocHandle;
		static const void *MallocAddress[ DEBUG_MEMORY_MAX ];
		static const char *MallocFile[ DEBUG_MEMORY_MAX ];
		static int MallocLine[ DEBUG_MEMORY_MAX ];
		static size_t MallocSize[ DEBUG_MEMORY_MAX ];
		// 代入禁止
		cDebug( cDebug& debug );
		cDebug& operator = ( const cDebug &debug );
};
#endif

// -------------------- デバッグしない
#if DEBUG_MODE == 0
#define DEBUGINIT( x )             ;
#define DEBUGFILECLEAR             ;
#define DEBUGOUTMODE( x )          ;
#define DEBUGOUT( x )              ;
#define DEBUGOUTDUMP( a, w, h )    ;
#define DEBUGDX( x )               ;
#define MEMORYSTATE()              ;
// -------------------- すべて
#elif DEBUG_MODE == 1
#define DEBUGINIT( x )             cDebug DebugMacro( x )
#define DEBUGFILECLEAR             DebugMacro.DeleteFile
#define DEBUGOUTTYPE( x )          DebugMacro.OutputType( x )
#define DEBUGOUT                   DebugMacro.Output
#define DEBUGOUTDUMP( a, w, h )    DebugMacro.OutputDump( a, w, h, DEBUG_DUMP8 )
#define DEBUGDX( x )               DebugMacro.OutputDxResult( (void*)&x )
#define malloc( x )                DebugMacro.Malloc( x, __FILE__, __LINE__ )
#define free( x )                  DebugMacro.Free( x )
#define MEMORYSTATE()              DebugMacro.MemoryStatus()
#if DEBUG_NEWDELETE == 1
#define new                        new( __FILE__, __LINE__ )
#endif

// -------------------- 出力のみ
#elif DEBUG_MODE == 2
#define DEBUGINIT( x )             cDebug DebugMacro( x )
#define DEBUGFILECLEAR             DebugMacro.DeleteFile
#define DEBUGOUTTYPE( x )          DebugMacro.OutputType( x )
#define DEBUGOUT                   DebugMacro.Output
#define DEBUGOUTDUMP( a, w, h )    DebugMacro.OutputDump( a, w, h, DEBUG_DUMP8 )
#define DEBUGDX( x )               DebugMacro.OutputDxResult( (void*)&x )
#define MEMORYSTATE()              ;
#endif

// -------------------- 他のファイルから参照可
extern cDebug DebugMacro;

#endif
