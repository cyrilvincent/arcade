//============================================================================
//  memory.h 「メモリ制御」 Win32 版
//----------------------------------------------------------------------------
//													Programmed by たご
//----------------------------------------------------------------------------
// 2004.02.23 Ver.1.00 作成.
//============================================================================
#ifndef DEFINE_MEMORY
#define DEFINE_MEMORY

// -------------------- 定数定義
#define MEMORY_MODE 0		// 0=デバッグ付き, 1=malloc/free
#define MEMORY_MAX 65536

// 関数定義
void InitMemory( void );
void* AllocateMemory( size_t size, const char *file, int line );
void FreeMemory( void *memory, const char *file, int line );
void DisplayMemory( const char *file, int line );

#endif
