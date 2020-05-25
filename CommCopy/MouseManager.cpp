#include "stdafx.h"
#include "MouseManager.h"

IMPLEMENT_SINGLETON(CMouseManager);

CMouseManager::CMouseManager()
	: m_dwLBTime(0), m_dwRBTime(0), m_MouseFlag(0), m_MBDownFlag(0), m_MBUpFlag(0), m_eMouseType(MOUSE_DEFAULT){
	INIT_STRUCT(m_MousePosition);
}

CMouseManager::~CMouseManager(){
	Release();
}

POINT& CMouseManager::GetPos(){
	return m_MousePosition;
}

bool CMouseManager::IsClick(MOUSEFLAG _flag){
	if(!(m_MBDownFlag & _flag) && (m_MouseFlag & _flag)){
		m_MBDownFlag |= _flag;
		return true;
	}

	if((m_MBDownFlag & _flag) && !(m_MouseFlag & _flag)){
		m_MBDownFlag ^= _flag;
		return false;
	}

	return false;
}

bool CMouseManager::IsClickEnd(MOUSEFLAG _flag){
	if((m_MBUpFlag & _flag) && !(m_MouseFlag & _flag)){
		m_MBUpFlag ^= _flag;
		return true;
	}

	if(!(m_MBUpFlag & _flag) && (m_MouseFlag & _flag)){
		m_MBUpFlag |= _flag;
		return false;
	}

	return false;
}

bool CMouseManager::IsDoubleClick(MOUSEFLAG _flag){
	DWORD dwClickTime = GetTickCount();

	if(m_MouseFlag & _flag){
		switch(_flag){
		case MOUSE_LBCLICK:
			if((dwClickTime - m_dwLBTime) < 100 && (dwClickTime - m_dwLBTime) > 30){
				m_dwLBTime = 0;
				return true;
			} else
				m_dwLBTime = dwClickTime;
			break;
		case MOUSE_RBCLICK:
			if((dwClickTime - m_dwRBTime) < 100 && (dwClickTime - m_dwRBTime) > 30){
				m_dwRBTime = 0;
				return true;
			} else
				m_dwRBTime = dwClickTime;
			break;
		}
	}
	return false;
}

bool CMouseManager::IsDrag(MOUSEFLAG _flag){
	if(m_MouseFlag & _flag)
		return true;

	return false;
}


void CMouseManager::Release(){
}



void CMouseManager::Initialize(){
	BMPMGR->AddBMP(L"CURSOR_CURSOR", PATH_CURSOR_CURSOR);
	BMPMGR->SetBmpInfo(L"CURSOR_CURSOR", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_CARRY", PATH_CURSOR_CARRY);
	BMPMGR->SetBmpInfo(L"CURSOR_CARRY", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_N_CARRY", PATH_CURSOR_N_CARRY);
	BMPMGR->SetBmpInfo(L"CURSOR_N_CARRY", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_PISTOL", PATH_CURSOR_PISTOL);
	BMPMGR->SetBmpInfo(L"CURSOR_PISTOL", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_N_PISTOL", PATH_CURSOR_N_PISTOL);
	BMPMGR->SetBmpInfo(L"CURSOR_N_PISTOL", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_KNIFE", PATH_CURSOR_KNIFE);
	BMPMGR->SetBmpInfo(L"CURSOR_KNIFE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_N_KNIFE", PATH_CURSOR_N_KNIFE);
	BMPMGR->SetBmpInfo(L"CURSOR_N_KNIFE", 1, 1, RGB(255, 255, 255));
}

void CMouseManager::Update(){
	GetCursorPos(&m_MousePosition);
	ScreenToClient(g_hWnd, &m_MousePosition);

	m_MouseFlag = MOUSE_NULL;

	if(GetAsyncKeyState(VK_LBUTTON) & 0x8000){
		m_MouseFlag |= MOUSE_LBCLICK;
	}

	if(GetAsyncKeyState(VK_RBUTTON) & 0x8000){
		m_MouseFlag |= MOUSE_RBCLICK;
	}
}

void CMouseManager::Render(HDC _hdc){
	HDC bmpDC = BMPMGR->GetBmpDC(L"CURSOR_CURSOR");
	BMPINFO info = BMPMGR->GetBmpInfo(L"CURSOR_CURSOR");

	switch(m_eMouseType){
	case MOUSE_DEFAULT:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_CURSOR");
		info = BMPMGR->GetBmpInfo(L"CURSOR_CURSOR");
		break;
	case MOUSE_PISTOL:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_PISTOL");
		info = BMPMGR->GetBmpInfo(L"CURSOR_PISTOL");
		break;
	case MOUSE_KNIFE:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_KNIFE");
		info = BMPMGR->GetBmpInfo(L"CURSOR_KNIFE");
		break;
	case MOUSE_CARRY:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_CARRY");
		info = BMPMGR->GetBmpInfo(L"CURSOR_CARRY");
		break;
	case MOUSE_N_PISTOL:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_N_PISTOL");
		info = BMPMGR->GetBmpInfo(L"CURSOR_N_PISTOL");
		break;
	case MOUSE_N_KNIFE:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_N_KNIFE");
		info = BMPMGR->GetBmpInfo(L"CURSOR_N_KNIFE");
		break;
	case MOUSE_N_CARRY:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_N_CARRY");
		info = BMPMGR->GetBmpInfo(L"CURSOR_N_CARRY");
		break;
	default:
		bmpDC = BMPMGR->GetBmpDC(L"CURSOR_CURSOR");
		info = BMPMGR->GetBmpInfo(L"CURSOR_CURSOR");
		break;
	}


	GdiTransparentBlt(_hdc, m_MousePosition.x, m_MousePosition.y, info.cx, info.cy,
		bmpDC, 0, 0, info.cx, info.cy, info.TransColor);
}
