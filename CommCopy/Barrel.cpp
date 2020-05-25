#include "stdafx.h"
#include "Barrel.h"


CBarrel::CBarrel() {

}

CBarrel::~CBarrel() {

}

void CBarrel::Release() {
}

void CBarrel::Initialize() {
	BMPMGR->AddBMP(L"BARRAL", PATH_BARRAL);
	BMPMGR->SetBmpInfo(L"BARRAL", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"BARRAL_DEAD", PATH_BARRAL_DEAD);
	BMPMGR->SetBmpInfo(L"BARRAL_DEAD", 1, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"BARRAL");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"BARRAL");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.bIsDead = false;
	m_tInfo.fSpeed = 0;
	m_tInfo.iHp = 1;

	CGameObject::UpdateRect();
}

int CBarrel::Update() {
	POINT pt = { LONG(m_tInfo.fX - SCRLMGR->m_fScrollX), LONG(m_tInfo.fY - SCRLMGR->m_fScrollY) };
	if(m_tInfo.iHp <= 0){
		if(!m_tInfo.bIsDead){
			EFCTMGR->LoadEffect(EFFECT_EXPLOSION, pt);
			for(CGameObject* elem : OBJMGR->GetList(OBJ_ALLIED)){
				float fDist = sqrtf(float(SQUERE(m_tInfo.fX - elem->GetInfo().fX) + SQUERE(m_tInfo.fY - elem->GetInfo().fY)));

				if(fDist <= 100.f){
					elem->SetDamage(100);
				}

			}

			for(CGameObject* elem : OBJMGR->GetList(OBJ_ENEMY)){
				float fDist = sqrtf(float(SQUERE(m_tInfo.fX - elem->GetInfo().fX) + SQUERE(m_tInfo.fY - elem->GetInfo().fY)));

				if(fDist <= 100.f){
					elem->SetDamage(100);
				}
			}

			for(CGameObject* elem : OBJMGR->GetList(OBJ_USEOBJ)){
				float fDist = sqrtf(float(SQUERE(m_tInfo.fX - elem->GetInfo().fX) + SQUERE(m_tInfo.fY - elem->GetInfo().fY)));

				if(fDist <= 100.f){
					elem->SetDamage(100);
				}
			}

			for(CGameObject* elem : OBJMGR->GetList(OBJ_MAPOBJ)){
				float fDist = sqrtf(float(SQUERE(m_tInfo.fX - elem->GetInfo().fX) + SQUERE(m_tInfo.fY - elem->GetInfo().fY)));

				if(fDist <= 100.f){
					elem->SetDamage(100);
				}
			}
		}
		m_tInfo.bIsDead = true;

	}

	if(m_tInfo.bIsDead){
		m_bmpDC = BMPMGR->GetBmpDC(L"BARRAL_DEAD");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"BARRAL_DEAD");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
	}

	CGameObject::UpdateRect();

	return 0;
}

void CBarrel::Render(HDC _hdc){
	if(m_bIsVisible)
		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
}
