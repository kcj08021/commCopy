#include "stdafx.h"
#include "RadioTower.h"
CRadioTower::CRadioTower() : m_CurrTime(0), m_OldTime(0){

}

CRadioTower::~CRadioTower(){
	Release();
}

void CRadioTower::Release(){
}

void CRadioTower::Initialize(){
	BMPMGR->AddBMP(L"RADIO", PATH_RADIO);
	BMPMGR->SetBmpInfo(L"RADIO", 1, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"RADIO_DEAD", PATH_RADIO_DEAD);
	BMPMGR->SetBmpInfo(L"RADIO_DEAD", 1, 1, RGB(255, 255, 255));
	m_bmpDC = BMPMGR->GetBmpDC(L"RADIO");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"RADIO");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.fSpeed = 0.f;
	m_tInfo.iHp = 100;
	m_tInfo.bIsDead = false;

	CGameObject::UpdateRect();
}

int CRadioTower::Update(){
	m_CurrTime = time(nullptr);

	if(m_tInfo.iHp <= 0){
		if(!m_tInfo.bIsDead){
			m_OldTime = time(nullptr);
		}

		m_tInfo.bIsDead = true;
	}

	if(m_tInfo.bIsDead){
			m_bmpDC = BMPMGR->GetBmpDC(L"RADIO_DEAD");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"RADIO_DEAD");
			m_tInfo.fCX = float(m_BmpInfo.cx);
			m_tInfo.fCY = float(m_BmpInfo.cy);
	
			if(m_CurrTime - m_OldTime > 3)
				SCNMGR->SetScean(SCENE_CLEAR);
	}

	CGameObject::UpdateRect();

	return 0;
}

void CRadioTower::Render(HDC _hdc){
	GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
}
