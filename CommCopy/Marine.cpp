#include "stdafx.h"
#include "Marine.h"
#include "RubberBoat.h"

CMarine::CMarine(): m_bFoldingBoat(false){
	
}

CMarine::~CMarine(){
	Release();
}

void CMarine::Release(){
	for(POINT* elem : m_DestPtList)
		SafeDelete(elem);
	m_DestPtList.clear();
}

void CMarine::Initialize(){
	BMPMGR->AddBMP(L"MR_WALK", PATH_MR_WALK);
	BMPMGR->SetBmpInfo(L"MR_WALK", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_RUN", PATH_MR_RUN);
	BMPMGR->SetBmpInfo(L"MR_RUN", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_PRONE", PATH_MR_PRONE);
	BMPMGR->SetBmpInfo(L"MR_PRONE", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_KNIFE", PATH_MR_KNIFE);
	BMPMGR->SetBmpInfo(L"MR_KNIFE", 4, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_PISTOL", PATH_MR_PISTOL);
	BMPMGR->SetBmpInfo(L"MR_PISTOL", 4, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_HARPOON", PATH_MR_HARPOON);
	BMPMGR->SetBmpInfo(L"MR_HARPOON", 4, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_DIVE", PATH_MR_DIVE);
	BMPMGR->SetBmpInfo(L"MR_DIVE", 6, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_FOLD", PATH_MR_FOLD);
	BMPMGR->SetBmpInfo(L"MR_FOLD", 3, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"MR_STAND", PATH_MR_STAND);
	BMPMGR->SetBmpInfo(L"MR_STAND", 1, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_DEAD1", PATH_MR_DEAD1);
	BMPMGR->SetBmpInfo(L"MR_DEAD1", 7, 1, RGB(255, 255, 255));


	m_bmpDC = BMPMGR->GetBmpDC(L"MR_STAND");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_STAND");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fX = 500.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fSpeed = 1.5f;
	m_tInfo.fAngle = -(PI / 4.f);
	m_tInfo.iHp = 5;

	m_eUnitType = UNIT_MARINE;


	CGameObject::UpdateRect();
}

int CMarine::Update(){
	float fSpeed = 0.f;
	TILEINFO* pTargetTile = nullptr;
	POINT* pt = nullptr;
	CAlliedUnit::ConfigState(fSpeed);
	RECT rc = {};
	CGameObject* pObj = nullptr;

	

		if(m_tInfo.bIsDead){
			m_bFocus = false;
			m_eState = STATE_DEAD;
			m_eAngle = ANGLE_TYPE(0);
		} else{
			if(m_tInfo.iHp <= 0){
				SNDMGR->PlaySound(L"MR_DIED.wav", SNDMGR->EFFECT);
				m_tInfo.bIsDead = true;
				return 0;
			}
			switch(m_eSkillType){
			case SKILL_KNIFE:
				if(m_pTargetObj != nullptr){
					pTargetTile = TILEMGR->GetTile(m_pTargetObj->GetInfo().fX, m_pTargetObj->GetInfo().fY);
					if(m_DestPtList.size() == 1){
						SafeDelete(m_DestPtList.front());
						m_DestPtList.clear();
						m_eState = STATE_KNIFE;
						m_iFrameX = 0;
						m_eSkillType = SKILL_NULL;
					} else if(TILEMGR->GetTile(*m_DestPtList.back()) != pTargetTile){
						pt = new POINT{ int(pTargetTile->fX), int(pTargetTile->fY) };
						m_DestPtList.push_back(pt);
						pt = nullptr;
					}
				}
				break;
			case SKILL_GUN:
				for(POINT* elem : m_DestPtList)
					SafeDelete(elem);
				m_DestPtList.clear();
				m_eState = STATE_GUN;
				break;
			case SKILL_HARPOON:
				for(POINT* elem : m_DestPtList)
					SafeDelete(elem);
				m_DestPtList.clear();
				m_eState = STATE_HARPOON;
				break;
			case SKILL_VEHICLE:
				pObj = OBJMGR->GetList(OBJ_VEHICLE).front();
				if(IntersectRect(&rc, &m_tRECT, &pObj->GetRect())){
					m_eState = STATE_VEHICLE;
					for(POINT* elem : m_DestPtList)
						SafeDelete(elem);
					m_DestPtList.clear();
					m_eSkillType = SKILL_NULL;

					dynamic_cast<CRubberBoat*>(pObj)->SetUnit(UNIT_MARINE, this);
				}
				break;
			case SKILL_CARRY:
				if(!m_bFoldingBoat){
					pObj = OBJMGR->GetList(OBJ_VEHICLE).front();
					POINT currPt = { LONG(m_tInfo.fX - SCRLMGR->m_fScrollX), LONG(m_tInfo.fY - SCRLMGR->m_fScrollY) };
					if(PtInRect(&pObj->GetRect(), currPt)){
						for(POINT* elem : m_DestPtList)
							SafeDelete(elem);
						m_DestPtList.clear();
					
						if(dynamic_cast<CRubberBoat*>(pObj)->FoldingBoat()){
							m_bFoldingBoat = true;
							m_eSkillType = SKILL_NULL;
							m_eState = STATE_CARRY;
							dynamic_cast<CRubberBoat*>(pObj)->SetVisible(false);
							m_iFrameX = BMPMGR->GetBmpInfo(L"MR_FOLD").FrameX * IMAGE_SET_TIMING - 1;
						} else{
							m_iFrameX = 0;
							m_eState = STATE_STAND;
							m_eSkillType = SKILL_CARRY;
						}
					}
				} 
				break;
			default:
				break;
			}

			switch(m_eState){
			case STATE_STAND:
			case STATE_WALK:
			case STATE_RUN:
			case STATE_PRONE:
				if(m_DestPtList.size() > 0){
					if(STATE_STAND == m_eState)
						m_eState = STATE_WALK;

					CAlliedUnit::CalculateDist();

					if(m_fDist > fSpeed){
						CAlliedUnit::CalculateAngle();
						m_tInfo.fX += fSpeed * cos(m_tInfo.fAngle);
						m_tInfo.fY -= fSpeed * sin(m_tInfo.fAngle);
					} else{
						m_tInfo.fX = float(m_DestPtList.front()->x);
						m_tInfo.fY = float(m_DestPtList.front()->y);

						SafeDelete(m_DestPtList.front());
						m_DestPtList.pop_front();
					}
				} else{
					m_eState = m_eState != STATE_PRONE ? STATE_STAND : STATE_PRONE;
					m_iFrameX = 0;
				}
				break;
			case STATE_DIVE:
				if(m_DestPtList.size() > 0){
					if(STATE_STAND == m_eState)
						m_eState = STATE_WALK;

					CAlliedUnit::CalculateDist();

					if(m_fDist > fSpeed){
						CAlliedUnit::CalculateAngle();
						m_tInfo.fX += fSpeed * cos(m_tInfo.fAngle);
						m_tInfo.fY -= fSpeed * sin(m_tInfo.fAngle);
					} else{
						m_tInfo.fX = float(m_DestPtList.front()->x);
						m_tInfo.fY = float(m_DestPtList.front()->y);

						SafeDelete(m_DestPtList.front());
						m_DestPtList.pop_front();
					}
				} else{
					m_iFrameX = 0;
				}
				break;
			case STATE_CARRY:
				if(m_bFoldingBoat){
					if(m_iFrameX <= 0){
						m_iFrameX = 0;
						m_eState = STATE_STAND;
					} else{
						--m_iFrameX;
					}
				} else{
					if(m_iFrameX >= BMPMGR->GetBmpInfo(L"MR_FOLD").FrameX * IMAGE_SET_TIMING - 1){
						m_iFrameX = 0;
						m_eState = STATE_STAND;
						if(pObj != nullptr){
							pObj->SetPosition(m_tInfo.fX + cosf(m_tInfo.fAngle) * 30, m_tInfo.fY - sinf(m_tInfo.fAngle) * 30);
							dynamic_cast<CRubberBoat*>(pObj)->SetVisible(true);
							dynamic_cast<CRubberBoat*>(pObj)->OpenBoat();
						}
					} else{
						++m_iFrameX;
					}

				}
			default:
				break;
			}
		}
	
	CGameObject::UpdateRect();
	return 0;
}

void CMarine::Render(HDC _hdc){
	if(m_bIsVisible){
		switch(m_eState){
		case STATE_STAND:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_STAND");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_STAND");
			break;
		case STATE_WALK:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_WALK");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_WALK");
			break;
		case STATE_RUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_RUN");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_RUN");
			break;
		case STATE_PRONE:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_PRONE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_PRONE");
			break;
		case STATE_KNIFE:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_KNIFE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_KNIFE");
			break;
		case STATE_GUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_PISTOL");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_PISTOL");
			break;
		case STATE_HARPOON:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_HARPOON");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_HARPOON");
			break;
		case STATE_DIVE:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_DIVE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_DIVE");
			break;
		case STATE_CARRY:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_FOLD");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_FOLD");
			break;
		case STATE_DEAD:
			m_bmpDC = BMPMGR->GetBmpDC(L"MR_DEAD1");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"MR_DEAD1");
			break;

		default:
			break;
		}

		if(1 < m_BmpInfo.FrameX){
			switch(m_eState){
			case STATE_WALK:
			case STATE_RUN:
			case STATE_PRONE:
				m_iFrameX = m_iFrameX < (m_BmpInfo.FrameX * IMAGE_SET_TIMING) - 1 ? m_iFrameX + 1 : 0;
				break;
			case STATE_DIVE:
				SNDMGR->PlaySound(L"EFFECT_DIVE.wav", SNDMGR->EFFECT);
				m_iFrameX = m_iFrameX < (m_BmpInfo.FrameX * IMAGE_SET_TIMING) - 1 ? m_iFrameX + 1 : 0;
				break;
			case STATE_KNIFE:
				if(m_iFrameX < (m_BmpInfo.FrameX * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else{
					m_eState = STATE_STAND;
					m_iFrameX = 0;
					m_pTargetObj->SetDamage(3);
					m_pTargetObj->GetInfo().bIsDead = true;
					m_pTargetObj = nullptr;
				}
				break;
			case STATE_GUN:
				if(m_iFrameX < ((m_BmpInfo.FrameX - 2) * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else
					if(m_bIsShot){
						++m_iFrameX;
						if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1)
							m_bIsShot = false;
					} else
						m_iFrameX = (m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING - 1;
					break;
			case STATE_HARPOON:
				if(m_iFrameX < ((m_BmpInfo.FrameX - 2) * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else
					if(m_bIsShot){
						++m_iFrameX;
						if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1){
							SNDMGR->PlaySound(L"EFFECT_HARPOON.wav", SNDMGR->EFFECT);
							m_bIsShot = false;
							m_eState = STATE_STAND;
							m_eSkillType = SKILL_NULL;
						}
					} else{
						m_iFrameX = (m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING - 1;
					}
				break;
			case STATE_CARRY:
				break;
			case STATE_DEAD:
				if(m_iFrameX < ((m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else
					m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1;
				break;

			default:
				break;
			}
		}

		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, m_BmpInfo.cx, m_BmpInfo.cy,
			m_bmpDC, m_BmpInfo.cx * (m_iFrameX / IMAGE_SET_TIMING), m_BmpInfo.cy * int(m_eAngle), m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
	
		if(m_bFocus)
			GdiTransparentBlt(_hdc, LONG(m_tInfo.fX - SCRLMGR->m_fScrollX) - 12, LONG(m_tInfo.fY - SCRLMGR->m_fScrollY) - 7, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cx, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cy,
				BMPMGR->GetBmpDC(L"CURSOR_FOCUS"), 0, 0, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cx, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cy, m_BmpInfo.TransColor);

	}
}