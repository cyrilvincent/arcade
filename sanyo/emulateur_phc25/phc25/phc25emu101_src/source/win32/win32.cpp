//============================================================================
//  win32.cpp 「ウインドウ制御プログラム」
//----------------------------------------------------------------------------
//													Programmed by 多胡圭一
//----------------------------------------------------------------------------
// ※ win32.h、win32.rc、resource.h が必要です。
//----------------------------------------------------------------------------
// 2004.02.13 R.P.G の Win32.cpp を修正して汎用に使えるようにした。
//============================================================================
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include "../common/debug.h"
#include "../win32/main.h"
#include "system.h"
#include "win32.h"
#include "resource.h"

// -------------------- リンクライブラリの指定
#pragma comment( lib, "Winmm.lib" )

#define MAX_LOADSTRING 100

#define MENU_SCREENSIZE  0
#define MENU_FRAMESKIP   1
#define MENU_VOLUME      2
#define MENU_SOUNDBUFFER 3

//-------------------- グローバル変数
HINSTANCE Instance;						// 現在のインスタンス
HWND Wnd;								// ウインドウのハンドル
TCHAR Title[ MAX_LOADSTRING ];			// タイトル バー テキスト
TCHAR WindowClass[ MAX_LOADSTRING ];	// タイトル バー テキスト
DWORD ScreenWidth;		// ウインドウの幅
DWORD ScreenHeight;		// ウインドウの高さ
DWORD ScreenColor;		// 色数 (8, 16, 24, 32)
DWORD ScreenMode;		// 画面モード
int ActiveWindow;		// 現在ウインドウがアクティブになっているか
int SmallWindow;		// 現在ウインドウが最小化になっているか
RECT WindowPosition;	// ウインドウの位置
HMENU Menu;
DWORD WindowStyle;
// フルスクリーン
LONG Style = WS_VISIBLE;
int DestX = 0;
int DestY = 0;

//-------------------- ローカル関数
int APIENTRY WinMain( HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show );
int InitWindow( HINSTANCE instance, int cmd_show, int width, int height );
LRESULT CALLBACK WndProc( HWND wnd, UINT message, WPARAM wparam, LPARAM lparam );
void SetWindowSize( int width, int height );
void ResetMenuCheck( int type );
void InitSetting( void );
LRESULT CALLBACK About( HWND dlg, UINT message, WPARAM wparam, LPARAM lparam );
void AnlyzeOption( char *cmd_line );
int GetKeyData( char *pOption, char *pKey );
int GetNumeral10( char *pData );
void PrintErrorMessage( void );

//============================================================================
//  WinMain 関数
//============================================================================
int APIENTRY WinMain( HINSTANCE instance, HINSTANCE prev_instance, LPSTR cmd_line, int cmd_show )
{
	DEBUGFILECLEAR();
	MSG msg;
	HACCEL accel_table;
	DWORD time;
	DWORD old_time;
	DWORD diff_time;
	int sum_time = 0;
	int frame_count = 0;
	// 変数初期化
	ActiveWindow = 0;
	SmallWindow = 0;
	// オプション
//	char *option_test = "/WIDTH=640 /HEIGHT=480";
//	cmd_line = option_test;	// デバッグオプション文字列登録
	AnlyzeOption( (char*)cmd_line );
	// グローバル ストリングを初期化します
	LoadString( instance, IDS_APP_TITLE, Title, MAX_LOADSTRING );
	LoadString( instance, IDC_KEY, WindowClass, MAX_LOADSTRING );
	// ウインドウの初期化
	DEBUGOUT( "■■■■■アプリケーション開始\n" );
	if( 0 == InitWindow( instance, cmd_show, ScreenWidth, ScreenHeight ) )
	{
		DEBUGOUT( "ウインドウの初期化に失敗しました.\n" );
		return 0;
	}
	// キーボードアクセラレータテーブルをロードする
	accel_table = LoadAccelerators( instance, (LPCTSTR)IDC_KEY );
	// COM ライブラリの初期化
	if( FAILED( CoInitialize( NULL ) ) )
	{
		DEBUGOUT( "COM ライブラリの初期化に失敗しました.\n" );
		return 0;
	}
	if( false == InitSystem( Wnd ) )
	{
		DEBUGOUT( "システムライブラリの初期化に失敗しました.\n" );
		return 0;
	}
	InitMain();
	InitSetting();
	old_time = timeGetTime();
	for( ; ; )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
		{
			if( FALSE == GetMessage( &msg, NULL, 0, 0 ) )
			{
				break;
			}
			if( FALSE == TranslateAccelerator( msg.hwnd, accel_table, &msg ) )
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			if( 0 == SmallWindow )
			{

				time = timeGetTime();
				diff_time = time - old_time;
				if( diff_time > 16 )
				{
					int i;
					int loop = 1;
					InvalidateRect( Wnd, NULL, FALSE );
					UpdateWindow( Wnd );
					if( GetFrameSkip() )
					{
						loop = diff_time / 16;
						if( loop > 10 )
						{
							loop = 10;
						}
					}
					for( i = 0; i < loop; i ++ )
					{
						if( Main() )
						{
							DestroyWindow( Wnd );
						}
					}
					old_time = time;
					sum_time += (int)diff_time;
					frame_count ++;
				}
				if( sum_time > 1000 )
				{
					float fps;
					fps =  ( 1000.0f * ( float )frame_count ) / ( float )sum_time;
					SetFps( fps );
					frame_count = 0;
					sum_time = 0;
				}
				Sleep( 0 );
			}
		}
	}
	// プログラム終了
	ReleaseMain();
	ReleaseSystem();
	// COM ライブラリを閉じる
	CoUninitialize();
	return (int)msg.wParam;
}

//============================================================================
//	Window の初期化
//----------------------------------------------------------------------------
// In  : width = 横の大きさ
//     : height = 縦の大きさ
// Out : 1 = 成功 / 0 = 失敗
//============================================================================
int InitWindow( HINSTANCE instance, int cmd_show, int width, int height )
{
	WNDCLASSEX wcex;
	int window_width;
	int window_height;
	// グローバル変数にインスタンスハンドルを保存します
	Instance = instance;
	// ウインドウクラスの定義
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= instance;
	wcex.hIcon			= LoadIcon( instance, (LPCTSTR)IDI_ICON );
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)( COLOR_WINDOW + 1 );
	wcex.lpszMenuName	= (LPCSTR)IDC_MENU;
	wcex.lpszClassName	= WindowClass;
	wcex.hIconSm		= LoadIcon( wcex.hInstance, (LPCTSTR)IDI_SMALL );
	RegisterClassEx( &wcex );
	// ウインドウのスタイル設定
	WindowStyle = WS_OVERLAPPEDWINDOW;
	// ウインドウの大きさを補正する
    window_width = width;
    window_height = height;
	window_width += ( GetSystemMetrics( SM_CXSIZEFRAME ) * 2 );
	window_height += ( GetSystemMetrics( SM_CYSIZEFRAME ) * 2 + GetSystemMetrics( SM_CYMENU ) + GetSystemMetrics( SM_CYCAPTION ) );
	// ウインドウ作成
	Wnd = CreateWindow( WindowClass,
						Title,
						WindowStyle,
						CW_USEDEFAULT, CW_USEDEFAULT,
						window_width, window_height,
						NULL, NULL, instance, NULL );
	if( !Wnd )
	{
		return 0;
	}
	ShowWindow( Wnd, cmd_show );
	UpdateWindow( Wnd );
	// メニューハンドルの保存
	Menu = GetMenu( Wnd );
	// ウインドウの座標を保存する
	GetWindowRect( Wnd, &WindowPosition );
	return 1;
}

void SetWindow( bool fullscreen )
{
	if( fullscreen && !GetFullScreen() )
	{
		// フルスクリーンに移行
		DEVMODE devmode;
		HDC hdc = GetDC( NULL );
		ZeroMemory( &devmode, sizeof( devmode ) );
		devmode.dmSize = sizeof( devmode );
		devmode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		devmode.dmBitsPerPel = GetDeviceCaps( hdc, BITSPIXEL );
		devmode.dmPelsWidth = 320;
		devmode.dmPelsHeight = 240;
		ReleaseDC( NULL, hdc );
		if( DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings( &devmode, CDS_TEST ) )
		{
			WINDOWPLACEMENT place;
			SetMenu( Wnd, NULL );
			place.length = sizeof( WINDOWPLACEMENT );
			GetWindowPlacement( Wnd, &place );
			DestX = place.rcNormalPosition.left;
			DestY = place.rcNormalPosition.top;
			ChangeDisplaySettings( &devmode, CDS_FULLSCREEN );
			Style = GetWindowLong( Wnd, GWL_STYLE );
			SetWindowLong( Wnd, GWL_STYLE, WS_VISIBLE );
			SetWindowPos( Wnd, HWND_TOP, 0, 0, 320, 240, SWP_SHOWWINDOW );
			SetCursorPos( 320, 240 );
			SetFullScreen( true );
		}
	}
	else if( !fullscreen && GetFullScreen() )
	{
		// フルスクリーンから復帰
		RECT rect =
		{
			0, 0, 0, 0
		};
		rect.right = ScreenWidth;
		rect.bottom = ScreenHeight;
		SetMenu( Wnd, Menu );
		AdjustWindowRect( &rect, WindowStyle, TRUE );
		ChangeDisplaySettings( NULL, 0 );
		SetWindowLong( Wnd, GWL_STYLE, Style );
		SetWindowPos( Wnd, HWND_BOTTOM, DestX, DestY, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW );
		SetFullScreen( false );
	}
}

//============================================================================
//	メイン ウィンドウのメッセージ処理
//----------------------------------------------------------------------------
// In  :
// Out :
//============================================================================
LRESULT CALLBACK WndProc( HWND wnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	int wm_id;
	int wm_event;
	switch( message )
	{
		case WM_ACTIVATEAPP:
			if( ( WA_ACTIVE == wparam ) || ( WA_CLICKACTIVE == wparam ) )
			{
				ActiveWindow = 1;
				SmallWindow = 0;
				InvalidateRect( wnd, NULL, FALSE );
				UpdateWindow( wnd );
			}
			else
			{
				ActiveWindow = 0;
			}
			break;
		case WM_SETCURSOR:
			if ( GetFullScreen() )
			{
				SetCursor( NULL );
			}
			break;
		case WM_COMMAND:
			wm_id = LOWORD( wparam );
			wm_event = HIWORD( wparam );
			// メニュー選択の解析:
			switch( wm_id )
			{
				case ID_SET_READTAPE:
					SetReadTape();
					break;
				case ID_REW_READTAPE:
					RewReadTape();
					break;
				case ID_SET_WRITETAPE:
					SetWriteTape();
					break;
				case ID_RESET:
					Reset();
					break;
				case IDM_EXIT:
					DestroyWindow( wnd );
					break;
				case ID_WINDOWSIZEx1:
					ResetMenuCheck( MENU_SCREENSIZE );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetWindow( false );
					SetWindowSize( ScreenWidth, ScreenHeight );
					SetScreenScale( 1 );
					break;
				case ID_WINDOWSIZEx2:
					ResetMenuCheck( MENU_SCREENSIZE );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetWindow( false );
					SetWindowSize( ScreenWidth * 2, ScreenHeight * 2 );
					SetScreenScale( 2 );
					break;
				case ID_WINDOWSIZEx3:
					ResetMenuCheck( MENU_SCREENSIZE );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetWindow( false );
					SetWindowSize( ScreenWidth * 3, ScreenHeight * 3 );
					SetScreenScale( 3 );
					break;
				case ID_WINDOWSIZEx4:
					ResetMenuCheck( MENU_SCREENSIZE );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetWindow( false );
					SetWindowSize( ScreenWidth * 4, ScreenHeight * 4 );
					SetScreenScale( 4 );
					break;
				case ID_FULLSCREEN:
				case IDM_CHANGESCREEN:
					if( GetFullScreen() )
					{
						ResetMenuCheck( MENU_SCREENSIZE );
						SetWindow( false );
						SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
						SetFullScreen( false );
						switch( GetScreenScale() )
						{
							case 1:
								CheckMenuItem( Menu, ID_WINDOWSIZEx1, MF_BYCOMMAND | MF_CHECKED );
								break;
							case 2:
								CheckMenuItem( Menu, ID_WINDOWSIZEx2, MF_BYCOMMAND | MF_CHECKED );
								break;
							case 3:
								CheckMenuItem( Menu, ID_WINDOWSIZEx3, MF_BYCOMMAND | MF_CHECKED );
								break;
							case 4:
								CheckMenuItem( Menu, ID_WINDOWSIZEx4, MF_BYCOMMAND | MF_CHECKED );
								break;
						}
					}
					else
					{
						ResetMenuCheck( MENU_SCREENSIZE );
						SetWindow( true );
						CheckMenuItem( Menu, ID_FULLSCREEN, MF_BYCOMMAND | MF_CHECKED );
						SetFullScreen( true );
					}
					break;
				case ID_FRAMESKIP_ON:
					SetFrameSkip( true );
					ResetMenuCheck( MENU_FRAMESKIP );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					break;
				case ID_FRAMESKIP_OFF:
					SetFrameSkip( false );
					ResetMenuCheck( MENU_FRAMESKIP );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					break;
				case ID_DRAW_STATUS:
					if( GetFullScreen() )
					{
						if( GetInformation() )
						{
							CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_UNCHECKED );
							SetInformation( false );
							ScreenHeight = 192;
						}
						else
						{
							CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_CHECKED );
							SetInformation( true );
							ScreenHeight = 192 + 12;
						}
					}
					else
					{
						if( GetInformation() )
						{
							CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_UNCHECKED );
							SetInformation( false );
							ScreenHeight = 192;
							SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
						}
						else
						{
							CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_CHECKED );
							SetInformation( true );
							ScreenHeight = 192 + 12;
							SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
						}
					}
					break;
				case ID_DRAW_TV:
					if( GetTV() )
					{
						CheckMenuItem( Menu, ID_DRAW_TV, MF_BYCOMMAND | MF_UNCHECKED );
						SetTV( false );
					}
					else
					{
						CheckMenuItem( Menu, ID_DRAW_TV, MF_BYCOMMAND | MF_CHECKED );
						SetTV( true );
					}
					break;
				case ID_SOUND_VOL100:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 100 );
					break;
				case ID_SOUND_VOL90:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 90 );
					break;
				case ID_SOUND_VOL80:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 80 );
					break;
				case ID_SOUND_VOL70:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 70 );
					break;
				case ID_SOUND_VOL60:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 60 );
					break;
				case ID_SOUND_VOL50:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 50 );
					break;
				case ID_SOUND_VOL40:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 40 );
					break;
				case ID_SOUND_VOL30:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 30 );
					break;
				case ID_SOUND_VOL20:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 20 );
					break;
				case ID_SOUND_VOL10:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 10 );
					break;
				case ID_SOUND_MUTE:
					ResetMenuCheck( MENU_VOLUME );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetVolume( 0 );
					break;
				case ID_SOUND_BUF10:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 0 );
					break;
				case ID_SOUND_BUF15:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 1 );
					break;
				case ID_SOUND_BUF20:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 2 );
					break;
				case ID_SOUND_BUF25:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 3 );
					break;
				case ID_SOUND_BUF30:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 4 );
					break;
				case ID_SOUND_BUF35:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 5 );
					break;
				case ID_SOUND_BUF40:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 6 );
					break;
				case ID_SOUND_BUF45:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 7 );
					break;
				case ID_SOUND_BUF50:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 8 );
					break;
				case ID_SOUND_BUF75:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 9 );
					break;
				case ID_SOUND_BUF100:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 10 );
					break;
				case ID_SOUND_BUF125:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 11 );
					break;
				case ID_SOUND_BUF150:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 12 );
					break;
				case ID_SOUND_BUF200:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 13 );
					break;
				case ID_SOUND_BUF500:
					ResetMenuCheck( MENU_SOUNDBUFFER );
					CheckMenuItem( Menu, wm_id, MF_BYCOMMAND | MF_CHECKED );
					SetSound( 44100, 14 );
					break;
				case ID_SETPRINTER:
					SetPrinter();
					break;
				case IDM_ABOUT:
					DialogBox( Instance, (LPCTSTR)IDD_ABOUTBOX, wnd, (DLGPROC)About );
					break;
				default:
				   return DefWindowProc( wnd, message, wparam, lparam );
			}
			break;
		case WM_DESTROY:
			// タスクバーに残らないようにする細工
			ShowWindow( wnd, SW_HIDE );
			Sleep( 500 );
			// プログラム終了
			PostQuitMessage( 0 );
			break;
		case WM_KEYDOWN:
			SetKey( ( int )wparam );
			break;
		case WM_KEYUP:
			ResetKey( ( int )wparam );
			break;
		case WM_PAINT:
			Render( GetFullScreen() );
			break;
		case WM_SIZE:
			if( SIZE_MAXIMIZED == wparam )
			{
				// ウインドウモード変更
			}
			if( SIZE_MINIMIZED == wparam )
			{
				SmallWindow = 1;
			}
			if( ( SIZE_MAXHIDE == wparam ) || ( SIZE_MINIMIZED == wparam ) )
			{
				ActiveWindow = 0;
			}
			else
			{
				ActiveWindow = 1;
				SmallWindow = 0;
			}
			break;
	}
	return DefWindowProc( wnd, message, wparam, lparam );
}

//============================================================================
//	ウインドウサイズ変更
//============================================================================
void SetWindowSize( int width, int height )
{
	RECT position;
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	// ウインドウ位置
	GetWindowRect( Wnd, &position );
	// ウインドウサイズ
	AdjustWindowRect( &rect, WindowStyle, TRUE );
	if( rect.left != 0 )
	{
		rect.right -= rect.left;
		rect.left = 0;
	}
	if( rect.top != 0 )
	{
		rect.bottom -= rect.top;
		rect.top = 0;
	}
	SetWindowPos( Wnd, HWND_TOP,
					position.left, position.top,
					rect.right,
					rect.bottom,
					SWP_SHOWWINDOW );
}

void ResetMenuCheck( int type )
{
	if( MENU_SCREENSIZE == type )
	{
		// Screen
		CheckMenuItem( Menu, ID_WINDOWSIZEx1, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_WINDOWSIZEx2, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_WINDOWSIZEx3, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_WINDOWSIZEx4, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_FULLSCREEN, MF_BYCOMMAND | MF_UNCHECKED );
	}
	else if( MENU_FRAMESKIP == type )
	{
		// Frame skip
		CheckMenuItem( Menu, ID_FRAMESKIP_ON, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_FRAMESKIP_OFF, MF_BYCOMMAND | MF_UNCHECKED );
	}
	else if( MENU_VOLUME == type )
	{
		// Volume
		CheckMenuItem( Menu, ID_SOUND_VOL100, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL90, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL80, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL70, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL60, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL50, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL40, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL30, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL20, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_VOL10, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_MUTE, MF_BYCOMMAND | MF_UNCHECKED );
	}
	else if( MENU_SOUNDBUFFER == type )
	{
		// Sound buffer
		CheckMenuItem( Menu, ID_SOUND_BUF10, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF15, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF20, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF25, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF30, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF35, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF40, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF45, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF50, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF75, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF100, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF125, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF150, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF200, MF_BYCOMMAND | MF_UNCHECKED );
		CheckMenuItem( Menu, ID_SOUND_BUF500, MF_BYCOMMAND | MF_UNCHECKED );
	}
}

void InitSetting( void )
{
	// 画面
	if( GetFullScreen() )
	{
		ResetMenuCheck( MENU_SCREENSIZE );
		SetFullScreen( false );
		SetWindow( true );
		SetFullScreen( true );
		CheckMenuItem( Menu, ID_FULLSCREEN, MF_BYCOMMAND | MF_CHECKED );
	}
	else
	{
		ResetMenuCheck( MENU_SCREENSIZE );
		SetWindow( false );
		SetFullScreen( false );
		SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
		switch( GetScreenScale() )
		{
			case 1:
				CheckMenuItem( Menu, ID_WINDOWSIZEx1, MF_BYCOMMAND | MF_CHECKED );
				break;
			case 2:
				CheckMenuItem( Menu, ID_WINDOWSIZEx2, MF_BYCOMMAND | MF_CHECKED );
				break;
			case 3:
				CheckMenuItem( Menu, ID_WINDOWSIZEx3, MF_BYCOMMAND | MF_CHECKED );
				break;
			case 4:
				CheckMenuItem( Menu, ID_WINDOWSIZEx4, MF_BYCOMMAND | MF_CHECKED );
				break;
		}
	}
	ResetMenuCheck( MENU_FRAMESKIP );
	if( GetFrameSkip() )
	{
		CheckMenuItem( Menu, ID_FRAMESKIP_ON, MF_BYCOMMAND | MF_CHECKED );
	}
	else
	{
		CheckMenuItem( Menu, ID_FRAMESKIP_OFF, MF_BYCOMMAND | MF_CHECKED );
	}
	ResetMenuCheck( MENU_VOLUME );
	if( GetVolume() < 10 )
	{
		CheckMenuItem( Menu, ID_SOUND_MUTE, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 20 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL10, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 30 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL20, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 40 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL30, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 50 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL40, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 60 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL50, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 70 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL60, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 80 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL70, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 90 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL80, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() < 100 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL90, MF_BYCOMMAND | MF_CHECKED );
	}
	else if( GetVolume() >= 100 )
	{
		CheckMenuItem( Menu, ID_SOUND_VOL100, MF_BYCOMMAND | MF_CHECKED );
	}
	ResetMenuCheck( MENU_SOUNDBUFFER );
	switch( GetSoundBuffer() )
	{
		case 0:
			SetSound( 44100, 0 );
			CheckMenuItem( Menu, ID_SOUND_BUF10, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 1:
			SetSound( 44100, 1 );
			CheckMenuItem( Menu, ID_SOUND_BUF15, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 2:
			SetSound( 44100, 2 );
			CheckMenuItem( Menu, ID_SOUND_BUF20, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 3:
			SetSound( 44100, 3 );
			CheckMenuItem( Menu, ID_SOUND_BUF25, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 4:
			SetSound( 44100, 4 );
			CheckMenuItem( Menu, ID_SOUND_BUF30, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 5:
			SetSound( 44100, 5 );
			CheckMenuItem( Menu, ID_SOUND_BUF35, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 6:
			SetSound( 44100, 6 );
			CheckMenuItem( Menu, ID_SOUND_BUF40, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 7:
			SetSound( 44100, 7 );
			CheckMenuItem( Menu, ID_SOUND_BUF45, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 8:
			SetSound( 44100, 8 );
			CheckMenuItem( Menu, ID_SOUND_BUF50, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 9:
			SetSound( 44100, 9 );
			CheckMenuItem( Menu, ID_SOUND_BUF75, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 10:
			SetSound( 44100, 10 );
			CheckMenuItem( Menu, ID_SOUND_BUF100, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 11:
			SetSound( 44100, 11 );
			CheckMenuItem( Menu, ID_SOUND_BUF125, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 12:
			SetSound( 44100, 12 );
			CheckMenuItem( Menu, ID_SOUND_BUF150, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 13:
			SetSound( 44100, 13 );
			CheckMenuItem( Menu, ID_SOUND_BUF200, MF_BYCOMMAND | MF_CHECKED );
			break;
		case 14:
			SetSound( 44100, 14 );
			CheckMenuItem( Menu, ID_SOUND_BUF500, MF_BYCOMMAND | MF_CHECKED );
			break;
	}
	if( GetFullScreen() )
	{
		if( GetInformation() )
		{
			CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_CHECKED );
			SetInformation( true );
			ScreenHeight = 192 + 12;
		}
		else
		{
			CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_UNCHECKED );
			SetInformation( false );
			ScreenHeight = 192;
		}
	}
	else
	{
		if( GetInformation() )
		{
			CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_CHECKED );
			SetInformation( true );
			ScreenHeight = 192 + 12;
			SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
		}
		else
		{
			CheckMenuItem( Menu, ID_DRAW_STATUS, MF_BYCOMMAND | MF_UNCHECKED );
			SetInformation( false );
			ScreenHeight = 192;
			SetWindowSize( ScreenWidth * GetScreenScale(), ScreenHeight * GetScreenScale() );
		}
	}
	if( GetTV() )
	{
		CheckMenuItem( Menu, ID_DRAW_TV, MF_BYCOMMAND | MF_CHECKED );
		SetTV( true );
	}
	else
	{
		CheckMenuItem( Menu, ID_DRAW_TV, MF_BYCOMMAND | MF_UNCHECKED );
		SetTV( false );
	}
}

//============================================================================
//	バージョン情報ボックス用メッセージ処理
//============================================================================
LRESULT CALLBACK About( HWND dlg, UINT message, WPARAM wparam, LPARAM lparam )
{
	switch( message )
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			if( ( IDOK == LOWORD( wparam ) ) || ( IDCANCEL == LOWORD( wparam ) ) )
			{
				EndDialog( dlg, LOWORD( wparam ) );
				return TRUE;
			}
			break;
	}
    return FALSE;
}

//============================================================================
//	コマンドライン解析
//============================================================================
void AnlyzeOption( char *cmd_line )
{
	// オプションデバッグ表示
	DEBUGOUT( "■■■■■オプション\n" );
	DEBUGOUT( "%s\n", cmd_line );
	// デフォルト設定
	ScreenWidth = 256;
	ScreenHeight = 192 + 12;
	ScreenColor = 32;
	// オプション取得
	// オプション解析
	DEBUGOUT( "■■■■■オプション解析結果\n" );
	DEBUGOUT( "なし\n" );
}

//============================================================================
//	オプション文字列の数値データ取得
//----------------------------------------------------------------------------
// In  : option = オプション文字列へのポインタ
//     : key = オプションキー
// Out : 文字位置
//============================================================================
int GetKeyData( char *option, char *key )
{
	char key_temp[ 260 ];
	int option_length;
	int key_length;
	int loop;
	int key_position;
	int data_position;
	int ret_code;
	int i;
	strcpy( key_temp, "/" );
	strcat( key_temp, key );
	strcat( key_temp, "=" );
	option_length = (int)strlen( option );
	key_length = (int)strlen( key );
	loop = option_length - key_length;
	key_position = -1;
	for( i = 0; i < loop; i ++ )
	{
		if( 0 == strnicmp( &option[ i ], key_temp, key_length ) )
		{
			key_position = i;
			break;
		}
	}
	if( -1 == key_position )
	{
		return -1;
	}
	data_position = key_position + key_length + 2;
	ret_code = GetNumeral10( &option[ data_position ] );
	return ret_code;
}

//============================================================================
//  文字列から数値データ取得
//----------------------------------------------------------------------------
// In  : 文字列データ
// Out : 数値データ
//============================================================================
int GetNumeral10( char *data )
{
	int ret_code = 0;
	while( !( ( *data > '9' ) || ( *data < '0' ) ) )
	{
		ret_code *= 10;
		ret_code += ( (int)*data - (int)'0' );
		data++;
	}
	return( ret_code );
}

void PrintErrorMessage( void )
{
	LPVOID message_buffer;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ), // デフォルト言語
		(LPTSTR)&message_buffer,
		0,
		NULL 
	);
	MessageBox( NULL, (LPTSTR)message_buffer, "Error", MB_OK | MB_ICONINFORMATION );
	LocalFree( message_buffer );
}
