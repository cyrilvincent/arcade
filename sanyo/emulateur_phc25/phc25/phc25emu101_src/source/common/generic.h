//============================================================================
//  generic.h 型定義ヘッダファイル  PS2EE/PS2IOP/PS1/GBA/ポケステ/Win32 版
//----------------------------------------------------------------------------
//													Programmed by 多胡圭一
//----------------------------------------------------------------------------
//※ リトルエンディアン専用 (x86、EE、IOP、ARM など)
//   ポケステは未完成
//----------------------------------------------------------------------------
// 2004.06.16 Ver.1.08 define から typrdef に変更した。NDS 対応。
// 2004.02.23 Ver.1.07 bool 定義を削除した。
// 2003.07.29 Ver.1.06 不要な定数を削除した。UxxDATA を整理した。
// 2003.06.26 Ver.1.05 GBA コンパイルは -DGBA オプション必須。
// 2003.04.24 Ver.1.04 NULL を定義した。
// 2003.04.08 Ver.1.03 GBA に対応した。
// 2003.02.20 Ver.1.02 bool 定義。
// 2003.02.20 Ver.1.01 IOP に対応。細かい最適化。
// 2003.02.14 Ver.1.00 ktDefine.h のファイル名を変更。PS2EE に対応。
//============================================================================
#ifndef GENERIC_INCLUDE
#define GENERIC_INCLUDE

// -------------------- ヘッダファイル登録
#if defined _WIN32
	#include <windows.h>
#elif defined R5900
	#include <eetypes.h>
#elif defined R3000
	#include <sys/types.h>
#elif defined SDK_ARM9
	#include <nitro.h>
#endif

// -------------------- 機種別定義
#if defined _WIN32
// Win32 型定義
typedef char				S8;
typedef short				S16;
typedef long				S32;
typedef __int64				S64;
typedef unsigned char		U8;
typedef unsigned short		U16;
typedef unsigned long		U32;
typedef unsigned __int64	U64;
#elif defined R5900
// PS2EE 型定義
typedef char				S8;
typedef	short				S16;
typedef	int					S32;
typedef	long				S64;
typedef	long128				S128;
typedef unsigned char		U8;
typedef	unsigned short		U16;
typedef	unsigned int		U32;
typedef	unsigned long		U64;
typedef	u_long128			U128;
#elif defined R3000
// PS1/PS2IOP 型定義
typedef	char				S8;
typedef	short				S16;
typedef	int					S32;
typedef	long				S64;
typedef	unsigned char		S8;
typedef	unsigned short		S16;
typedef	unsigned int		S32;
typedef	unsigned long		S64;
#elif defined GBA
// GBA 型定義
typedef	char				S8;
typedef	short				S16;
typedef	long				S32;
typedef	unsigned char		U8;
typedef	unsigned short		U16;
typedef	unsigned long		U32;
#elif defined SDK_ARM9
// NDS 型定義
typedef	signed char				S8;
typedef	signed short int		S16;
typedef	signed long				S32;
typedef	signed long long int	S64;
typedef	unsigned char			U8;
typedef	unsigned short int		U16;
typedef	unsigned long			U32;
typedef	unsigned long long int	U64;
#endif

// Windows に合わせる
#ifndef _WIN32
typedef	U8	BYTE;
typedef U8	*LPBYTE;
typedef U16	WORD;
typedef U16	*LPWORD;
typedef U32	DWORD;
typedef U32	*LPDWORD;
#endif

// BOOL 定義
#ifndef BOOL
#define BOOL  int
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE  1
#endif

// NULL 定義
#ifndef NULL
#define NULL 0
#endif

#endif
