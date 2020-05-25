#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject(): m_eState(STATE_STAND), m_eAngle(ANGLE_RIGHT), m_iFrameX(0), m_bIsVisible(true){
	INIT_STRUCT(m_tRECT);
	INIT_STRUCT(m_tInfo);
	INIT_STRUCT(m_BmpInfo);
	INIT_STRUCT(m_bmpDC);
}

CGameObject::~CGameObject(){}


float CGameObject::CalculateDist(POINT& _pt){
	int x = int(m_tInfo.fX);
	int y = int(m_tInfo.fY);

	float fDist = sqrtf(float(SQUERE(x - _pt.x) + SQUERE(y - _pt.y)));

	return fDist;
}

float CGameObject::CalculateDist(float _fx, float _fy){
	POINT pt = { LONG(_fx), LONG(_fy) };

	return CGameObject::CalculateDist(pt);
}

void CGameObject::CalculateAngle(POINT& _pt, float _fDist){
	m_tInfo.fAngle = acosf(float((_pt.x - int(m_tInfo.fX)) / _fDist));

	if(isnan(m_tInfo.fAngle) != 0)
		m_tInfo.fAngle = -1 / 4 * PI;

	if(_pt.y > m_tInfo.fY)
		m_tInfo.fAngle *= -1.f;

	UpdateAngleState();
}

void CGameObject::UpdateRect(){
	m_tRECT.top = static_cast<LONG>((m_tInfo.fY - m_tInfo.fCY) - SCRLMGR->m_fScrollY);
	m_tRECT.left = static_cast<LONG>((m_tInfo.fX - m_tInfo.fCX * 0.5f) - SCRLMGR->m_fScrollX);
	m_tRECT.bottom = static_cast<LONG>(m_tInfo.fY - SCRLMGR->m_fScrollY);
	m_tRECT.right = static_cast<LONG>(m_tInfo.fX + m_tInfo.fCX * 0.5f - SCRLMGR->m_fScrollX);
}

void CGameObject::UpdateAngleState(){
	float fDegree = DEGREE(m_tInfo.fAngle);

	if(22.5f >= fDegree && -22.5 < fDegree)
		m_eAngle = ANGLE_RIGHT;
	else if(-22.5 >= fDegree && -67.5f < fDegree)
		m_eAngle = ANGLE_RDOWN;
	else if(-67.5f >= fDegree && -112.5f < fDegree)
		m_eAngle = ANGLE_DOWN;
	else if(112.5f >= fDegree && 67.5f < fDegree)
		m_eAngle = ANGLE_UP;
	else if(67.5f >= fDegree && 22.5f < fDegree)
		m_eAngle = ANGLE_RUP;
	else if(-157.5 >= fDegree || 157.5 < fDegree)
		m_eAngle = ANGLE_LEFT;
	else if(-112.5f >= fDegree && -157.5 < fDegree)
		m_eAngle = ANGLE_LDOWN;
	else if(157.5 >= fDegree && 112.5f < fDegree)
		m_eAngle = ANGLE_LUP;
}

void CGameObject::ConfigState(float& _fSpeed){

	switch(m_eState){
	case STATE_WALK:
		_fSpeed = m_tInfo.fSpeed;
		break;
	case STATE_RUN:
		_fSpeed = m_tInfo.fSpeed * 2.f;
		break;
	case STATE_CARRYBODY:
	case STATE_CARRY:
	case STATE_LADDER:
	case STATE_PRONE:
		_fSpeed = 1.f;
		break;
	case STATE_LADDEREND:
		_fSpeed = 0.5f;
	default:
		_fSpeed = m_tInfo.fSpeed;
		break;
	}

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
}