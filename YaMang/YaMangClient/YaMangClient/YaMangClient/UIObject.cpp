﻿#include "stdafx.h"
#include "UIObject.h"
#include "YaMangDxDll.h"


UIObject::UIObject()
{
}


UIObject::~UIObject()
{
}

void UIObject::Update()
{

}

void UIObject::Render() const
{

}

void UIObject::SetUIPosition( int x, int y )
{
	SetUIPos(m_UIType, x, y);
}