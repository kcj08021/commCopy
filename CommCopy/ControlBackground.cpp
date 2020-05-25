#include "stdafx.h"
#include "ControlBackground.h"

constexpr TCHAR* szObjKey = L"ControlBackground";

CControlBackground::CControlBackground(){

}

CControlBackground::~CControlBackground(){
	Release();
}

void CControlBackground::Release(){
}

void CControlBackground::Initialize(){
	BMPMGR->AddBMP(szObjKey, PATH_CON_BG);
	BMPMGR->SetBmpInfo(szObjKey, 1, 1, RGB(255, 0, 255));
	m_BmpInfo = BMPMGR->GetBmpInfo(szObjKey);
	m_bmpDC = BMPMGR->GetBmpDC(szObjKey);
	
	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fX = WINCX / 2.f;
	m_tInfo.fY = WINCY;
}

int CControlBackground::Update(){
	return 0;
}

void CControlBackground::Render(HDC _hdc){

	GdiTransparentBlt(_hdc, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy,
						m_bmpDC, 0,0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);

}
