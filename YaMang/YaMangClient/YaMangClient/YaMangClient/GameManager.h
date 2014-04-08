﻿#pragma once

#include "MacroSet.h"

struct MESHOBJECT;

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	bool Init();
	bool Process();
	void Destroy();
	void Stop() { m_Continue = false;  }

private:
	GameManager( const GameManager & );
	GameManager & operator=( const GameManager & );
	
	bool			m_Continue;

	MESHOBJECT*		m_Mesh;
};