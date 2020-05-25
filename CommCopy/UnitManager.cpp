#include "stdafx.h"
#include "UnitManager.h"
#include "Enemy.h"
#include "RubberBoat.h"

IMPLEMENT_SINGLETON(CUnitManager);

CUnitManager::CUnitManager(): m_pEnemyList(nullptr), m_eUnitType(UNIT_END), m_UnitSkill(0), m_iMultiSound(0){
	memset(&m_UnitArray, 0, sizeof(m_UnitArray));		//배열 초기화
}

CUnitManager::~CUnitManager(){
	Release();
}

void CUnitManager::UnitSelect(){
	static POINT rcpt;
	bool bIsClick = false;
	POINT pt = MOUSEMGR->GetPos();
	INFO* info = nullptr;

	if(m_UnitSkill == 0){
		if(pt.x < WINCX - GAP_X && pt.y> GAP_Y){

			if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
				bIsClick = true;
				for(CGameObject* elem : m_UnitArray){
					dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
				}
				rcpt = MOUSEMGR->GetPos();
			} else if(MOUSEMGR->IsDrag(MOUSE_LBCLICK)){
				m_SelectRC.left = rcpt.x;
				m_SelectRC.top = rcpt.y;
				m_SelectRC.right = pt.x;
				m_SelectRC.bottom = pt.y;
			}
			int iCount = 0;


			if(MOUSEMGR->IsClickEnd(MOUSE_LBCLICK)){
				bool UsedSelectSound = true;

				RECT rc = {};
				int i = 0;
				for(; i< int(UNIT_END); ++i){
					if(IntersectRect(&rc, &m_SelectRC, &(m_UnitArray[i])->GetRect())){
						if(!m_UnitArray[i]->IsDead() && m_UnitArray[i]->IsVisible()){
							dynamic_cast<CAlliedUnit*>(m_UnitArray[i])->SetFocus(true);
							m_eUnitType = UNIT_TYPE(i);
							++iCount;
						}
					}
					if(iCount == 1 && UsedSelectSound){
						switch(UNIT_TYPE(i)){
						case UNIT_GREENBERETS:
							SNDMGR->PlaySound(L"GB_SELECT.wav", SNDMGR->PLAYER);
							UsedSelectSound = false;
							break;
						case UNIT_MARINE:
							SNDMGR->PlaySound(L"MR_SELECT.wav", SNDMGR->PLAYER);
							UsedSelectSound = false;
							break;
						case UNIT_DRIVER:
							SNDMGR->PlaySound(L"DR_SELECT.wav", SNDMGR->PLAYER);
							UsedSelectSound = false;
							break;
						default:
							break;
						}
					}
				}

				if(iCount == 0){
					if(dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->IsControlable())
						if(IntersectRect(&rc, &m_SelectRC, &(m_pVehicleList->front()->GetRect()))){
							for(CGameObject* elem : m_UnitArray){
								dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
							}

							dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->SetFocus(true);
							m_eUnitType = UNIT_MARINE;
							SNDMGR->PlaySound(L"MR_SELECT.wav", SNDMGR->PLAYER);
						}
				}

				memset(&m_SelectRC, 0, sizeof(RECT));

				if(iCount > 1){

					m_eUnitType = UNIT_MULTISELECT;
					//유닛 UI 초기화
				} else if(iCount == 1){
					//유닛 UI 불러오기
				}
				bool checkUnit = false;
				for(CGameObject* elem : m_UnitArray)
					if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus())
						checkUnit = true;

				if(!checkUnit)
					m_eUnitType = UNIT_END;

				return;
			}

			for(int i = 0; i < int(UNIT_END); ++i){
				if(bIsClick && PtInRect(&m_UnitArray[i]->GetRect(), pt)){
					//int curPointX = MOUSEMGR->GetPos().x;
					//int curPointY = MOUSEMGR->GetPos().y;

					if(!m_UnitArray[i]->IsDead()){
						dynamic_cast<CAlliedUnit*>(m_UnitArray[i])->SetFocus(true);
						m_eUnitType = UNIT_TYPE(i);
						m_iMultiSound = UNIT_TYPE(i);
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
					//유닛 UI 불러오기
					return;
				}
			}

			if(dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->IsControlable())
				if(bIsClick && PtInRect(&(m_pVehicleList->front()->GetRect()), pt)){
					for(CGameObject* elem : m_UnitArray){
						dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
					}

					dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->SetFocus(true);
					m_eUnitType = UNIT_MARINE;
				}
		}
	} else{
		rcpt = MOUSEMGR->GetPos();

	}
	if(KEYMGR->IsKeyDown(KEY_CHAR_1)){
		for(CGameObject* elem : m_UnitArray){
			dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
		}
		m_eUnitType = UNIT_GREENBERETS;
		dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_GREENBERETS])->SetFocus(true);
		info = &m_UnitArray[UNIT_GREENBERETS]->GetInfo();
		SCRLMGR->SetScrollValue(info->fX, info->fY);
		if(m_UnitArray[UNIT_GREENBERETS]->IsDead()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_GREENBERETS])->SetFocus(false);
			m_eUnitType = UNIT_END;
		} else{
			SNDMGR->PlaySound(L"GB_SELECT.wav", SNDMGR->EFFECT);
		}
	} else if(KEYMGR->IsKeyDown(KEY_CHAR_2)){
		for(CGameObject* elem : m_UnitArray){
			dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
		}
		m_eUnitType = UNIT_MARINE;
		dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_MARINE])->SetFocus(true);
		if(dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_MARINE])->GetState() == STATE_VEHICLE)
			dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->SetFocus(true);
		info = &m_UnitArray[UNIT_MARINE]->GetInfo();
		SCRLMGR->SetScrollValue(info->fX, info->fY);
		if(m_UnitArray[UNIT_MARINE]->IsDead()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_MARINE])->SetFocus(false);
			m_eUnitType = UNIT_END;
		}else{
			SNDMGR->PlaySound(L"MR_SELECT.wav", SNDMGR->EFFECT);
		}
	} else if(KEYMGR->IsKeyDown(KEY_CHAR_3)){
		for(CGameObject* elem : m_UnitArray){
			dynamic_cast<CAlliedUnit*>(elem)->SetFocus(false);
		}
		m_eUnitType = UNIT_DRIVER;
		dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_DRIVER])->SetFocus(true);
		info = &m_UnitArray[UNIT_DRIVER]->GetInfo();
		SCRLMGR->SetScrollValue(info->fX, info->fY);
		if(m_UnitArray[UNIT_DRIVER]->IsDead()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[UNIT_DRIVER])->SetFocus(false);
			m_eUnitType = UNIT_END;
		} else{
			SNDMGR->PlaySound(L"DR_SELECT.wav", SNDMGR->EFFECT);
		}
	}

	if(KEYMGR->IsKeyDown(KEY_CHAR_0))
		for(CGameObject* elem : m_UnitArray){
			if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_DEAD){
				dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_STAND);
				elem->GetInfo().iHp = 5;
				elem->GetInfo().bIsDead = false;
			}
		}

}


void CUnitManager::UnitControl(){
	if(KEYMGR->IsKeyDown(KEY_CHAR_Z)){
		Prone();
	}

	if(MOUSEMGR->IsClick(MOUSE_RBCLICK)){
		if(UNIT_MULTISELECT != m_eUnitType && UNIT_END != m_eUnitType){
			if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetSkill() != SKILL_NULL){
				if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() == STATE_LADDER){
					return;
				}
				if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() != STATE_CARRYBODY){
					dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_STAND);
					dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_NULL);
					dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(nullptr);
				}
			}
		}
		if(m_UnitSkill){
			m_UnitSkill = UNITFLAG_NULL;
		} else{
			EFCTMGR->LoadEffect(EFFECT_MOVE, MOUSEMGR->GetPos());
			Move();
		}
	}

	if(m_eUnitType != UNIT_MULTISELECT && m_eUnitType != UNIT_END){
		if(KEYMGR->IsKeyDown(KEY_CHAR_X)){
			m_UnitSkill = UNITFLAG_KNIFE;
		} else if(KEYMGR->IsKeyDown(KEY_CHAR_G)){
			m_UnitSkill = UNITFLAG_PISTOL;
		} else if(KEYMGR->IsKeyDown(KEY_CHAR_C)){
			m_UnitSkill = UNITFLAG_CARRY;
		} else if(KEYMGR->IsKeyDown(KEY_CHAR_H)){
			m_UnitSkill = UNITFLAG_HARPOON;
		} else if(KEYMGR->IsKeyDown(KEY_CHAR_D)){
			m_UnitSkill = UNITFLAG_DIVE;
		} else if(KEYMGR->IsKeyDown(KEY_CHAR_U)){
			m_UnitSkill = UNITFLAG_QUITBOAT;
		}
	}

	switch(m_UnitSkill){
	case UNITFLAG_KNIFE:
		MOUSEMGR->SetMouseCursor(MOUSE_N_KNIFE);
		Knife();
		break;
	case UNITFLAG_PISTOL:
		MOUSEMGR->SetMouseCursor(MOUSE_PISTOL);
		Gun();
		break;
	case UNITFLAG_CARRY:
		MOUSEMGR->SetMouseCursor(MOUSE_N_CARRY);
		Carry(); 
		break;
	case UNITFLAG_HARPOON:
		Harpoon();
		break;
	case UNITFLAG_DIVE:
		Dive();
		break;
	case UNITFLAG_QUITBOAT:
		QuitVehicle();
		break;
	default:
		break;
	}

	if(m_UnitSkill == UNITFLAG_NULL){
		MOUSEMGR->SetMouseCursor(MOUSE_DEFAULT);
	}
}

void CUnitManager::Prone(){
	POINT pt = {};

	if(m_eUnitType == UNIT_MULTISELECT){
		STATE_TYPE eState;
		for(CGameObject* elem : m_UnitArray){
			if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus()){
				eState = dynamic_cast<CAlliedUnit*>(elem)->GetState();
				break;
			}
		}

		for(CGameObject* elem : m_UnitArray)
			if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus()){
				pt.x = int(elem->GetInfo().fX - SCRLMGR->m_fScrollX);
				pt.y = int(elem->GetInfo().fY - SCRLMGR->m_fScrollY);
				dynamic_cast<CAlliedUnit*>(elem)->SetDest(pt);

				if(eState == STATE_PRONE)
					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_STAND);
				else
					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_PRONE);
			}
	} else{
		for(CGameObject* elem : m_UnitArray){
			if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus()){
				pt.x = int(elem->GetInfo().fX - SCRLMGR->m_fScrollX);
				pt.y = int(elem->GetInfo().fY - SCRLMGR->m_fScrollY);
				dynamic_cast<CAlliedUnit*>(elem)->SetDest(pt);

				if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_PRONE)
					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_STAND);

				else if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_CARRYBODY){
					Carry();
					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_PRONE);

				} else
					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_PRONE);
			}
		}
	}
}

void CUnitManager::Move(){
	POINT pt = MOUSEMGR->GetPos();
	CGameObject* Boat = OBJMGR->GetList(OBJ_VEHICLE).front();

	if(pt.x < WINCX - GAP_X && pt.y> GAP_Y){
		if(m_eUnitType == UNIT_GREENBERETS){
			if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() == STATE_CARRYBODY){
				dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetDest(pt);
				return;
			}
		}

		if(KEYMGR->IsKeyPressing(KEY_SHIFT)){
			for(CGameObject* elem : m_UnitArray){
				if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus()){
					if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_VEHICLE)
						return;
					if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_CARRY)
						return;
					if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_CARRYBODY)
						return;

					dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_RUN);

					if(nullptr != Boat)
						if(m_eUnitType != UNIT_MULTISELECT)
							if(PtInRect(&Boat->GetRect(), pt))
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_VEHICLE);
					if(m_eUnitType == UNIT_GREENBERETS)
						if(TILEMGR->GetTile(pt.x + SCRLMGR->m_fScrollX, pt.y + SCRLMGR->m_fScrollY)->eTileType == TILE_WALL)
							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_LADDER);

					dynamic_cast<CAlliedUnit*>(elem)->SetDest(pt);
				}
			}
		} else{
			for(CGameObject* elem : m_UnitArray){
				if(dynamic_cast<CAlliedUnit*>(elem)->GetFocus()){
					if(nullptr != Boat)
						if(m_eUnitType != UNIT_MULTISELECT && m_eUnitType != UNIT_END)
							if(Boat->IsVisible())
								if(PtInRect(&Boat->GetRect(), pt))
									dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_VEHICLE);

					if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_VEHICLE)
						if(m_eUnitType == UNIT_MARINE){
							dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->SetDest(pt);
							return;
						} else
							return;

						if(m_eUnitType == UNIT_GREENBERETS)
							if(TILEMGR->GetTile(pt.x + SCRLMGR->m_fScrollX, pt.y + SCRLMGR->m_fScrollY)->eTileType == TILE_WALL)
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_LADDER);

						dynamic_cast<CAlliedUnit*>(elem)->SetDest(pt);

						if(dynamic_cast<CAlliedUnit*>(elem)->GetState() == STATE_RUN)
							dynamic_cast<CAlliedUnit*>(elem)->SetState(STATE_WALK);

				}
			}
		}
	}
}

void CUnitManager::Knife(){
	switch(m_eUnitType){
	case UNIT_GREENBERETS:
	case UNIT_MARINE:
		switch(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState()){
		case STATE_STAND:
		case STATE_WALK:
		case STATE_RUN:
		case STATE_PRONE:
			POINT pt = MOUSEMGR->GetPos();

			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_KNIFE);

			for(CGameObject* elem : *m_pEnemyList){
				if(PtInRect(&elem->GetRect(), pt)){
					MOUSEMGR->SetMouseCursor(MOUSE_KNIFE);
					if(!elem->IsDead())
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							if(KEYMGR->IsKeyPressing(KEY_SHIFT))
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_RUN);
							else
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_WALK);

							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(elem);

							m_UnitSkill = UNITFLAG_NULL;
						}
				} 
			}
			break;
		default:
			break;
		}
		break;
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}

}

void CUnitManager::Gun(){
	POINT pt = MOUSEMGR->GetPos();

	switch(m_eUnitType){
	case UNIT_GREENBERETS:
	case UNIT_MARINE:
		if(!m_UnitArray[m_eUnitType]->IsDead()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_GUN);

			if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
				if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetShotPoint(pt)){
					EFCTMGR->LoadEffect(EFFECT_PISTOL, pt);
					for(CGameObject* elem : *m_pEnemyList){
						if(PtInRect(&elem->GetRect(), pt)){
							elem->SetDamage(1);
						}

						POINT FiringTargetPt = { (LONG)m_UnitArray[m_eUnitType]->GetInfo().fX, (LONG)m_UnitArray[m_eUnitType]->GetInfo().fY };

						INFO& pEnemyInfo = elem->GetInfo();

						if(TILEMGR->GetTile(FiringTargetPt)->dwTileColor == TILEMGR->GetTile(pEnemyInfo.fX, pEnemyInfo.fY)->dwTileColor){
							float fDist = sqrtf(SQUERE(float(FiringTargetPt.x) - pEnemyInfo.fX) + SQUERE(float(FiringTargetPt.y) - pEnemyInfo.fY));

							if(fDist < 400.f){
								dynamic_cast<CEnemy*>(elem)->SetTarget(FiringTargetPt);
							}
						}
					}

					for(CGameObject* elem : OBJMGR->GetList(OBJ_USEOBJ))
						if(PtInRect(&elem->GetRect(), pt)){
							elem->SetDamage(1);
						}
				}

			}
		}
		break;
	case UNIT_DRIVER:
		if(!m_UnitArray[m_eUnitType]->IsDead()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_GUN);

			if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
				if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetShotPoint(pt)){
					EFCTMGR->LoadEffect(EFFECT_PISTOL, pt);
					for(CGameObject* elem : *m_pEnemyList){
						float fDist = sqrtf(float(SQUERE((pt.x + SCRLMGR->m_fScrollX) - elem->GetInfo().fX) + SQUERE((pt.y + SCRLMGR->m_fScrollY) - elem->GetInfo().fY)));
						if(50.f > fDist){
							elem->SetDamage(3);
							elem->GetInfo().bIsDead = true;
						}

						POINT FiringTargetPt = { (LONG)m_UnitArray[m_eUnitType]->GetInfo().fX, (LONG)m_UnitArray[m_eUnitType]->GetInfo().fY };

						INFO& pEnemyInfo = elem->GetInfo();

						if(TILEMGR->GetTile(FiringTargetPt)->dwTileColor == TILEMGR->GetTile(pEnemyInfo.fX, pEnemyInfo.fY)->dwTileColor){
							float fDist = sqrtf(SQUERE(float(FiringTargetPt.x) - pEnemyInfo.fX) + SQUERE(float(FiringTargetPt.y) - pEnemyInfo.fY));

							if(fDist < 400.f){
								dynamic_cast<CEnemy*>(elem)->SetTarget(FiringTargetPt);
							}
						}
					}

					for(CGameObject* elem : OBJMGR->GetList(OBJ_USEOBJ)){
							float fDist = sqrtf(float(SQUERE((pt.x + SCRLMGR->m_fScrollX) - elem->GetInfo().fX) + SQUERE((pt.y + SCRLMGR->m_fScrollY) - elem->GetInfo().fY)));
							if(50.f > fDist){
								elem->SetDamage(3);
							}
						}
				}
			}
		}
		break;
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}
}

void CUnitManager::Carry(){
	POINT pt = {};
	switch(m_eUnitType){
	case UNIT_GREENBERETS:
		pt = MOUSEMGR->GetPos();
		if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() != STATE_CARRYBODY &&
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() != STATE_CARRY){

			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_CARRYBODY);

			for(CGameObject* elem : *m_pEnemyList){
				if(PtInRect(&elem->GetRect(), pt)){
					MOUSEMGR->SetMouseCursor(MOUSE_CARRY);
					if(elem->IsDead())
						if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
							if(KEYMGR->IsKeyPressing(KEY_SHIFT))
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_RUN);
							else
								dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_WALK);

							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(elem);

							m_UnitSkill = UNITFLAG_NULL;
							return;
						}
				}
			}

			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_CARRY);

			for(CGameObject* elem : OBJMGR->GetList(OBJ_USEOBJ)){
				if(PtInRect(&elem->GetRect(), pt)){
					MOUSEMGR->SetMouseCursor(MOUSE_CARRY);
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						if(KEYMGR->IsKeyPressing(KEY_SHIFT))
							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_RUN);
						else
							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_WALK);

						dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(elem);

						m_UnitSkill = UNITFLAG_NULL;
						return;
					}
				}
			}
		} else if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() == STATE_CARRYBODY){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_STAND);
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SoundAction();
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_NULL);
			CGameObject* pTarget = dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetTarget();
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(nullptr);
			if(nullptr != pTarget){
				pTarget->SetPosition(m_UnitArray[m_eUnitType]->GetInfo().fX, m_UnitArray[m_eUnitType]->GetInfo().fY);
				pTarget->SetVisible(true);
			}
			m_UnitSkill = UNITFLAG_NULL;
		} else if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() == STATE_CARRY){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_STAND);
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SoundAction();
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_NULL);
			CGameObject* pTarget = dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetTarget();
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetTarget(nullptr);
			if(nullptr != pTarget){
				pTarget->SetPosition(m_UnitArray[m_eUnitType]->GetInfo().fX, m_UnitArray[m_eUnitType]->GetInfo().fY);
				pTarget->SetVisible(true);
			}
			m_UnitSkill = UNITFLAG_NULL;
		}
		break;
	case UNIT_MARINE:
		pt = MOUSEMGR->GetPos();
		if(!dynamic_cast<CMarine*>(m_UnitArray[m_eUnitType])->GetFoldingBoat()){
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_CARRY);

			if(PtInRect(&m_pVehicleList->front()->GetRect(), pt)){
				MOUSEMGR->SetMouseCursor(MOUSE_CARRY);
				if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
					if(KEYMGR->IsKeyPressing(KEY_SHIFT))
						dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_RUN);
					else
						dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_WALK);

					dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetDest(pt);

					m_UnitSkill = UNITFLAG_NULL;
				}
			}
		} else{
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_CARRY);
			dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SoundAction();

			dynamic_cast<CMarine*>(m_UnitArray[m_eUnitType])->SetFoldingBoat(false);
		}
		break;
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}
}

void CUnitManager::Dive(){
	TILEINFO* tile = nullptr;
	switch(m_eUnitType){
	case UNIT_MARINE:
		tile = TILEMGR->GetTile(m_UnitArray[m_eUnitType]->GetInfo().fX, m_UnitArray[m_eUnitType]->GetInfo().fY);
		if(tile->dwTileColor == RGB(0, 255, 255)){
			if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() != STATE_DIVE){
				dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_DIVE);
				m_UnitSkill = UNITFLAG_NULL;
			} else{
				dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_STAND);
				m_UnitSkill = UNITFLAG_NULL;
			}
		}
		break;
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}
}

void CUnitManager::Harpoon(){
	switch(m_eUnitType){
	case UNIT_MARINE:
		POINT pt = MOUSEMGR->GetPos();

		dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetSkill(SKILL_HARPOON);


		for(CGameObject* elem : *m_pEnemyList){
			if(PtInRect(&elem->GetRect(), pt))
				if(!elem->IsDead())
					if(MOUSEMGR->IsClick(MOUSE_LBCLICK)){
						dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetShotPoint(pt);
						elem->SetDamage(3);
						m_UnitSkill = UNITFLAG_NULL;
					}
		}
		break;
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}
}

void CUnitManager::QuitVehicle(){
	INFO* info = nullptr;
	switch(m_eUnitType){
	case UNIT_GREENBERETS:
	case UNIT_MARINE:
	case UNIT_DRIVER:
		if(dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->GetState() == STATE_VEHICLE){
			info = &m_UnitArray[m_eUnitType]->GetInfo();
			if(TILEMGR->GetTile(info->fX, info->fY)->eTileType == TILE_WATER || TILEMGR->GetTile(info->fX, info->fY)->eTileType == TILE_NULL){
				for(int i = -10; i < 10; i += 10)
					for(int j = -10; j < 10; j += 10){
						if(i == 0 && j == 0)
							continue;

						if(TILEMGR->GetTile(info->fX + (float)i, info->fY + (float)j)->eTileType == TILE_WATER
							|| TILEMGR->GetTile(info->fX, info->fY)->eTileType == TILE_NULL){
							dynamic_cast<CRubberBoat*>(m_pVehicleList->front())->QuitBoat(m_eUnitType);
							m_UnitArray[m_eUnitType]->SetVisible(true);
							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SetState(STATE_STAND);
							dynamic_cast<CAlliedUnit*>(m_UnitArray[m_eUnitType])->SoundAction();

							info->fX += i;
							info->fY += j;

							m_UnitSkill = UNITFLAG_NULL;
							return;
						}
					}
			} else{
				m_UnitSkill = UNITFLAG_NULL;
				return;
			}
		} else{
			m_UnitSkill = UNITFLAG_NULL;
			return;
		}
	default:
		m_UnitSkill = UNITFLAG_NULL;
		return;
	}
}

void CUnitManager::Release(){

}

void CUnitManager::Initialize(){
	SetEnemyList();
	SetVehicleList();
}

void CUnitManager::Update(){
	if(m_eUnitType != UNIT_MULTISELECT && m_eUnitType != UNIT_END)
		if(m_UnitArray[m_eUnitType]->IsDead()){
			m_eUnitType = UNIT_END;
		}

	UnitSelect();
	UnitControl();
}

void CUnitManager::Render(HDC _hdc){
	Rectangle(_hdc, m_SelectRC.left, m_SelectRC.top, m_SelectRC.right, m_SelectRC.bottom);
}

