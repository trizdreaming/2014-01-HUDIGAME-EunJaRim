﻿#include "stdafx.h"
#include "MainWindow.h"
#include "GameManager.h"
#include "NetworkManager.h"
#include "Renderer.h"

MainWindow::MainWindow()
{
}


MainWindow::~MainWindow()
{
}

LRESULT MainWindow::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// int wmId, wmEvent;

	switch ( uMsg )
	{
		case WM_TIMER:
		{
			// 타이머 이벤트가 발생하면 이곳에서 핸들링 해 봅니다.
			
			//////////////////////////////////////////////////////////////////////////
			// 9느님 원 소스에서 발췌 - 주기적으로 채팅하기
			/*
			ChatBroadcastRequest sendData;

			sendData.mPlayerId = g_MyClientId;

			/// 랜덤 문자열을 채팅으로 날리기
			char* buff = sendData.mChat;
			for ( int i = 0; i < 300; ++i )
			{
				sendData.mChat[i] = (char)( 65 + ( rand() % 26 ) );
			}
			sendData.mChat[300] = '\0';

			if ( g_SendBuffer.Write( (const char*)&sendData, sendData.mSize ) )
				// sendData.mSize = sizeof(ChatBroadcastRequest);
			{
				PostMessage( hWnd, WM_SOCKET, wParam, FD_WRITE );
				//////////////////////////////////////////////////////////////////////////
				// http://blog.naver.com/gkqxhq324456/110177315036 참조
				//
				// 채팅을 날리려고 버퍼에 데이터도 넣어 두었으니, WM_SOCKET 이벤트를 발생시키자
				//////////////////////////////////////////////////////////////////////////
			}
			*/
			//////////////////////////////////////////////////////////////////////////
		}
			return 0;

		case WM_SOCKET:
		{
			// 네트워크 매니저(싱글톤 객체)를 활용하여 패킷을 핸들링 해 줍니다.

			/*
			// lParam 이 에러인지 검출 해보기
			if ( WSAGETSELECTERROR( lParam ) )
			{
				MessageBox( hWnd, L"WSAGETSELECTERROR", L"Error", MB_OK | MB_ICONERROR );
				SendMessage( hWnd, WM_DESTROY, NULL, NULL );
				break;
			}

			// 에러 아니면 이벤트 검출해서 switch
			switch ( WSAGETSELECTEVENT( lParam ) )
			{
				case FD_CONNECT:
					// 연결이 되었다
				{
					/// NAGLE 끈다
					int opt = 1;
					::setsockopt( g_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof( int ) );

					srand( static_cast<unsigned int> ( time( NULL ) ) );
					/// 대략 1000~1100 의 ID로 로그인 해보자
					LoginRequest sendData;
					sendData.mPlayerId = 1000 + rand() % 101;

					if ( g_SendBuffer.Write( (const char*)&sendData, sendData.mSize ) )
					{
						PostMessage( hWnd, WM_SOCKET, wParam, FD_WRITE );
					}


					int nResult = WSAAsyncSelect( g_Socket, hWnd, WM_SOCKET, ( FD_CLOSE | FD_READ | FD_WRITE ) );
					if ( nResult )
					{
						assert( false );
						break;
					}
				}
					break;

				case FD_READ:
				{
					char inBuf[4096] = { 0, };

					int recvLen = recv( g_Socket, inBuf, 4096, 0 );
					// send() 함수와 반대

					// 소켓에서 읽어온 데이터를 일단 버퍼에 쓰자
					if ( !g_RecvBuffer.Write( inBuf, recvLen ) )
					{
						/// 버퍼 꽉찼다.
						assert( false );
					}

					ProcessPacket( hWnd );
					//////////////////////////////////////////////////////////////////////////
					// 패킷 핸들링!
					//////////////////////////////////////////////////////////////////////////
				}
					break;

					//////////////////////////////////////////////////////////////////////////
					// 데이터를 받으면 -> 버퍼에 쓴 후에, 핸들링 하는 쪽에서 버퍼 데이터 뽑아서 처리
					//
					// 데이터를 보낼때 -> 버퍼에 쓴 후에, FD_WRITE 쪽에서 버퍼 데이터 뽑아서 send()
					//////////////////////////////////////////////////////////////////////////

				case FD_WRITE:
				{
					/// 실제로 버퍼에 있는것들 꺼내서 보내기
					int size = g_SendBuffer.GetCurrentSize();
					if ( size > 0 )
					{
						char* data = new char[size];
						g_SendBuffer.Peek( data );

						int sent = send( g_Socket, data, size, 0 );

						/// 다를수 있다
						if ( sent != size )
							OutputDebugStringA( "sent != request\n" );

						// 보낸 데이터는 지우자
						g_SendBuffer.Consume( sent );

						delete[] data;
					}

				}
					break;

				case FD_CLOSE:
				{
					MessageBox( hWnd, L"Server closed connection", L"Connection closed!", MB_ICONINFORMATION | MB_OK );
					closesocket( g_Socket );
					SendMessage( hWnd, WM_DESTROY, NULL, NULL );

					// 여기는 네트워크 매니저에서 Destroy 하고 매니저를 Release 하도록 한다
				}
					break;
			}
			*/
		}
			return 0;
		case WM_SIZE:
		{
			// 리사이징에 대한 부분을 여기서 처리 해 줌
			// int x = (int)LOWORD( lParam );
			// int y = (int)HIWORD( lParam );
			// Renderer::GetInstance()->Resize( x, y );
			InvalidateRect( m_HandleOfWindow, NULL, FALSE );
		}
			return 0;

		case WM_DESTROY:
		{	
			if ( GameManager::GetInstance()->Process() )
			{
				GameManager::GetInstance()->Stop();
				// 창이 강제 제거 되었을 때(창 닫기 등)
				// 여기서 이 이벤트를 발생시켜서 RunGame()의 루프에서 빠져나오게 해야
				// 안전하게 리소스가 해제 되면서 메모리 릭을 피할 수 있다.
			}
			PostQuitMessage( 0 );
		}
			return 0;

		/*
		case WM_MOUSEMOVE:
		{
			MouseX = LOWORD( IParam );
			MouseY = HIWORD( IParam );
		}
			break;
		*/
		case WM_KEYDOWN:
			switch ( wParam )
			{
				case VK_ESCAPE:
					GameManager::GetInstance()->Stop();
					return 0;
			}

		case WM_ERASEBKGND:
			return 1;

		default:
			return DefWindowProc( m_HandleOfWindow, uMsg, wParam, lParam );
	}

	return 0;
}

int MainWindow::RunGame()
{
	MSG msg = {0,};

	if ( false == GameManager::GetInstance()->Init() )
	{
		GameManager::GetInstance()->Destroy();
		GameManager::Release();
		// 사실 여기 이렇게 그냥 두었지만,
		// Init() 함수 내부에서 방어 코드 종류별로 케바케로 실패 뜬 부분 전부 잡아서 Release() 해줘야 됨.
		//
		// 뭔가 스마트 포인터의 필요성이 보이는 것 같다 =ㅅ=
		
		MessageBox( m_HandleOfWindow, L"Gama Manager Initialization Error", L"Game Manager Init Error!", MB_ICONINFORMATION | MB_OK );
		SendMessage( m_HandleOfWindow, WM_DESTROY, NULL, NULL );
		return false;
	}

	while ( msg.message != WM_QUIT )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if ( false == GameManager::GetInstance()->Process() )
		{
			GameManager::GetInstance()->Destroy();
			GameManager::Release();
			PostQuitMessage( 0 );
			break;
		}
	}

	return (int)msg.wParam;
}