#include "stdafx.h"
#include "ClearScene.h"

CClearScene::CClearScene(){
	INIT_STRUCT(m_Button);
}

CClearScene::~CClearScene(){

}

void CClearScene::Release(){
}

void CClearScene::Initialize(){
	BMPMGR->AddBMP(L"BACKGROUND", PATH_BACKGROUND);

	BMPMGR->AddBMP(L"MISSIONCLEAR", PATH_MISSIONCLEAR);
	BMPMGR->SetBmpInfo(L"MISSIONCLEAR", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"QUITGAME", PATH_QUITGAME);
	BMPMGR->SetBmpInfo(L"QUITGAME", 1, 1, RGB(255, 255, 255));

	SNDMGR->PlaySound(L"BGM_CLEAR.wav", SNDMGR->BGM);

	m_Button.left = 309;
	m_Button.top = 300;
	m_Button.right = 491;
	m_Button.bottom = 350;

}

int CClearScene::Update(){
	if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
		if(PtInRect(&m_Button, MOUSEMGR->GetPos())){
			DestroyWindow(g_hWnd);
		}
	}
	return 0;
}

void CClearScene::Render(HDC _hdc){
	HDC bmpDC = BMPMGR->GetBmpDC(L"BACKGROUND");
	BitBlt(_hdc, 0, 0, 800, 600, bmpDC, 0, 0, SRCCOPY);

	bmpDC = BMPMGR->GetBmpDC(L"MISSIONCLEAR");
	BMPINFO info = BMPMGR->GetBmpInfo(L"MISSIONCLEAR");
	GdiTransparentBlt(_hdc, 400 - (info.cx / 2), 200 - (info.cy / 2), info.cx, info.cy, bmpDC, 0, 0, info.cx, info.cy, info.TransColor);

	bmpDC = BMPMGR->GetBmpDC(L"QUITGAME");
	info = BMPMGR->GetBmpInfo(L"QUITGAME");
	GdiTransparentBlt(_hdc, 309, 300, info.cx, info.cy, bmpDC, 0, 0, info.cx, info.cy, info.TransColor);
}
