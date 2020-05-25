#include "stdafx.h"
#include "Wall.h"

CWall::CWall(){
}

CWall::~CWall(){
	Release();
}

void CWall::Release(){
}

void CWall::Initialize(){
	BMPMGR->AddBMP(L"WALL", PATH_WALL);
	BMPMGR->SetBmpInfo(L"WALL", 1, 1, RGB(255, 255, 255));
	m_bmpDC = BMPMGR->GetBmpDC(L"WALL");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"WALL");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.fSpeed = 0.f;
	m_tInfo.iHp = 9999;
	m_tInfo.bIsDead = false;
	m_bIsVisible = false;

	CGameObject::UpdateRect();
}

int CWall::Update(){

	CGameObject::UpdateRect();

	return 0;
}

void CWall::Render(HDC _hdc){
	if(m_bIsVisible){
		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
	}
}
