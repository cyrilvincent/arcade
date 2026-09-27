//============================================================================
//  system.h 「互換性のない部分を吸収する」
//----------------------------------------------------------------------------
//													Programmed by 多胡圭一
//============================================================================

// -------------------- 2 重定義防止
#ifndef INCLUDE_SYSTEM
#define INCLUDE_SYSTEM

// -------------------- ヘッダファイル登録
#include <windows.h>
#include "memory.h"
#define PAD_LEFT     0x00000004	// 左
#define PAD_DOWN     0x00000002	// 下
#define PAD_RIGHT    0x00000008	// 右
#define PAD_UP       0x00000001	// 上
#define PAD_BUTTON1  0x00000010	// ボタン 1

// メモリ
#define SystemMalloc(x) AllocateMemory(x,__FILE__, __LINE__)
#define SystemFree(x) FreeMemory(x,__FILE__, __LINE__)
#define SystemMemoryStatus() DisplayMemory(__FILE__,__LINE__)
//#define SystemMalloc(x) malloc(x)
//#define SystemFree(x) free(x)
//#define SystemMemoryStatus() ;
// システム
bool InitSystem( HWND window_handle );
void ReleaseSystem( void );
// 画面
void Flip( void );
void Clear( void );
void InitRender( void );
void ReleaseRender( void );
void Render( bool fullscreen );
void SetTV( bool tv );
bool GetTV( void );
// CPU
void RunCPU( void );
void ExecRETI( void );
bool ExecInterrupt( void );
void Reset( void );
// I/O ポート
unsigned char ReadIO_CPU( unsigned char laddr, unsigned char haddr );
void WriteIO_CPU( unsigned char laddr, unsigned char haddr, unsigned char val );
// キーボード
void SetKey( int code );
void ResetKey( int code );
// 仮想マシンのメモリ
void WriteMemoryByte( unsigned short addr, unsigned char val );
// プリンタ
void SetPrinter( void );
void WritePhcPrinter( int chr );
// テープ
void SetReadTape( void );
void SetWriteTape( void );
void WriteTape( int data );
int ReadTape( void );
void RewReadTape( void );
// 情報欄
void SetInformation( bool information );
bool GetInformation( void );
void SetInfomationMode( DWORD mode );
void ResetInfomationMode( DWORD mode );
void SetFps( float fps );
// PSG
void MakeSound( bool fill );
void UpdateSound( void );
void SetVolume( int volume );
int GetVolume( void );
void SetSound( int rate, int sample_count );
int GetSoundBuffer( void );
// ジョイパッド
DWORD GetStick( int player );
// 設定
void LoadSetting( void );
void SaveSetting( void );
void SetScreenScale( int scale );
int GetScreenScale( void );
void SetFullScreen( bool fullscreen );
bool GetFullScreen( void );
void SetFrameSkip( bool skip );
bool GetFrameSkip( void );

#endif
