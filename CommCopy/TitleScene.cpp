#include "stdafx.h"
#include "TitleScene.h"

CTitleScene::CTitleScene(){

}

CTitleScene::~CTitleScene(){
	Release();
}

void CTitleScene::Release(){
}

void CTitleScene::Initialize(){
	BMPMGR->AddBMP(L"TITLE", PATH_TITLE);
}

int CTitleScene::Update(){
	if(KEYMGR->IsKeyDown(KEY_RETURN) || MOUSEMGR->IsClick(MOUSE_LBCLICK))
		SCNMGR->SetScean(SCENE_MENU);
	return 0;
}

void CTitleScene::Render(HDC _hdc){
	HDC bmpDC = BMPMGR->GetBmpDC(L"TITLE");

	BitBlt(_hdc, 0, 0, 800, 600, bmpDC, 0, 0, SRCCOPY);
}
