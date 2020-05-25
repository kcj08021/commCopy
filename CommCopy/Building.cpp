#include "stdafx.h"
#include "Building.h"

CBuilding::CBuilding(){
}

CBuilding::~CBuilding(){
	Release();
}

void CBuilding::SetBuilding(BUILDING_TYPE _enum){
	switch(_enum){
	case BUILDING_ONE:
		m_bmpDC = BMPMGR->GetBmpDC(L"BUILDING1");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"BUILDING1");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case BUILDING_TWO:
		m_bmpDC = BMPMGR->GetBmpDC(L"BUILDING2");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"BUILDING2");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case BUILDING_THREE:
		m_bmpDC = BMPMGR->GetBmpDC(L"BUILDING3");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"BUILDING3");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	default:
		break;
	}
}

void CBuilding::Release(){
}

void CBuilding::Initialize(){
	BMPMGR->AddBMP(L"BUILDING1", PATH_BULILDING1);
	BMPMGR->SetBmpInfo(L"BUILDING1", 1, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"BUILDING2", PATH_BULILDING2);
	BMPMGR->SetBmpInfo(L"BUILDING2", 1, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"BUILDING3", PATH_BULILDING3);
	BMPMGR->SetBmpInfo(L"BUILDING3", 1, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"BUILDING1");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"BUILDING1");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.fSpeed = 0.f;
	m_tInfo.iHp = 9999;
	m_tInfo.bIsDead = false;

	CGameObject::UpdateRect();
}

int CBuilding::Update(){
	CGameObject::UpdateRect();

	return 0;
}

void CBuilding::Render(HDC _hdc){
	GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
}
