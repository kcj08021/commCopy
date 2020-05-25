#include "stdafx.h"
#include "MainGame.h"

CMainGame::CMainGame(){
	INIT_STRUCT(m_hDC);
	INIT_STRUCT(m_memDC);
}

CMainGame::~CMainGame(){
	Release();
}

void CMainGame::Release(){
	ReleaseDC(g_hWnd, m_hDC);

	KEYMGR->DestroyInstance();
	SCNMGR->DestroyInstance();
	BMPMGR->DestroyInstance();
	MOUSEMGR->DestroyInstance();
	SCRLMGR->DestroyInstance();
	TILEMGR->DestroyInstance();
	UIMGR->DestroyInstance();
	UNITMGR->DestroyInstance();
	EFCTMGR->DestroyInstance();
	OBJMGR->DestroyInstance();
	SNDMGR->DestroyInstance();
}

void CMainGame::Initialize(){
	srand(static_cast<unsigned int>(time(nullptr)));

	m_hDC = GetDC(g_hWnd);

	ShowCursor(false);

	BMPMGR->AddBMP(L"BackBuffer", PATH_BACKBUFFER);
	BMPMGR->AddBMP(L"Background", PATH_BACKGROUND);

	//매니저 초기화
	SNDMGR->Initialize();
	UNITMGR->Initialize();
	EFCTMGR->Initialize();
	UIMGR->Initialize();
	MOUSEMGR->Initialize();

	SCNMGR->SetScean(SCENE_TITLE);
}

void CMainGame::Update(){
	KEYMGR->Update();
	MOUSEMGR->Update();
	SNDMGR->UpdateSound();
	SCNMGR->Update();
}

void CMainGame::Render(){
	m_memDC = BMPMGR->GetBmpDC(L"BackBuffer");
	if(nullptr == m_memDC)
		return;

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(220, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(m_memDC, pen);
	SelectObject(m_memDC, GetStockObject(NULL_BRUSH));

	SCNMGR->Render(m_memDC);
	MOUSEMGR->Render(m_memDC);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_memDC, 0, 0, SRCCOPY);

	SelectObject(m_memDC, oldPen);
	DeleteObject(pen);
}