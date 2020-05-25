#include "stdafx.h"
#include "Tree.h"

CTree::CTree(){

}

CTree::~CTree(){
	Release();
}

void CTree::SetTree(bool _bool){
	if(_bool){
		m_bmpDC = BMPMGR->GetBmpDC(L"TREE1");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"TREE1");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
	} else{
		m_bmpDC = BMPMGR->GetBmpDC(L"TREE2");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"TREE2");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
	}
}

void CTree::Release(){
}

void CTree::Initialize(){
	BMPMGR->AddBMP(L"TREE1", PATH_TREE1);
	BMPMGR->SetBmpInfo(L"TREE1", 1, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"TREE2", PATH_TREE2);
	BMPMGR->SetBmpInfo(L"TREE2", 1, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"TREE1");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"TREE1");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fAngle = 0.f;
	m_tInfo.fSpeed = 0.f;
	m_tInfo.iHp = 9999;
	m_tInfo.bIsDead = false;

	CGameObject::UpdateRect();
}

int CTree::Update(){
	CGameObject::UpdateRect();
	return 0;
}

void CTree::Render(HDC _hdc){
	GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
		m_bmpDC, 0, 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
}
