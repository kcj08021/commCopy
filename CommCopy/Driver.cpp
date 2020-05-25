#include "stdafx.h"
#include "Driver.h"
#include "RubberBoat.h"


CDriver::CDriver(){

}

CDriver::~CDriver(){
	Release();
}

void CDriver::Release(){
	for(POINT* elem : m_DestPtList)
		SafeDelete(elem);
	m_DestPtList.clear();
}

void CDriver::Initialize(){
	BMPMGR->AddBMP(L"DR_WALK", PATH_DR_WALK);
	BMPMGR->SetBmpInfo(L"DR_WALK", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"DR_RUN", PATH_DR_RUN);
	BMPMGR->SetBmpInfo(L"DR_RUN", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"DR_PRONE", PATH_DR_PRONE);
	BMPMGR->SetBmpInfo(L"DR_PRONE", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"DR_SMG", PATH_DR_SMG);
	BMPMGR->SetBmpInfo(L"DR_SMG", 5, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"DR_STAND", PATH_DR_STAND);
	BMPMGR->SetBmpInfo(L"DR_STAND", 1, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"DR_DEAD1", PATH_DR_DEAD1);
	BMPMGR->SetBmpInfo(L"DR_DEAD1", 5, 1, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"DR_STAND");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_STAND");


	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fSpeed = 1.5f;
	m_tInfo.fAngle = -(PI / 4.f);
	m_tInfo.iHp = 5;

	m_eUnitType = UNIT_DRIVER;

	CGameObject::UpdateRect();
}

int CDriver::Update(){
	float fSpeed = 0.f;
	CGameObject* pObj = nullptr;
	RECT rc = {};

	CAlliedUnit::ConfigState(fSpeed);



	if(m_tInfo.bIsDead){
		m_bFocus = false;
		m_eState = STATE_DEAD;
		m_eAngle = ANGLE_TYPE(0);
	} else{
		if(m_tInfo.iHp <= 0){
			m_tInfo.bIsDead = true;
			SNDMGR->PlaySound(L"GB_DIED.wav", SNDMGR->EFFECT);
			return 0;
		}

		switch(m_eSkillType){
		case SKILL_GUN:
			m_eState = STATE_GUN;
			break;
		case SKILL_VEHICLE:
			pObj = OBJMGR->GetList(OBJ_VEHICLE).front();
			if(IntersectRect(&rc, &m_tRECT, &pObj->GetRect())){
				m_eState = STATE_VEHICLE;
				for(POINT* elem : m_DestPtList)
					SafeDelete(elem);
				m_DestPtList.clear();
				m_eSkillType = SKILL_NULL;

				dynamic_cast<CRubberBoat*>(pObj)->SetUnit(UNIT_DRIVER, this);
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
		case STATE_DEAD:
			break;
		default:
			break;
		}
	}

	CGameObject::UpdateRect();

	return 0;
}

void CDriver::Render(HDC _hdc){
	if(m_bIsVisible){
		switch(m_eState){
		case STATE_STAND:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_STAND");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_STAND");
			break;
		case STATE_WALK:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_WALK");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_WALK");
			break;
		case STATE_RUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_RUN");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_RUN");
			break;
		case STATE_PRONE:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_PRONE");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_PRONE");
			break;
		case STATE_GUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_SMG");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_SMG");
			break;
		case STATE_DEAD:
			m_bmpDC = BMPMGR->GetBmpDC(L"DR_DEAD1");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"DR_DEAD1");
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