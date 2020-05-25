#include "stdafx.h"
#include "ScrollManager.h"

IMPLEMENT_SINGLETON(CScrollManager);

CScrollManager::CScrollManager():m_fScrollX(0.f), m_fScrollY(0.f), m_fScrollMaxX(0.f), m_fScrollMaxY(0), m_fScrollMinX(0.f), m_fScrollMinY(0.f){

}

CScrollManager::~CScrollManager(){

}

void CScrollManager::SetScrollMaxValue(const float _x, const float _y){
	m_fScrollMaxX = _x;
	m_fScrollMaxY = _y;
}

void CScrollManager::SetScrollMinValue(const float _x, const float _y){
	m_fScrollMinX = _x;
	m_fScrollMinY = _y;
}

void CScrollManager::SetScrollValue(float _x, float _y){
	_y -= 45.f;	//스크롤 보정값

	if(_x > m_fScrollMaxX + (WINCX - GAP_X) / 2)
		m_fScrollX = m_fScrollMaxX;
	else if(_x < (WINCX - GAP_X)/2)
		m_fScrollX = 0;
	else
		m_fScrollX = _x - (WINCX - GAP_X) / 2;

	if(_y > m_fScrollMaxY + (WINCY - GAP_Y) / 2)
		m_fScrollY = m_fScrollMaxY ;
	else if(_y < (WINCY - GAP_Y)/2)
		m_fScrollY = 0;
	else
		m_fScrollY = _y - (WINCY - GAP_Y) / 2;
}

void CScrollManager::Initialize(){
	m_fScrollX = 0;
	m_fScrollY = 0;
}

void CScrollManager::Update(){
	POINT pt = MOUSEMGR->GetPos();

	if(pt.x <= 1 || KEYMGR->IsKeyPressing(KEY_LEFT))
		if(m_fScrollMinX < m_fScrollX - 10.f)
			m_fScrollX -= 10.f;
		else if(m_fScrollX - 10.f <= m_fScrollMinX)
			m_fScrollX = float(m_fScrollMinX);

	if(pt.x >= WINCX - 1 || KEYMGR->IsKeyPressing(KEY_RIGHT))
		if(m_fScrollMaxX > m_fScrollX + 10.f)
			m_fScrollX += 10.f;
		else if(m_fScrollX + 10.f >= m_fScrollMaxX)
			m_fScrollX = float(m_fScrollMaxX);

	if(pt.y <= 1 || KEYMGR->IsKeyPressing(KEY_UP))
		if(m_fScrollMinY < m_fScrollY - 10.f)
			m_fScrollY -= 10.f;
		else if(m_fScrollY - 10.f <= m_fScrollMinY)
			m_fScrollY = float(m_fScrollMinY);

	if(pt.y >= WINCY - 1 || KEYMGR->IsKeyPressing(KEY_DOWN))
		if(m_fScrollMaxY > m_fScrollY + 10.f)
			m_fScrollY += 10.f;
		else if(m_fScrollY + 10 >= m_fScrollMaxY)
			m_fScrollY = float(m_fScrollMaxY);
}

