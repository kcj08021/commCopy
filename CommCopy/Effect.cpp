#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect(): m_bIsLoop(false), m_bIsEnded(false), m_etype(EFFECT_PISTOL){
}

CEffect::~CEffect(){
	Release();
}

void CEffect::SetEffect(EFFECT_TYPE _enum){
	m_etype = _enum;
	switch(_enum){
	case EFFECT_PISTOL:
		m_bmpDC = BMPMGR->GetBmpDC(L"EFFECT_PISTOL");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"EFFECT_PISTOL");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case EFFECT_EXPLOSION:
		m_bmpDC = BMPMGR->GetBmpDC(L"EFFECT_EXPLOSION");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"EFFECT_EXPLOSION");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case EFFECT_FIRE:
		m_bmpDC = BMPMGR->GetBmpDC(L"EFFECT_FIRE");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"EFFECT_FIRE");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case EFFECT_BLOOD:
		m_bmpDC = BMPMGR->GetBmpDC(L"EFFECT_BLOOD");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"EFFECT_BLOOD");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	case EFFECT_MOVE:
		m_bmpDC = BMPMGR->GetBmpDC(L"EFFECT_MOVE");
		m_BmpInfo = BMPMGR->GetBmpInfo(L"EFFECT_MOVE");
		m_tInfo.fCX = float(m_BmpInfo.cx);
		m_tInfo.fCY = float(m_BmpInfo.cy);
		break;
	default:
		break;
	}

	CGameObject::UpdateRect();
}

void CEffect::Release(){
}

void CEffect::Initialize(){
	BMPMGR->AddBMP(L"EFFECT_PISTOL", PATH_EFFECT_PISTOL);
	BMPMGR->SetBmpInfo(L"EFFECT_PISTOL", 4, 1, RGB(255, 0, 255));
	BMPMGR->AddBMP(L"EFFECT_FIRE", PATH_EFFECT_FIRE);
	BMPMGR->SetBmpInfo(L"EFFECT_FIRE", 14, 1, RGB(255, 0, 255));
	BMPMGR->AddBMP(L"EFFECT_EXPLOSION", PATH_EFFECT_EXPLOSION);
	BMPMGR->SetBmpInfo(L"EFFECT_EXPLOSION", 11, 1, RGB(255, 0, 255));
	BMPMGR->AddBMP(L"EFFECT_BLOOD", PATH_EFFECT_BLOOD);
	BMPMGR->SetBmpInfo(L"EFFECT_BLOOD", 3, 1, RGB(255, 0, 255));
	BMPMGR->AddBMP(L"EFFECT_MOVE", PATH_EFFECT_MOVE);
	BMPMGR->SetBmpInfo(L"EFFECT_MOVE", 6, 1, RGB(255, 255, 255));
	m_tInfo.bIsDead = false;
	m_bIsVisible = true;
	m_bIsLoop = false;

	CGameObject::UpdateRect();
}

int CEffect::Update(){

	if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING){
		if(m_bIsLoop){
			m_iFrameX = 0;
		} else{
			if(m_bIsEnded){
				m_tInfo.bIsDead = true;
				m_bIsVisible = false;
			} else{
				m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING;
			}
		}
	} else
		++m_iFrameX;

	CGameObject::UpdateRect();
	return 0;
}

void CEffect::Render(HDC _hdc){
	if(m_iFrameX == 1)
		switch(m_etype){
		case EFFECT_PISTOL:
			SNDMGR->PlaySound(L"EFFECT_PISTOL.wav", SNDMGR->EFFECT);
			break;
		case EFFECT_EXPLOSION:
			SNDMGR->PlaySound(L"EFFECT_EXPLOSION.wav", SNDMGR->EFFECT);
			break;
		default:
			break;
		}

	if(m_bIsVisible){
		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			m_bmpDC, m_BmpInfo.cx * ((m_iFrameX / IMAGE_SET_TIMING) - 1), 0, m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);
	}
}
