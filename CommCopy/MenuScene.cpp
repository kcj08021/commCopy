#include "stdafx.h"
#include "MenuScene.h"

CMenuScene::CMenuScene(){
	INIT_ARRAY(m_Button);
}

CMenuScene::~CMenuScene(){
	Release();
}

void CMenuScene::Release(){
	SNDMGR->StopAll();
}


void CMenuScene::Initialize(){
	BMPMGR->AddBMP(L"BACKGROUND", PATH_BACKGROUND);

	BMPMGR->AddBMP(L"MAINMENU", PATH_MAINMENU);
	BMPMGR->SetBmpInfo(L"MAINMENU", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GAMESTART", PATH_GAMESTART);
	BMPMGR->SetBmpInfo(L"GAMESTART", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"QUITGAME", PATH_QUITGAME);
	BMPMGR->SetBmpInfo(L"QUITGAME", 1, 1, RGB(255, 255, 255));

	m_Button[START_BUTTON].left = 297;
	m_Button[START_BUTTON].top = 270;
	m_Button[START_BUTTON].right = 503;
	m_Button[START_BUTTON].bottom = 312;

	m_Button[QUIT_BUTTON].left = 309;
	m_Button[QUIT_BUTTON].top = 330;
	m_Button[QUIT_BUTTON].right = 497;
	m_Button[QUIT_BUTTON].bottom = 380;

	SNDMGR->PlayBGM(L"BGM_MENU.wav");
}

int CMenuScene::Update(){

	if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
		if(PtInRect(&m_Button[START_BUTTON], MOUSEMGR->GetPos())){
			SCNMGR->SetScean(SCENE_MISSION_01);
		} else if(PtInRect(&m_Button[QUIT_BUTTON], MOUSEMGR->GetPos())){
			DestroyWindow(g_hWnd);
		}
	}


	return 0;
}

void CMenuScene::Render(HDC _hdc){
	HDC bmpDC = BMPMGR->GetBmpDC(L"BACKGROUND");
	BitBlt(_hdc, 0, 0, 800, 600, bmpDC, 0, 0, SRCCOPY);

	bmpDC = BMPMGR->GetBmpDC(L"MAINMENU");
	BMPINFO info = BMPMGR->GetBmpInfo(L"MAINMENU");
	GdiTransparentBlt(_hdc, 271, 150, info.cx, info.cy, bmpDC, 0, 0, info.cx, info.cy, info.TransColor);

	bmpDC = BMPMGR->GetBmpDC(L"GAMESTART");
	info = BMPMGR->GetBmpInfo(L"GAMESTART");
	GdiTransparentBlt(_hdc, 297, 270, info.cx, info.cy, bmpDC, 0, 0, info.cx, info.cy, info.TransColor);

	bmpDC = BMPMGR->GetBmpDC(L"QUITGAME");
	info = BMPMGR->GetBmpInfo(L"QUITGAME");
	GdiTransparentBlt(_hdc, 309, 330, info.cx, info.cy, bmpDC, 0, 0, info.cx, info.cy, info.TransColor);

}
