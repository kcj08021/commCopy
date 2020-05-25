#include "stdafx.h"
#include "Pole.h"

CPole::CPole(){
}

CPole::~CPole(){
	Release();
}

void CPole::SetSelect(bool _bool){
	if(_bool){
		m_bmpDC = BMPMGR->GetBmpDC(L"POLE1");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"POLE1");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
	} else{
		m_bmpDC = BMPMGR->GetBmpDC(L"POLE2");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"POLE2");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
	}
}

void CPole::Release(){
}

void CPole::Initialize(){
	BMPMGR->AddBMP(L"POLE1", PATH_POLE1);
	BMPMGR->SetBmpInfo(L"POLE1", 1, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"POLE2", PATH_POLE2);
	BMPMGR->SetBmpInfo(L"POLE2", 1, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"POLE1");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"POLE1");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.fSpeed = 0.f;
	m_tInfo.iHp = 9999;
	m_tInfo.bIsDead = false;

	CGameObject::UpdateRect();
}

int CPole::Update(){

	CGameObject::UpdateRect();

	return 0;
}

void CPole::Render(HDC _hdc){
	GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
}
