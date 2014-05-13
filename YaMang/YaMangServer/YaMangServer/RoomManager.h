﻿#pragma once

class ClientSession;
class GameRoom;


class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	int 	AddRoom(); // 방 생성
	
	bool	EnterRoom( int roomNumber, int pid );
	bool	LeaveRoom( int roomNumber, int pid );

	bool	DeleteRoom( int roomNumber ); // 방 삭제

	bool	CheckRoom( int roomNumber);

	ClientSession*	CreateClient( SOCKET sock );
	void			FlushClientSend( );
	void			OnPeriodWork( );



	void			PrintClientList(); // 테스트용 함수


public:
	GameRoom*					m_Lobby;

private:
	typedef std::hash_map<int, GameRoom*> RoomList; ///# RoomList는 순회를 자주한다. 그러면 해시맵으로 쓰면 안된다. 그냥 맵으로 쓸 것.  그런데 왜일까?
	RoomList						m_RoomList;
	int								m_RoomCount = 0;



};
extern std::hash_map<int, ClientSession*>	g_PidSessionTable;
extern RoomManager*							g_RoomManager;

