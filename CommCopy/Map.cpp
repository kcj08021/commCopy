#include "stdafx.h"
#include "Map.h"

CMap::CMap(){

}

CMap::~CMap(){
	Release();
}

void CMap::Release(){
}

void CMap::Initialize(){
	BMPMGR->AddBMP(L"MAP01", PATH_MAP01);
	BMPMGR->AddBMP(L"TileMAP01", PATH_TILEMAP01);
	m_bmpDC = BMPMGR->GetBmpDC(L"MAP01");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"MAP01");

	m_tInfo.fCX = WINCX - GAP_X;
	m_tInfo.fCY = WINCY - GAP_Y;

	float fMaxScrollX = float(m_BmpInfo.cx - WINCX + GAP_X);
	float fMaxScrollY = float(m_BmpInfo.cy - WINCY + GAP_Y);
	
	SCRLMGR->SetScrollMaxValue(fMaxScrollX, fMaxScrollY);
	SCRLMGR->SetScrollMinValue(0, 0);

	TILEMGR->SetTileMap(BMPMGR->GetBmpDC(L"TileMAP01"));
	TILEMGR->CreateTile(m_BmpInfo.cx, m_BmpInfo.cy);
}

int CMap::Update(){
	
	return 0;
}

void CMap::Render(HDC _hdc){
	StretchBlt(_hdc, 0, GAP_Y, int(m_tInfo.fCX), int(m_tInfo.fCY),
			   m_bmpDC, int(SCRLMGR->m_fScrollX), int(SCRLMGR->m_fScrollY), WINCX - GAP_X, WINCY - GAP_Y, SRCCOPY);
}
