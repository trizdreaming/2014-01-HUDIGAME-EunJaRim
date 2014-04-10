﻿// YaMangClient.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "YaMangClient.h"

#include <stdio.h>
#include <time.h>
#include <crtdbg.h>

#include "Logger.h"
#include "MainWindow.h"

#pragma comment(lib,"ws2_32.lib")

int APIENTRY _tWinMain( _In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPTSTR    lpCmdLine,
						_In_ int       nCmdShow )
{
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );

	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	// _CrtSetBreakAlloc( #### );
	// 메모리 릭을 체크하려면 위의 #### 칸에 릭 난 곳 { 숫자 } 표기 된 숫자를 넣어주면 됩니다.

#ifdef _PRINT_CONSOLE
	Logger::GetInstance();
#endif

	// WS_POPUPWINDOW
	if ( false == MainWindow::GetInstance()->Create( L"YaMang", WS_OVERLAPPEDWINDOW , MAKEINTRESOURCE( IDC_YAMANGCLIENT ) ) )
	{
		return 0;
	}

	MainWindow::GetInstance()->Display( nCmdShow );
	
	int result = MainWindow::GetInstance()->RunGame();
	MainWindow::Release();

#ifdef _PRINT_CONSOLE
	Logger::Release();
#endif

	return result;
}