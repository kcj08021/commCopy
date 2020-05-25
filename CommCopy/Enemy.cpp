#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy(): m_iRallyIndex(0), m_currTime(0), m_oldTime(0), m_DeadSelect(false), m_bIsCheckFire(false), m_bDetectUnit(false), m_bIsSight(false), m_DetectedUnit(nullptr){
	INIT_STRUCT(m_tBackupInfo);
}

CEnemy::~CEnemy(){
	Release();
}

void CEnemy::SetTarget(POINT& _pt){
	m_bIsCheckFire = true;

	POINT pt = { int(m_tInfo.fX), int(m_tInfo.fY) };

	for(POINT* elem : m_PathPt)
		SafeDelete(elem);
	m_PathPt.clear();

	TILEMGR->PathFind(m_PathPt, pt, _pt);

	m_eState = STATE_RUN;

	if(m_RallyPt.size() == 0)
		if(m_tBackupInfo.fX == 0.f && m_tBackupInfo.fY == 0.f)
			m_tBackupInfo = m_tInfo;
}

void CEnemy::Detect(){
	list<CGameObject*>* Unitlist = &OBJMGR->GetList(OBJ_ALLIED);

	for(CGameObject* elem : *Unitlist){
		if(!elem->IsDead()){
			float fDist = CGameObject::CalculateDist(elem->GetInfo().fX, elem->GetInfo().fY);
			if(fDist < 400.f){
				POINT SrcPt = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };
				POINT DestPt = { (LONG)elem->GetInfo().fX, (LONG)elem->GetInfo().fY };

				float fAngle = DEGREE(GetAngleToPoint(SrcPt, DestPt));

				float fUpAngle = (DEGREE(m_tInfo.fAngle) + 30.f) > 180.f ? -180.f + ((DEGREE(m_tInfo.fAngle) + 30.f) - 180.f) : DEGREE(m_tInfo.fAngle) + 30.f;
				float fDownAngle = (DEGREE(m_tInfo.fAngle) - 30.f) < -180.f ? 180.f - ((DEGREE(m_tInfo.fAngle) - 30.f) + 180.f) : DEGREE(m_tInfo.fAngle) - 30.f;

				if((fAngle <= fUpAngle) && (fAngle >= fDownAngle)){
					//브레젠험을 이용한 장애물 판별

					int iDeltaX = DestPt.x - SrcPt.x;
					int iDeltaY = DestPt.y - SrcPt.y;

					int iDF1 = 2 * iDeltaY;
					int iDF2 = 2 * (iDeltaY - iDeltaX);

					int iF = 2 * (iDeltaY - iDeltaX);

					int temp = 0;

					if(iDeltaX < 0){
						iDeltaX *= -1;
						temp = DestPt.x;
						DestPt.x = SrcPt.x;
						SrcPt.x = temp;
					}

					if(iDeltaY < 0){
						iDeltaY *= -1;
						temp = DestPt.y;
						DestPt.y = SrcPt.y;
						SrcPt.y = temp;
					}

					TILEINFO* tile = nullptr;

					int j = 0;
					for(int i = 0; i < iDeltaX; i += 10){
						tile = TILEMGR->GetTile(float(SrcPt.x + i), float(SrcPt.y + j));
						if(iF < 0)
							iF += iDF1;
						else{
							j += 10;
							iF += iDF2;
						}

						if(nullptr != tile && tile->eTileType != TILE_NULL){
							if(m_eState == STATE_STAND || m_eState == STATE_WALK)
								m_eState = STATE_STAND;
							else
								m_eState = STATE_RUN;
							m_bDetectUnit = false;
							return;
						}
					}

					if(fDist < 300.f){
						if(m_RallyPt.size() == 0)
							if(m_tBackupInfo.fX == 0.f && m_tBackupInfo.fY == 0.f)
								m_tBackupInfo = m_tInfo;
						m_eState = STATE_GUN;
						m_DetectedUnit = elem;
						m_bDetectUnit = true;
						return;
					} else if(fDist >= 300.f && dynamic_cast<CAlliedUnit*>(elem)->GetState() != STATE_PRONE){
						if(m_RallyPt.size() == 0)
							if(m_tBackupInfo.fX == 0.f && m_tBackupInfo.fY == 0.f)
								m_tBackupInfo = m_tInfo;
						m_eState = STATE_GUN;
						m_DetectedUnit = elem;
						m_bDetectUnit = true;
						return;
					}
				}

			}
		}
	}


	if(m_bDetectUnit == true){
		POINT SrcPt = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };
		POINT DestPt = { (LONG)m_DetectedUnit->GetInfo().fX, (LONG)m_DetectedUnit->GetInfo().fY };
		m_eState = STATE_RUN;
		for(POINT* elem : m_PathPt)
			SafeDelete(elem);
		m_PathPt.clear();

		TILEMGR->PathFind(m_PathPt, SrcPt, DestPt);
	}

	m_bDetectUnit = false;
	m_DetectedUnit = nullptr;
}

void CEnemy::Release(){
	for(POINT* elem : m_RallyPt)
		SafeDelete(elem);
	m_RallyPt.clear();

	for(POINT* elem : m_PathPt)
		SafeDelete(elem);
	m_PathPt.clear();
}

void CEnemy::Initialize(){
	BMPMGR->AddBMP(L"ENEMY_WALK", PATH_ENEMY_WALK);
	BMPMGR->SetBmpInfo(L"ENEMY_WALK", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"ENEMY_RUN", PATH_ENEMY_RUN);
	BMPMGR->SetBmpInfo(L"ENEMY_RUN", 8, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"ENEMY_SHOT", PATH_ENEMY_SHOT);
	BMPMGR->SetBmpInfo(L"ENEMY_SHOT", 4, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"ENEMY_STAND", PATH_ENEMY_STAND);
	BMPMGR->SetBmpInfo(L"ENEMY_STAND", 1, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"ENEMY_DEAD1", PATH_ENEMY_DEAD1);
	BMPMGR->SetBmpInfo(L"ENEMY_DEAD1", 6, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"ENEMY_DEAD2", PATH_ENEMY_DEAD2);
	BMPMGR->SetBmpInfo(L"ENEMY_DEAD2", 2, 1, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"ENEMY_RANGE", PATH_ENEMY_RANGE);
	BMPMGR->SetBmpInfo(L"ENEMY_RANGE", 1, 8, RGB(255, 0, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_STAND");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_STAND");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);

	m_tInfo.fSpeed = 1.0f;
	m_tInfo.fAngle = -(PI / 4.f);
	m_tInfo.iHp = 3;
	m_bIsVisible = true;

	m_DeadSelect = bool(rand() & 1);

	CGameObject::UpdateRect();
}

int CEnemy::Update(){
	float fSpeed = 0.f;
	POINT pt = { int(m_tInfo.fX),int(m_tInfo.fY) };
	m_currTime = time(nullptr);
	Detect();
	if(m_tInfo.iHp <= 0){
		if(!m_tInfo.bIsDead)
			m_iFrameX = 0;
		m_tInfo.bIsDead = true;
	}
	if(m_tInfo.bIsDead){
		m_eState = STATE_DEAD;
		m_eAngle = ANGLE_TYPE(0);
	} else{
		if(m_bDetectUnit){
			if(nullptr == m_DetectedUnit)
				return 0;

			if(dynamic_cast<CAlliedUnit*>(m_DetectedUnit)->GetState() != STATE_STAND && dynamic_cast<CAlliedUnit*>(m_DetectedUnit)->GetState() != STATE_PRONE){
				if(m_currTime - m_oldTime > 1 && m_bIsShot == false){
					m_bIsShot = true;
					m_oldTime = time(nullptr);
					m_DetectedUnit->SetDamage(1);
				}
			}
		} else{
			if(m_RallyPt.size() > 1){
				if(0 == m_PathPt.size() && ((m_currTime - m_oldTime) >= 5)){
					if(m_bIsCheckFire){
						m_bIsCheckFire = false;
					} else{
						m_iRallyIndex = (m_iRallyIndex + 1) % m_RallyPt.size();
					}
					TILEMGR->PathFind(m_PathPt, pt, *m_RallyPt[m_iRallyIndex]);
					m_oldTime = 0;
				} else{
					if(m_PathPt.size() > 0){
						if(STATE_STAND == m_eState)
							m_eState = STATE_WALK;

						CGameObject::ConfigState(fSpeed);

						float fDist = CGameObject::CalculateDist(*m_PathPt.front());

						if(fDist > fSpeed){
							CGameObject::CalculateAngle(*m_PathPt.front(), fDist);
							m_tInfo.fX += fSpeed * cos(m_tInfo.fAngle);
							m_tInfo.fY -= fSpeed * sin(m_tInfo.fAngle);
						} else{
							m_tInfo.fX = float(m_PathPt.front()->x);
							m_tInfo.fY = float(m_PathPt.front()->y);

							SafeDelete(m_PathPt.front());
							m_PathPt.pop_front();

							if(0 == m_PathPt.size()){
								m_oldTime = time(nullptr);
							}
						}
					} else{
						m_eState = STATE_STAND;
						m_iFrameX = 0;
					}
				}
			} else{
				if(m_bIsCheckFire){
					if(m_PathPt.size() > 0){
						if(STATE_STAND == m_eState)
							m_eState = STATE_WALK;

						CGameObject::ConfigState(fSpeed);

						float fDist = CGameObject::CalculateDist(*m_PathPt.front());

						if(fDist > fSpeed){
							CGameObject::CalculateAngle(*m_PathPt.front(), fDist);
							m_tInfo.fX += fSpeed * cos(m_tInfo.fAngle);
							m_tInfo.fY -= fSpeed * sin(m_tInfo.fAngle);
						} else{
							m_tInfo.fX = float(m_PathPt.front()->x);
							m_tInfo.fY = float(m_PathPt.front()->y);

							SafeDelete(m_PathPt.front());
							m_PathPt.pop_front();

							if(0 == m_PathPt.size()){
								m_oldTime = time(nullptr);
							}
						}
					} else{
						m_eState = STATE_STAND;
						m_iFrameX = 0;
					}

					if(m_currTime - m_oldTime >= 5 && m_oldTime != 0){
						POINT DestPt = { (LONG)m_tBackupInfo.fX, (LONG)m_tBackupInfo.fY };
						POINT currPt = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };

						TILEMGR->PathFind(m_PathPt, currPt, DestPt);
						m_bIsCheckFire = false;

						m_oldTime = 0;
					}
				} else{
					if(m_PathPt.size() > 0){
						if(STATE_STAND == m_eState)
							m_eState = STATE_WALK;

						CGameObject::ConfigState(fSpeed);

						float fDist = CGameObject::CalculateDist(*m_PathPt.front());

						if(fDist > fSpeed){
							CGameObject::CalculateAngle(*m_PathPt.front(), fDist);
							m_tInfo.fX += fSpeed * cos(m_tInfo.fAngle);
							m_tInfo.fY -= fSpeed * sin(m_tInfo.fAngle);
						} else{
							m_tInfo.fX = float(m_PathPt.front()->x);
							m_tInfo.fY = float(m_PathPt.front()->y);

							SafeDelete(m_PathPt.front());
							m_PathPt.pop_front();

							if(0 == m_PathPt.size()){
								m_oldTime = time(nullptr);
							}
						}
					} else{
						m_eState = STATE_STAND;
						m_iFrameX = 0;
						if(m_tBackupInfo.fX != 0.f && m_tBackupInfo.fY != 0.f){
							if(m_tBackupInfo.fX != m_tInfo.fX && m_tBackupInfo.fY != m_tInfo.fY){
								if(m_currTime - m_oldTime >= 5 && m_oldTime != 0){
									POINT DestPt = { (LONG)m_tBackupInfo.fX, (LONG)m_tBackupInfo.fY };
									POINT currPt = { (LONG)m_tInfo.fX, (LONG)m_tInfo.fY };

									TILEMGR->PathFind(m_PathPt, currPt, DestPt);
								}
							} else{
								m_tInfo = m_tBackupInfo;
								memset(&m_tBackupInfo, 0, sizeof(m_tBackupInfo));
								CGameObject::UpdateAngleState();
							}
						}
					}
				}
			}
		}
	}

	CGameObject::UpdateRect();
	return 0;
}

void CEnemy::Render(HDC _hdc){
	if(m_bIsVisible){
		switch(m_eState){
		case STATE_STAND:
			m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_STAND");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_STAND");
			break;
		case STATE_WALK:
			m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_WALK");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_WALK");
			break;
		case STATE_RUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_RUN");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_RUN");
			break;
		case STATE_GUN:
			m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_SHOT");
			m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_SHOT");
			break;
		case STATE_DEAD:
			if(m_DeadSelect){
				m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_DEAD2");
				m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_DEAD2");
			} else{
				m_bmpDC = BMPMGR->GetBmpDC(L"ENEMY_DEAD1");
				m_BmpInfo = BMPMGR->GetBmpInfo(L"ENEMY_DEAD1");
			}
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
				if(m_iFrameX == 0)
					SNDMGR->PlaySound(L"ENEMY_DETECT.wav", SNDMGR->EFFECT);

				if(m_iFrameX < ((m_BmpInfo.FrameX - 3) * IMAGE_SET_TIMING) - 1)
					++m_iFrameX;
				else
					if(m_bIsShot){
						++m_iFrameX;
						if(m_iFrameX >= (m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING - 1){
							SNDMGR->PlaySound(L"EFFECT_SMG.wav", SNDMGR->EFFECT);
							m_bIsShot = false;
						}
					} else
						m_iFrameX = (m_BmpInfo.FrameX - 2) * IMAGE_SET_TIMING - 1;
					break;
			case STATE_DEAD:
				if(m_iFrameX < ((m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING) - 1){
					++m_iFrameX;
					if(m_iFrameX >= ((m_BmpInfo.FrameX - 1) * IMAGE_SET_TIMING) - 1){
						POINT pt = { LONG(m_tInfo.fX - SCRLMGR->m_fScrollX), LONG(m_tInfo.fY - SCRLMGR->m_fScrollY - m_BmpInfo.cy / 2.f) };
						EFCTMGR->EndlessEffect(EFFECT_BLOOD, pt);
					}
				} else{
					m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1;
				}
				break;
			default:
				break;
			}
		}

		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, m_BmpInfo.cx, m_BmpInfo.cy,
			m_bmpDC, m_BmpInfo.cx * (m_iFrameX / IMAGE_SET_TIMING), m_BmpInfo.cy * int(m_eAngle), m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);

		if(m_bIsSight && !m_tInfo.bIsDead)
			GdiTransparentBlt(_hdc, (LONG)m_tInfo.fX - 400 - (LONG)SCRLMGR->m_fScrollX, (LONG)m_tInfo.fY - 400 - (LONG)SCRLMGR->m_fScrollY, 800, 800,
				BMPMGR->GetBmpDC(L"ENEMY_RANGE"), 0, 800 * int(m_eAngle), 800, 800, RGB(255, 0, 255));
	}
}