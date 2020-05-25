#include "stdafx.h"
#include "GreenBerets.h"
#include "RubberBoat.h"

CGreenBerets::CGreenBerets() : m_bIsLadderEnd(false){
}

CGreenBerets::~CGreenBerets(){
	Release();
}

void CGreenBerets::Release(){
	for(POINT* elem : m_DestPtList)
		SafeDelete(elem);
	m_DestPtList.clear();
}

void CGreenBerets::Initialize(){
	BMPMGR->AddBMP(L"GB_WALK", PATH_GB_WALK);
	BMPMGR->SetBmpInfo(L"GB_WALK", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_RUN", PATH_GB_RUN);
	BMPMGR->SetBmpInfo(L"GB_RUN", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_PRONE", PATH_GB_PRONE);
	BMPMGR->SetBmpInfo(L"GB_PRONE", 8, 8, RGB(255, 255, 255));


	BMPMGR->AddBMP(L"GB_STAND", PATH_GB_STAND);
	BMPMGR->SetBmpInfo(L"GB_STAND", 1, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_DEAD1", PATH_GB_DEAD1);
	BMPMGR->SetBmpInfo(L"GB_DEAD1", 5, 1, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_KNIFE", PATH_GB_KNIFE);
	BMPMGR->SetBmpInfo(L"GB_KNIFE", 4, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_PISTOL", PATH_GB_PISTOL);
	BMPMGR->SetBmpInfo(L"GB_PISTOL", 5, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_CARRYBODY", PATH_GB_CARRYBODY);
	BMPMGR->SetBmpInfo(L"GB_CARRYBODY", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_CARRY", PATH_GB_CARRY);
	BMPMGR->SetBmpInfo(L"GB_CARRY", 8, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_LADDER", PATH_GB_LADDER);
	BMPMGR->SetBmpInfo(L"GB_LADDER", 7, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"GB_LADDEREND", PATH_GB_LADDEREND);
	BMPMGR->SetBmpInfo(L"GB_LADDEREND", 6, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"CURSOR_FOCUS", PATH_CURSOR_FOCUS);
	BMPMGR->SetBmpInfo(L"CURSOR_FOCUS", 1, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"GB_STAND");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_STAND");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fSpeed = 1.5f;
	m_tInfo.fAngle = -(PI / 4.f);
	m_tInfo.bIsDead = false;
	m_tInfo.iHp = 5;

	m_eUnitType = UNIT_GREENBERETS;
	CGameObject::UpdateRect();
}

int CGreenBerets::Update(){
	float fSpeed = 0.f;
	TILEINFO* pTargetTile = nullptr;
	POINT* pt = nullptr;
	CAlliedUnit::ConfigState(fSpeed);
	CGameObject* pObj = nullptr;
	RECT rc = {};


	if(m_tInfo.bIsDead){
		m_bFocus = false;
		m_eState = STATE_DEAD;
		m_eAngle = ANGLE_TYPE(0);
	} else{
		if(m_tInfo.iHp <= 0){
			SNDMGR->PlaySound(L"GB_DIED.wav", SNDMGR->EFFECT);
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
				} else if(pTargetTile == TILEMGR->GetTile(m_tInfo.fX, m_tInfo.fY)){
					for(POINT* elem : m_DestPtList)
						SafeDelete(elem);
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
			m_eState = STATE_GUN;
			break;
		case SKILL_CARRYBODY:
			if(m_pTargetObj != nullptr){
				if(m_DestPtList.size() == 0){
					m_eState = STATE_CARRYBODY;
					m_iFrameX = IMAGE_SET_TIMING * 3;
					m_eSkillType = SKILL_NULL;
					m_pTargetObj->SetVisible(false);
				}
			}
			break;
		case SKILL_CARRY:
			if(m_pTargetObj != nullptr){
				if(m_DestPtList.size() == 0){
					m_eState = STATE_CARRY;
					m_iFrameX = 0;
					m_eSkillType = SKILL_NULL;
					m_pTargetObj->SetVisible(false);
				}
			}
			break;
		case SKILL_LADDER:
			if(TILEMGR->GetTile(m_tInfo.fX, m_tInfo.fY)->eTileType == TILE_WALL){
				m_eState = STATE_LADDER;
				m_eAngle = ANGLE_RUP;
				m_iFrameX = 0;
				for(POINT* elem : m_DestPtList)
					SafeDelete(elem);
				m_DestPtList.clear();
				m_eSkillType = SKILL_NULL;
			}
			break;
		case SKILL_VEHICLE:
			pObj = OBJMGR->GetList(OBJ_VEHICLE).front();
			if(IntersectRect(&rc, &m_tRECT, &pObj->GetRect())){
				m_eState = STATE_VEHICLE;
				for(POINT* elem : m_DestPtList)
					SafeDelete(elem);
				m_DestPtList.clear();
				m_eSkillType = SKILL_NULL;

				dynamic_cast<CRubberBoat*>(pObj)->SetUnit(UNIT_GREENBERETS, this);
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
		case STATE_CARRYBODY:
			if(m_DestPtList.size() > 0){
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
				m_iFrameX = IMAGE_SET_TIMING * 3;
			}
			break;
		case STATE_CARRY:
			if(m_DestPtList.size() > 0){
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
		case STATE_LADDER:
			if(!m_bIsLadderEnd)
				m_tInfo.fY -= fSpeed;
			else
				m_tInfo.fY += fSpeed;
			break;
		case STATE_LADDEREND:
			m_tInfo.fX += 0.2f;
			m_tInfo.fY -= 0.2f;
			break;
		default:
			break;
		}
	}

	CGameObject::UpdateRect();

	return 0;
}

void CGreenBerets::Render(HDC _hdc){
	if(m_bIsVisible){
		switch(m_eState){
		case STATE_STAND:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_STAND");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_STAND");
			break;
		case STATE_WALK:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_WALK");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_WALK");
			break;
		case STATE_RUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_RUN");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_RUN");
			break;
		case STATE_PRONE:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_PRONE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_PRONE");
			break;
		case STATE_KNIFE:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_KNIFE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_KNIFE");
			break;
		case STATE_GUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_PISTOL");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_PISTOL");
			break;
		case STATE_CARRYBODY:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_CARRYBODY");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_CARRYBODY");
			break;
		case STATE_CARRY:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_CARRY");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_CARRY");
			break;
		case STATE_LADDER:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_LADDER");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_LADDER");
			break;
		case STATE_LADDEREND:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_LADDEREND");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_LADDEREND");
			break;
		case STATE_DEAD:
			m_bmpDC = BMPMGR->GetBmpDC(L"GB_DEAD1");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"GB_DEAD1");
			break;
		default:
			break;
		}

		if(1 < m_BmpInfo.FrameX){
			switch(m_eState){
			case STATE_WALK:
			case STATE_RUN:
			case STATE_PRONE:
			case STATE_CARRYBODY:
			case STATE_CARRY:
				m_iFrameX = m_iFrameX < (m_BmpInfo.FrameX * IMAGE_SET_TIMING) - 1 ? m_iFrameX + 1 : 0;
				break;
			case STATE_KNIFE:
				if(m_iFrameX < (m_BmpInfo.FrameX * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else{
					m_eState = STATE_STAND;
					m_iFrameX = 0;
					SNDMGR->PlaySound(L"EFFECT_KNIFE.wav", SNDMGR->EFFECT);
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
			case STATE_DEAD:
				if(m_iFrameX < ((m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else
					m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1;
				break;
			case STATE_LADDER:
				if(!m_bIsLadderEnd){
					
					if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING){
						m_eState = STATE_LADDEREND;
						m_iFrameX = 0;
					} else
						++m_iFrameX;
				} else{
					if(m_iFrameX <= 0){
						m_eState = STATE_STAND;
						POINT srcPt = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };
						POINT destPt = { (LONG)m_tInfo.fX + 20, (LONG)m_tInfo.fY - 50 };
						TILEMGR->PathFind(m_DestPtList, srcPt, destPt);
					} else{
						--m_iFrameX;
					}
				}
				break;
			case STATE_LADDEREND:
				if(!m_bIsLadderEnd){
					
					if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING -1){
						m_eAngle = ANGLE_LDOWN;
						m_bIsLadderEnd = true;
					}else
						++m_iFrameX;
				} else{
					if(m_iFrameX <= 0){
						m_eState = STATE_LADDER;
						OBJMGR->GetList(OBJ_MAPOBJ).front()->SetVisible(true);
						m_iFrameX = BMPMGR->GetBmpInfo(L"GB_LADDER").FrameX * IMAGE_SET_TIMING -1;
					}else
						--m_iFrameX;
				}
			default:
				break;
			}
		}

		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, m_BmpInfo.cx, m_BmpInfo.cy,
			m_bmpDC, m_BmpInfo.cx * (m_iFrameX / IMAGE_SET_TIMING), m_BmpInfo.cy * int(m_eAngle), m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
	
		if(m_bFocus)
			GdiTransparentBlt(_hdc, LONG(m_tInfo.fX - SCRLMGR->m_fScrollX)-12, LONG(m_tInfo.fY - SCRLMGR->m_fScrollY) - 7, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cx, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cy,
				BMPMGR->GetBmpDC(L"CURSOR_FOCUS"), 0, 0, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cx, BMPMGR->GetBmpInfo(L"CURSOR_FOCUS").cy, m_BmpInfo.TransColor);
	}
}