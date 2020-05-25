#include "stdafx.h"
#include "RubberBoat.h"

CRubberBoat::CRubberBoat(): m_currTime(0), m_oldTime(0), m_bMarineFrameX(false), m_bFocus(false), m_bFoldingFlag(false), m_fDist(0.f){
	m_Units[UNIT_GREENBERETS] = nullptr;
	m_Units[UNIT_MARINE] = nullptr;
	m_Units[UNIT_DRIVER] = nullptr;
}

CRubberBoat::~CRubberBoat(){
	Release();
}

void CRubberBoat::CalculateDist(){
	int x = int(m_tInfo.fX);
	int y = int(m_tInfo.fY);

	m_fDist = sqrtf(float(SQUERE(x - m_PathPt.front()->x) + SQUERE(y - m_PathPt.front()->y)));
}


void CRubberBoat::CalculateAngle(){
	m_tInfo.fAngle = acosf(float(m_PathPt.front()->x - int(m_tInfo.fX)) / m_fDist);

	if(isnan(m_tInfo.fAngle) != 0)
		m_tInfo.fAngle = -1 / 4 * PI;

	if(m_PathPt.front()->y > m_tInfo.fY)
		m_tInfo.fAngle *= -1.f;

	CGameObject::UpdateAngleState();
}

void CRubberBoat::SetDest(POINT _pt){

	if(m_bIsVisible){
		POINT tDestPoint = _pt;
		tDestPoint.x += int(SCRLMGR->m_fScrollX);
		tDestPoint.y += int(SCRLMGR->m_fScrollY);

		POINT UnitPos = { int(m_tInfo.fX),int(m_tInfo.fY) };

		if(TILEMGR->GetTile(tDestPoint)->dwTileColor != TILEMGR->GetTile(UnitPos)->dwTileColor)
			if(TILEMGR->GetTile(tDestPoint)->eTileType != TILE_WATER)
				if(TILE_WATER == TILEMGR->GetTile(UnitPos)->eTileType){
					switch(TILEMGR->GetTile(tDestPoint)->eTileType){
					case TILE_OBJ:
					case TILE_WALL:
					case TILE_NULL:
						return;
					default:
						break;
					}
				} else{
					return;
				}

		for(POINT* elem : m_PathPt)
			SafeDelete(elem);
		m_PathPt.clear();

		if(TILEMGR->PathFindWater(m_PathPt, UnitPos, tDestPoint)){
			if(m_Units[UNIT_MARINE] != nullptr){
				dynamic_cast<CMarine*>(m_Units[UNIT_MARINE])->SoundMove();
			}
		} else{
			if(m_Units[UNIT_MARINE] != nullptr){
				dynamic_cast<CMarine*>(m_Units[UNIT_MARINE])->SoundRefuse();
			}
		}
	}
}

bool CRubberBoat::FoldingBoat(){
	for(CGameObject* elem: m_Units)
		if(elem != nullptr)
			return false;

	m_bFoldingFlag = true;

	if(m_iFrameX <= 0){
		return true;
	} else{
		return false;
	}
}

void CRubberBoat::OpenBoat(){
	m_bFoldingFlag = false;
}

void CRubberBoat::Release(){
	for(POINT* elem : m_PathPt)
		SafeDelete(elem);
	m_PathPt.clear();
}

void CRubberBoat::Initialize(){
	BMPMGR->AddBMP(L"RUBBERBOAT", PATH_RUBBERBOAT);
	BMPMGR->SetBmpInfo(L"RUBBERBOAT", 5, 8, RGB(255, 255, 255));

	BMPMGR->AddBMP(L"GB_BOAT", PATH_GB_BOAT);
	BMPMGR->SetBmpInfo(L"GB_BOAT", 1, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"MR_BOAT", PATH_MR_BOAT);
	BMPMGR->SetBmpInfo(L"MR_BOAT", 2, 8, RGB(255, 255, 255));
	BMPMGR->AddBMP(L"DR_BOAT", PATH_DR_BOAT);
	BMPMGR->SetBmpInfo(L"DR_BOAT", 1, 8, RGB(255, 255, 255));

	m_bmpDC = BMPMGR->GetBmpDC(L"RUBBERBOAT");
	m_BmpInfo = BMPMGR->GetBmpInfo(L"RUBBERBOAT");

	m_tInfo.fCX = float(m_BmpInfo.cx);
	m_tInfo.fCY = float(m_BmpInfo.cy);
	m_tInfo.fSpeed = 1.5f;
	m_tInfo.fAngle = RADIAN(45.f);
	m_tInfo.bIsDead = false;

	CGameObject::UpdateAngleState();

	m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING-1;
}

int CRubberBoat::Update(){
	m_currTime = time(nullptr);

	if(m_bFoldingFlag){
		if(m_iFrameX <= 0)
			m_iFrameX = 0;
		else
			--m_iFrameX;
	}
	else{
		if(m_iFrameX >= m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1)
			m_iFrameX = m_BmpInfo.FrameX * IMAGE_SET_TIMING - 1;
		else
			++m_iFrameX;
	}

	if(nullptr != m_Units[UNIT_MARINE]){
		if(m_PathPt.size() > 0){

			
			CalculateDist();
			
			if(m_fDist > m_tInfo.fSpeed){
				CalculateAngle();
				m_tInfo.fX += m_tInfo.fSpeed * cos(m_tInfo.fAngle);
				m_tInfo.fY -= m_tInfo.fSpeed * sin(m_tInfo.fAngle);
			} else{
				m_tInfo.fX = float(m_PathPt.front()->x);
				m_tInfo.fY = float(m_PathPt.front()->y);

				SafeDelete(m_PathPt.front());
				m_PathPt.pop_front();
			}
		}else
			m_oldTime = m_currTime;


		for(CGameObject* elem : m_Units)
			if(nullptr != elem)
				elem->SetPosition(m_tInfo.fX, m_tInfo.fY);
	}

	CGameObject::UpdateRect();

	return 0;
}

void CRubberBoat::Render(HDC _hdc){
	HDC UnitBmpDc;
	BMPINFO tUnitBmpInfo;
	vector<BoatStruct*> UnitSt;
	
	if(m_bIsVisible){

		for(int i = 0; i < 3; ++i){
			BoatStruct* temp = new BoatStruct;
			temp->type = UNIT_END;
			UnitSt.push_back(temp);
		}

		if(m_currTime - m_oldTime >= 1){
			m_oldTime = m_currTime;
			m_bMarineFrameX = !m_bMarineFrameX;
			if(m_PathPt.size() != 0 && m_currTime & 1)
				SNDMGR->PlaySound(L"EFFECT_BOAT.wav", SNDMGR->EFFECT);
		}
		


		GdiTransparentBlt(_hdc, m_tRECT.left, m_tRECT.top, m_BmpInfo.cx, m_BmpInfo.cy,
			m_bmpDC, m_BmpInfo.cx * (m_iFrameX / IMAGE_SET_TIMING), m_BmpInfo.cy * int(m_eAngle), m_BmpInfo.cx, m_BmpInfo.cy, m_BmpInfo.TransColor);

		if(nullptr != m_Units[UNIT_MARINE]){
			UnitSt[UNIT_MARINE]->type = UNIT_MARINE;

			switch(m_eAngle){
			case ANGLE_RIGHT:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left + 7;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top + 2;
				break;
			case ANGLE_RDOWN:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 2;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top + 2;
				break;
			case ANGLE_DOWN:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 3;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top + 4;
				break;
			case ANGLE_UP:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 3;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top - 10;
				break;
			case ANGLE_RUP:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left + 2;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top - 2;
				break;
			case ANGLE_LEFT:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 15;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top + 3;
				break;
			case ANGLE_LDOWN:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 2;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top + 2;
				break;
			case ANGLE_LUP:
				UnitSt[UNIT_MARINE]->pt.x = m_tRECT.left - 2;
				UnitSt[UNIT_MARINE]->pt.y = m_tRECT.top - 2;
				break;
			default:
				break;
			}


		}

		if(nullptr != m_Units[UNIT_GREENBERETS]){

			UnitSt[UNIT_GREENBERETS]->type = UNIT_GREENBERETS;

			switch(m_eAngle){
			case ANGLE_RIGHT:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 15;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top - 5;
				break;
			case ANGLE_RDOWN:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 30;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top + 2;
				break;
			case ANGLE_DOWN:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 28;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top;
				break;
			case ANGLE_UP:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 18;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top + 12;
				break;
			case ANGLE_RUP:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 13;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top + 4;
				break;
			case ANGLE_LEFT:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 30;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top - 3;
				break;
			case ANGLE_LDOWN:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 30;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top + 3;
				break;
			case ANGLE_LUP:
				UnitSt[UNIT_GREENBERETS]->pt.x = m_tRECT.left + 37;
				UnitSt[UNIT_GREENBERETS]->pt.y = m_tRECT.top + 5;
				break;
			default:
				break;
			}

		}

		if(nullptr != m_Units[UNIT_DRIVER]){
			UnitSt[UNIT_DRIVER]->type = UNIT_DRIVER;

			switch(m_eAngle){
			case ANGLE_RIGHT:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 12;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 10;
				break;
			case ANGLE_RDOWN:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 17;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 4;
				break;
			case ANGLE_DOWN:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 20;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top;
				break;
			case ANGLE_UP:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 30;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 17;
				break;
			case ANGLE_RUP:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 22;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 17;
				break;
			case ANGLE_LEFT:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 34;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 10;
				break;
			case ANGLE_LDOWN:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 26;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top;
				break;
			case ANGLE_LUP:
				UnitSt[UNIT_DRIVER]->pt.x = m_tRECT.left + 30;
				UnitSt[UNIT_DRIVER]->pt.y = m_tRECT.top + 15;
				break;
			default:
				break;
			}
		}

		sort(UnitSt.begin(), UnitSt.end(), BoatGreater());


		for(size_t i = 0; i < UnitSt.size(); ++i){
			switch(UnitSt[i]->type){
			case UNIT_MARINE:
				UnitBmpDc = BMPMGR->GetBmpDC(L"MR_BOAT");
				tUnitBmpInfo = BMPMGR->GetBmpInfo(L"MR_BOAT");

				GdiTransparentBlt(_hdc, UnitSt[i]->pt.x, UnitSt[i]->pt.y, tUnitBmpInfo.cx, tUnitBmpInfo.cy,
					UnitBmpDc, tUnitBmpInfo.cx * int(m_bMarineFrameX), tUnitBmpInfo.cy * int(m_eAngle), tUnitBmpInfo.cx, tUnitBmpInfo.cy, tUnitBmpInfo.TransColor);
				continue;
			case UNIT_GREENBERETS:
				UnitBmpDc = BMPMGR->GetBmpDC(L"GB_BOAT");
				tUnitBmpInfo = BMPMGR->GetBmpInfo(L"GB_BOAT");

				GdiTransparentBlt(_hdc, UnitSt[i]->pt.x, UnitSt[i]->pt.y, tUnitBmpInfo.cx, tUnitBmpInfo.cy,
					UnitBmpDc, tUnitBmpInfo.cx * 0, tUnitBmpInfo.cy * int(m_eAngle), tUnitBmpInfo.cx, tUnitBmpInfo.cy, tUnitBmpInfo.TransColor);
				continue;
			case UNIT_DRIVER:
				UnitBmpDc = BMPMGR->GetBmpDC(L"DR_BOAT");
				tUnitBmpInfo = BMPMGR->GetBmpInfo(L"DR_BOAT");

				GdiTransparentBlt(_hdc, UnitSt[i]->pt.x, UnitSt[i]->pt.y, tUnitBmpInfo.cx, tUnitBmpInfo.cy,
					UnitBmpDc, tUnitBmpInfo.cx * 0, tUnitBmpInfo.cy * int(m_eAngle), tUnitBmpInfo.cx, tUnitBmpInfo.cy, tUnitBmpInfo.TransColor);
				continue;
			default:
				continue;
			}
		}

		for(BoatStruct* elem : UnitSt)
			SafeDelete(elem);
		UnitSt.clear();
	}
}
