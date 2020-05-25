#include "stdafx.h"
#include "UIManager.h"
#include "Marine.h"
#include "Enemy.h"

IMPLEMENT_SINGLETON(CUIManager);

CUIManager::CUIManager():m_bIsMouseOnSight(false) {
	//배열 초기화
	INIT_ARRAY(m_UnitPictueFrame);
	INIT_ARRAY(m_ProneStandButton);
	INIT_ARRAY(m_bInvenButton);
	INIT_ARRAY(m_UnitButton);
	INIT_ARRAY(m_InvenButton);


	//구조체 초기화
	INIT_STRUCT(m_SightButton);
}


CUIManager::~CUIManager(){

}

void CUIManager::EnemySight(bool _bool){
	//적 유닛에 시야표시 전달
	for(CGameObject* elem : *UNITMGR->m_pEnemyList){
		dynamic_cast<CEnemy*>(elem)->SetSightOnOff(_bool);
	}
}



void CUIManager::Initialize(){
	//이미지 로드
	BMPMGR->AddBMP(L"UI_BAG", PATH_UI_BAG);
	BMPMGR->SetBmpInfo(L"UI_BAG", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_BOAT", PATH_UI_BOAT);
	BMPMGR->SetBmpInfo(L"UI_BOAT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_CARRY", PATH_UI_CARRY);
	BMPMGR->SetBmpInfo(L"UI_CARRY", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_HARPOON", PATH_UI_HARPOON);
	BMPMGR->SetBmpInfo(L"UI_HARPOON", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_KNIFE", PATH_UI_KNIFE);
	BMPMGR->SetBmpInfo(L"UI_KNIFE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_PISTOL", PATH_UI_PISTOL);
	BMPMGR->SetBmpInfo(L"UI_PISTOL", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_SMG", PATH_UI_SMG);
	BMPMGR->SetBmpInfo(L"UI_SMG", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_DIVE", PATH_UI_DIVE);
	BMPMGR->SetBmpInfo(L"UI_DIVE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_PICTURE", PATH_UI_PICTURE);
	BMPMGR->SetBmpInfo(L"UI_PICTURE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_PICTURE", PATH_UI_GB_PICTURE);
	BMPMGR->SetBmpInfo(L"GB_PICTURE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"MR_PICTURE", PATH_UI_MR_PICTURE);
	BMPMGR->SetBmpInfo(L"MR_PICTURE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"DR_PICTURE", PATH_UI_DR_PICTURE);
	BMPMGR->SetBmpInfo(L"DR_PICTURE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_UI_SELECT", PATH_UI_GB_SELECT);
	BMPMGR->SetBmpInfo(L"GB_UI_SELECT", 10, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"MR_UI_SELECT", PATH_UI_MR_SELECT);
	BMPMGR->SetBmpInfo(L"MR_UI_SELECT", 10, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"DR_UI_SELECT", PATH_UI_DR_SELECT);
	BMPMGR->SetBmpInfo(L"DR_UI_SELECT", 10, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_SELECT", PATH_UI_SELECT);
	BMPMGR->SetBmpInfo(L"UI_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_HP", PATH_UI_HP);
	BMPMGR->SetBmpInfo(L"UI_HP", 5, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_STAND", PATH_UI_STAND);
	BMPMGR->SetBmpInfo(L"UI_STAND", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_PRONE", PATH_UI_PRONE);
	BMPMGR->SetBmpInfo(L"UI_PRONE", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_SIGHT", PATH_UI_SIGHT);
	BMPMGR->SetBmpInfo(L"UI_SIGHT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_BOAT_SELECT", PATH_UI_BOAT_SELECT);
	BMPMGR->SetBmpInfo(L"UI_BOAT_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_CARRY_SELECT", PATH_UI_CARRY_SELECT);
	BMPMGR->SetBmpInfo(L"UI_CARRY_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_HARPOON_SELECT", PATH_UI_HARPOON_SELECT);
	BMPMGR->SetBmpInfo(L"UI_HARPOON_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_KNIFE_SELECT", PATH_UI_KNIFE_SELECT);
	BMPMGR->SetBmpInfo(L"UI_KNIFE_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_PISTOL_SELECT", PATH_UI_PISTOL_SELECT);
	BMPMGR->SetBmpInfo(L"UI_PISTOL_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_SMG_SELECT", PATH_UI_SMG_SELECT);
	BMPMGR->SetBmpInfo(L"UI_SMG_SELECT", 1, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"UI_DIVE_SELECT", PATH_UI_DIVE_SELECT);
	BMPMGR->SetBmpInfo(L"UI_DIVE_SELECT", 1, 1, RGB(255, 255, 255));


	//버튼 배치
	m_UnitButton[UNIT_GREENBERETS].left = 10;
	m_UnitButton[UNIT_GREENBERETS].top = 0;
	m_UnitButton[UNIT_GREENBERETS].right = 70;
	m_UnitButton[UNIT_GREENBERETS].bottom = 42;
	m_UnitButton[UNIT_MARINE].left = 75;
	m_UnitButton[UNIT_MARINE].top = 0;
	m_UnitButton[UNIT_MARINE].right = 135;
	m_UnitButton[UNIT_MARINE].bottom = 42;
	m_UnitButton[UNIT_DRIVER].left = 140;
	m_UnitButton[UNIT_DRIVER].top = 0;
	m_UnitButton[UNIT_DRIVER].right = 200;
	m_UnitButton[UNIT_DRIVER].bottom = 42;

	m_ProneStandButton[UI_PRONE].left = 410;
	m_ProneStandButton[UI_PRONE].top = 5;
	m_ProneStandButton[UI_PRONE].right = 457;
	m_ProneStandButton[UI_PRONE].bottom = 40;
	m_ProneStandButton[UI_STAND].left = 470;
	m_ProneStandButton[UI_STAND].top = 0;
	m_ProneStandButton[UI_STAND].right = 494;
	m_ProneStandButton[UI_STAND].bottom = 45;

	m_SightButton.left = 748;
	m_SightButton.top = 0;
	m_SightButton.right = 800;
	m_SightButton.bottom = 45;

	m_InvenButton[UI_PISTOL].left = 747;
	m_InvenButton[UI_PISTOL].top = 498;
	m_InvenButton[UI_PISTOL].right = 800;
	m_InvenButton[UI_PISTOL].bottom = 569;

	m_InvenButton[UI_SMG].left = 680;
	m_InvenButton[UI_SMG].top = 450;
	m_InvenButton[UI_SMG].right = 752;
	m_InvenButton[UI_SMG].bottom = 600;

	m_InvenButton[UI_CARRY].left = 737;
	m_InvenButton[UI_CARRY].top = 385;
	m_InvenButton[UI_CARRY].right = 800;
	m_InvenButton[UI_CARRY].bottom = 455;

	m_InvenButton[UI_KNIFE].left = 678;
	m_InvenButton[UI_KNIFE].top = 455;
	m_InvenButton[UI_KNIFE].right = 800;
	m_InvenButton[UI_KNIFE].bottom = 477;

	m_InvenButton[UI_BOAT].left = 650;
	m_InvenButton[UI_BOAT].top = 503;
	m_InvenButton[UI_BOAT].right = 687;
	m_InvenButton[UI_BOAT].bottom = 600;

	m_InvenButton[UI_HARPOON].left = 692;
	m_InvenButton[UI_HARPOON].top = 490;
	m_InvenButton[UI_HARPOON].right = 744;
	m_InvenButton[UI_HARPOON].bottom = 800;

	m_InvenButton[UI_DIVE].left = 744;
	m_InvenButton[UI_DIVE].top = 570;
	m_InvenButton[UI_DIVE].right = 800;
	m_InvenButton[UI_DIVE].bottom = 600;

	m_InvenButton[UI_DIVE].left = 744;
	m_InvenButton[UI_DIVE].top = 570;
	m_InvenButton[UI_DIVE].right = 800;
	m_InvenButton[UI_DIVE].bottom = 600;

	m_InvenButton[UI_PICTURE].left = 700;
	m_InvenButton[UI_PICTURE].top = 500;
	m_InvenButton[UI_PICTURE].right = 764;
	m_InvenButton[UI_PICTURE].bottom = 580;

	m_bIsMouseOnSight = false;
}

void CUIManager::Update(){
	for(int i = 0; i < UNIT_END; ++i){
		if(PtInRect(&m_UnitButton[i], MOUSEMGR->GetPos())){
			if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
				for(CGameObject* elem : UNITMGR->m_UnitArray){
					dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
				}
				UNITMGR->m_eUnitType = UNIT_TYPE(i);
				dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[i])->SetFocus(true);
				INFO* info = &UNITMGR->m_UnitArray[i]->GetInfo();
				SCRLMGR->SetScrollValue(info->fX, info->fY);
				if(UNITMGR->m_UnitArray[i]->IsDead()){
					dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[i])->SetFocus(false);
					UNITMGR->m_eUnitType = UNIT_END;
				} else{
					switch(UNIT_TYPE(i)){
					case UNIT_GREENBERETS:
						SNDMGR->PlaySound(L"GB_SELECT.wav", SNDMGR->PLAYER);
						break;
					case UNIT_MARINE:
						SNDMGR->PlaySound(L"MR_SELECT.wav", SNDMGR->PLAYER);
						break;
					case UNIT_DRIVER:
						SNDMGR->PlaySound(L"DR_SELECT.wav", SNDMGR->PLAYER);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	if(UNITMGR->m_eUnitType != UNIT_END && UNITMGR->m_eUnitType != UNIT_MULTISELECT){
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->GetState() == STATE_PRONE){
			if(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType]->IsVisible()){
				if(PtInRect(&m_ProneStandButton[1], MOUSEMGR->GetPos())){
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->Prone();
					}
				}
			}
		} else{
			if(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType]->IsVisible()){
				if(PtInRect(&m_ProneStandButton[0], MOUSEMGR->GetPos())){
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->Prone();
					}
				}
			}
		}
	}

	if(PtInRect(&m_SightButton, MOUSEMGR->GetPos())){
		m_bIsMouseOnSight = true;
		if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
			EnemySight(true);
		} else if(MOUSEMGR->IsClickEnd(MOUSE_LBCLICK)){
			EnemySight(false);
		}
	} else{
		m_bIsMouseOnSight = false;
		EnemySight(false);
	}

	if(KEYMGR->IsKeyPressing(KEY_CTRL)){
		EnemySight(true);
	} else if(KEYMGR->IsKeyUp(KEY_CTRL)){
		EnemySight(false);
	}

	if(UNITMGR->m_eUnitType != UNIT_END && UNITMGR->m_eUnitType != UNIT_MULTISELECT){
		switch(UNITMGR->m_eUnitType){
		case UNIT_GREENBERETS:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRY &&
					dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRYBODY){
					if(PtInRect(&m_InvenButton[UI_PISTOL], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_PISTOL] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_PISTOL;
							UNITMGR->Gun();
						}
					} else{
						m_bInvenButton[UI_PISTOL] = false;
					}
				}
			}
			break;
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(PtInRect(&m_InvenButton[UI_PISTOL], MOUSEMGR->GetPos())){
					m_bInvenButton[UI_PISTOL] = true;
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->m_UnitSkill = UNITFLAG_PISTOL;
						UNITMGR->Gun();
					}
				} else{
					m_bInvenButton[UI_PISTOL] = false;
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_DRIVER:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(PtInRect(&m_InvenButton[UI_SMG], MOUSEMGR->GetPos())){
					m_bInvenButton[UI_SMG] = true;
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->m_UnitSkill = UNITFLAG_PISTOL;
						UNITMGR->Gun();
					}
				} else{
					m_bInvenButton[UI_SMG] = false;
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_GREENBERETS:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(PtInRect(&m_InvenButton[UI_CARRY], MOUSEMGR->GetPos())){
					m_bInvenButton[UI_CARRY] = true;
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->m_UnitSkill = UNITFLAG_CARRY;
						UNITMGR->Carry();
					}
				} else{
					m_bInvenButton[UI_CARRY] = false;
				}
			}
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(!dynamic_cast<CMarine*>(UNITMGR->m_UnitArray[UNIT_MARINE])->GetFoldingBoat()){
					if(PtInRect(&m_InvenButton[UI_CARRY], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_CARRY] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_CARRY;
							UNITMGR->Carry();
						}
					} else{
						m_bInvenButton[UI_CARRY] = false;
					}
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_GREENBERETS:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRY &&
					dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRYBODY){
					if(PtInRect(&m_InvenButton[UI_KNIFE], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_KNIFE] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_KNIFE;
							UNITMGR->Knife();
						}
					} else{
						m_bInvenButton[UI_KNIFE] = false;
					}
				}
			}
			break;
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(PtInRect(&m_InvenButton[UI_KNIFE], MOUSEMGR->GetPos())){
					m_bInvenButton[UI_KNIFE] = true;
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->m_UnitSkill = UNITFLAG_KNIFE;
						UNITMGR->Knife();
					}
				} else{
					m_bInvenButton[UI_KNIFE] = false;
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(dynamic_cast<CMarine*>(UNITMGR->m_UnitArray[UNIT_MARINE])->GetFoldingBoat()){
					if(PtInRect(&m_InvenButton[UI_BOAT], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_BOAT] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_CARRY;
							UNITMGR->Carry();
						}
					} else{
						m_bInvenButton[UI_BOAT] = false;
					}
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(PtInRect(&m_InvenButton[UI_HARPOON], MOUSEMGR->GetPos())){
					m_bInvenButton[UI_HARPOON] = true;
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						UNITMGR->m_UnitSkill = UNITFLAG_HARPOON;
						UNITMGR->Harpoon();
					}

				} else{
					m_bInvenButton[UI_HARPOON] = false;
				}
			}
		default:
			break;
		}

		switch(UNITMGR->m_eUnitType){
		case UNIT_MARINE:
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
				if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fX, UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fY)->eTileType == TILE_WATER){
					if(PtInRect(&m_InvenButton[UI_DIVE], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_DIVE] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_DIVE;
							UNITMGR->Dive();
						}
					} else{
						m_bInvenButton[UI_DIVE] = false;
					}
				}
			}
		default:
			break;
		}

		if(!dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType]->GetInfo().fX, UNITMGR->m_UnitArray[UNITMGR->m_eUnitType]->GetInfo().fY)->eTileType == TILE_WATER){
					if(PtInRect(&m_InvenButton[UI_PICTURE], MOUSEMGR->GetPos())){
						m_bInvenButton[UI_PICTURE] = true;
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							UNITMGR->m_UnitSkill = UNITFLAG_DIVE;
							UNITMGR->QuitVehicle();
						}
					} else{
						m_bInvenButton[UI_PICTURE] = false;
					}
			}
		}
	}
}

void CUIManager::Render(HDC _hdc){
	BMPINFO BmpInfo = {};
	HDC BmpDC;
	int iHp;

	for(int i = 0; i < UNIT_END; ++i){
		if(!UNITMGR->m_UnitArray[i]->IsDead()){
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[i])->GetFocus()){
				if(m_UnitPictueFrame[i] <= 8 * IMAGE_SET_TIMING)
					++m_UnitPictueFrame[i];
				else
					m_UnitPictueFrame[i] = 8 * IMAGE_SET_TIMING;
			} else{
				if(m_UnitPictueFrame[i] >= 0)
					--m_UnitPictueFrame[i];
				else
					m_UnitPictueFrame[i] = 0;
			}
		} else
			m_UnitPictueFrame[i] = 9 * IMAGE_SET_TIMING;
	}


	BmpInfo = BMPMGR->GetBmpInfo(L"GB_UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"GB_UI_SELECT");
	GdiTransparentBlt(_hdc, 10, 0, BmpInfo.cx, BmpInfo.cy,
		BmpDC, BmpInfo.cx * (m_UnitPictueFrame[UNIT_GREENBERETS] / IMAGE_SET_TIMING), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_HP");
	BmpDC = BMPMGR->GetBmpDC(L"UI_HP");
	iHp = UNITMGR->m_UnitArray[UNIT_GREENBERETS]->GetHp();

	if(iHp > 0){
		GdiTransparentBlt(_hdc, 50, 3, BmpInfo.cx, BmpInfo.cy,
			BmpDC, BmpInfo.cx*(5-iHp), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
	}


	BmpInfo = BMPMGR->GetBmpInfo(L"MR_UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"MR_UI_SELECT");
	GdiTransparentBlt(_hdc, 75, 0, BmpInfo.cx, BmpInfo.cy,
		BmpDC, BmpInfo.cx * (m_UnitPictueFrame[UNIT_MARINE] / IMAGE_SET_TIMING), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_HP");
	BmpDC = BMPMGR->GetBmpDC(L"UI_HP");
	iHp = UNITMGR->m_UnitArray[UNIT_MARINE]->GetHp();

	if(iHp > 0){
		GdiTransparentBlt(_hdc, 115, 3, BmpInfo.cx, BmpInfo.cy,
			BmpDC, BmpInfo.cx * (5 - iHp), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
	}

	BmpInfo = BMPMGR->GetBmpInfo(L"DR_UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"DR_UI_SELECT");
	GdiTransparentBlt(_hdc, 140, 0, BmpInfo.cx, BmpInfo.cy,
		BmpDC, BmpInfo.cx * (m_UnitPictueFrame[UNIT_DRIVER] / IMAGE_SET_TIMING), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_HP");
	BmpDC = BMPMGR->GetBmpDC(L"UI_HP");
	iHp = UNITMGR->m_UnitArray[UNIT_DRIVER]->GetHp();

	if(iHp > 0){
		GdiTransparentBlt(_hdc, 180, 3, BmpInfo.cx, BmpInfo.cy,
			BmpDC, BmpInfo.cx * (5 - iHp), 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
	}

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"UI_SELECT");
	GdiTransparentBlt(_hdc, 5, 0, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"UI_SELECT");
	GdiTransparentBlt(_hdc, 70, 0, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

	BmpInfo = BMPMGR->GetBmpInfo(L"UI_SELECT");
	BmpDC = BMPMGR->GetBmpDC(L"UI_SELECT");
	GdiTransparentBlt(_hdc, 135, 0, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);



	switch(UNITMGR->m_eUnitType){
	case UNIT_GREENBERETS:
	case UNIT_MARINE:
	case UNIT_DRIVER:
		if(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType]->IsVisible()){
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->GetState() == STATE_PRONE){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_STAND");
				BmpDC = BMPMGR->GetBmpDC(L"UI_STAND");
				GdiTransparentBlt(_hdc, 470, 0, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			} else{
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_PRONE");
				BmpDC = BMPMGR->GetBmpDC(L"UI_PRONE");
				GdiTransparentBlt(_hdc, 410, 5, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	default:
		break;
	}
	if(m_bIsMouseOnSight){
		BmpInfo = BMPMGR->GetBmpInfo(L"UI_SIGHT");
		BmpDC = BMPMGR->GetBmpDC(L"UI_SIGHT");
		GdiTransparentBlt(_hdc, 748, 0, BmpInfo.cx, BmpInfo.cy,
			BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_MULTISELECT:
	case UNIT_GREENBERETS:
	case UNIT_MARINE:
	case UNIT_DRIVER:
		BmpInfo = BMPMGR->GetBmpInfo(L"UI_BAG");
		BmpDC = BMPMGR->GetBmpDC(L"UI_BAG");
		GdiTransparentBlt(_hdc, 688, 451, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_GREENBERETS:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRY &&
				dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRYBODY){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_PISTOL");
				BmpDC = BMPMGR->GetBmpDC(L"UI_PISTOL");
				GdiTransparentBlt(_hdc, 747, 498, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				if(m_bInvenButton[UI_PISTOL]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_PISTOL_SELECT");
					BmpDC = BMPMGR->GetBmpDC(L"UI_PISTOL_SELECT");
					GdiTransparentBlt(_hdc, 747, 498, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
		break;
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			BmpInfo = BMPMGR->GetBmpInfo(L"UI_PISTOL");
			BmpDC = BMPMGR->GetBmpDC(L"UI_PISTOL");
			GdiTransparentBlt(_hdc, 747, 498, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			if(m_bInvenButton[UI_PISTOL]){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_PISTOL_SELECT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_PISTOL_SELECT");
				GdiTransparentBlt(_hdc, 747, 498, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_DRIVER:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			BmpInfo = BMPMGR->GetBmpInfo(L"UI_SMG");
			BmpDC = BMPMGR->GetBmpDC(L"UI_SMG");
			GdiTransparentBlt(_hdc, 680, 450, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			if(m_bInvenButton[UI_SMG]){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_SMG_SELECT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_SMG_SELECT");
				GdiTransparentBlt(_hdc, 680, 450, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_GREENBERETS:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			BmpInfo = BMPMGR->GetBmpInfo(L"UI_CARRY");
			BmpDC = BMPMGR->GetBmpDC(L"UI_CARRY");
			GdiTransparentBlt(_hdc, 737, 385, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			if(m_bInvenButton[UI_CARRY]){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_CARRY_SELECT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_CARRY_SELECT");
				GdiTransparentBlt(_hdc, 737, 385, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(!dynamic_cast<CMarine*>(UNITMGR->m_UnitArray[UNIT_MARINE])->GetFoldingBoat()){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_CARRY");
				BmpDC = BMPMGR->GetBmpDC(L"UI_CARRY");
				GdiTransparentBlt(_hdc, 737, 385, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				if(m_bInvenButton[UI_CARRY]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_CARRY_SELECT");
					BmpDC = BMPMGR->GetBmpDC(L"UI_CARRY_SELECT");
					GdiTransparentBlt(_hdc, 737, 385, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_GREENBERETS:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRY &&
				dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNIT_GREENBERETS])->GetState() != STATE_CARRYBODY){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_KNIFE");
				BmpDC = BMPMGR->GetBmpDC(L"UI_KNIFE");
				GdiTransparentBlt(_hdc, 678, 455, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);

				if(m_bInvenButton[UI_KNIFE]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_KNIFE_SELECT");
					BmpDC = BMPMGR->GetBmpDC(L"UI_KNIFE_SELECT");
					GdiTransparentBlt(_hdc, 678, 455, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
		break;
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			BmpInfo = BMPMGR->GetBmpInfo(L"UI_KNIFE");
			BmpDC = BMPMGR->GetBmpDC(L"UI_KNIFE");
			GdiTransparentBlt(_hdc, 678, 455, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			if(m_bInvenButton[UI_KNIFE]){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_KNIFE_SELECT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_KNIFE_SELECT");
				GdiTransparentBlt(_hdc, 678, 455, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(dynamic_cast<CMarine*>(UNITMGR->m_UnitArray[UNIT_MARINE])->GetFoldingBoat()){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_BOAT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_BOAT");
				GdiTransparentBlt(_hdc, 650, 503, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				if(m_bInvenButton[UI_BOAT]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_BOAT_SELECT");
					BmpDC = BMPMGR->GetBmpDC(L"UI_BOAT_SELECT");
					GdiTransparentBlt(_hdc, 650, 503, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			BmpInfo = BMPMGR->GetBmpInfo(L"UI_HARPOON");
			BmpDC = BMPMGR->GetBmpDC(L"UI_HARPOON");
			GdiTransparentBlt(_hdc, 692, 458, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			if(m_bInvenButton[UI_HARPOON]){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_HARPOON_SELECT");
				BmpDC = BMPMGR->GetBmpDC(L"UI_HARPOON_SELECT");
				GdiTransparentBlt(_hdc, 692, 458, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_MARINE:
		if(dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fX, UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fY)->eTileType == TILE_WATER){
				BmpInfo = BMPMGR->GetBmpInfo(L"UI_DIVE");
				BmpDC = BMPMGR->GetBmpDC(L"UI_DIVE");
				GdiTransparentBlt(_hdc, 744, 537, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				if(m_bInvenButton[UI_DIVE]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_DIVE_SELECT");
					BmpDC = BMPMGR->GetBmpDC(L"UI_DIVE_SELECT");
					GdiTransparentBlt(_hdc, 744, 537, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
	default:
		break;
	}

	switch(UNITMGR->m_eUnitType){
	case UNIT_GREENBERETS:
		if(!dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNIT_GREENBERETS]->GetInfo().fX, UNITMGR->m_UnitArray[UNIT_GREENBERETS]->GetInfo().fY)->eTileType == TILE_WATER){
				BmpInfo = BMPMGR->GetBmpInfo(L"GB_PICTURE");
				BmpDC = BMPMGR->GetBmpDC(L"GB_PICTURE");
				GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				
				if(m_bInvenButton[UI_PICTURE]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_PICTURE");
					BmpDC = BMPMGR->GetBmpDC(L"UI_PICTURE");
					GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			
			}
		}
		break;
	case UNIT_MARINE:
		if(!dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fX, UNITMGR->m_UnitArray[UNIT_MARINE]->GetInfo().fY)->eTileType == TILE_WATER){
				BmpInfo = BMPMGR->GetBmpInfo(L"MR_PICTURE");
				BmpDC = BMPMGR->GetBmpDC(L"MR_PICTURE");
				GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				
				if(m_bInvenButton[UI_PICTURE]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_PICTURE");
					BmpDC = BMPMGR->GetBmpDC(L"UI_PICTURE");
					GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}

			}
		}
		break;
	case UNIT_DRIVER:
		if(!dynamic_cast<CAlliedUnit*>(UNITMGR->m_UnitArray[UNITMGR->m_eUnitType])->IsVisible()){
			if(TILEMGR->GetTile(UNITMGR->m_UnitArray[UNIT_DRIVER]->GetInfo().fX, UNITMGR->m_UnitArray[UNIT_DRIVER]->GetInfo().fY)->eTileType == TILE_WATER){
				BmpInfo = BMPMGR->GetBmpInfo(L"DR_PICTURE");
				BmpDC = BMPMGR->GetBmpDC(L"DR_PICTURE");
				GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				
				if(m_bInvenButton[UI_PICTURE]){
					BmpInfo = BMPMGR->GetBmpInfo(L"UI_PICTURE");
					BmpDC = BMPMGR->GetBmpDC(L"UI_PICTURE");
					GdiTransparentBlt(_hdc, 700, 500, BmpInfo.cx, BmpInfo.cy, BmpDC, 0, 0, BmpInfo.cx, BmpInfo.cy, BmpInfo.TransColor);
				}
			}
		}
		break;
	default:
		break;
	}
}
