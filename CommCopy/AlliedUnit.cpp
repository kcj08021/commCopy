#include "stdafx.h"
#include "AlliedUnit.h"


CAlliedUnit::CAlliedUnit(): m_pTargetObj(nullptr), m_bFocus(false), m_bIsShot(false), m_fDist(0.f), m_eSkillType(SKILL_NULL),m_eUnitType(UNIT_END){
	INIT_ARRAY(UnitSound);
}

CAlliedUnit::~CAlliedUnit(){

}

void CAlliedUnit::CalculateDist(){
	int x = int(m_tInfo.fX);
	int y = int(m_tInfo.fY);

	m_fDist = sqrtf(float(SQUERE(x - m_DestPtList.front()->x) + SQUERE(y - m_DestPtList.front()->y)));
}

float CAlliedUnit::CalculateDist(POINT& _pt){
	float x = m_tInfo.fX - SCRLMGR->m_fScrollX;
	float y = m_tInfo.fY - SCRLMGR->m_fScrollY;

	float fDist = sqrtf(float(SQUERE(x - float(_pt.x)) + SQUERE(y - float(_pt.y))));

	return fDist;
}




void CAlliedUnit::CalculateAngle(){
	m_tInfo.fAngle = acosf(float((m_DestPtList.front()->x - int(m_tInfo.fX)) / m_fDist));

	if(isnan(m_tInfo.fAngle) != 0)
		m_tInfo.fAngle = -1 / 4 * PI;

	if(m_DestPtList.front()->y > m_tInfo.fY)
		m_tInfo.fAngle *= -1.f;

	CGameObject::UpdateAngleState();
}

void CAlliedUnit::CalculateAngle(POINT& _pt, float _fDist){
	m_tInfo.fAngle = acosf(float((_pt.x - int(m_tInfo.fX - SCRLMGR->m_fScrollX)) / _fDist));

	if(isnan(m_tInfo.fAngle) != 0)
		m_tInfo.fAngle = -1 / 4 * PI;

	if(_pt.y > m_tInfo.fY - SCRLMGR->m_fScrollY)
		m_tInfo.fAngle *= -1.f;

	UpdateAngleState();
}

void CAlliedUnit::SetDest(POINT& _pt){
	POINT tDestPoint = _pt;
	tDestPoint.x += int(SCRLMGR->m_fScrollX);
	tDestPoint.y += int(SCRLMGR->m_fScrollY);

	POINT UnitPos = { int(m_tInfo.fX),int(m_tInfo.fY) };


	switch(m_eState){
	case STATE_DIVE:
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

		for(POINT* elem : m_DestPtList)
			SafeDelete(elem);
		m_DestPtList.clear();

		TILEMGR->PathFindWater(m_DestPtList, UnitPos, tDestPoint);
		break;
	case STATE_VEHICLE:
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

		for(POINT* elem : m_DestPtList)
			SafeDelete(elem);
		m_DestPtList.clear();

		if(TILEMGR->PathFindWater(m_DestPtList, UnitPos, tDestPoint)){
			SoundMove();
		} else{
			SoundRefuse();
		}
		break;
	default:
		if(TILEMGR->GetTile(tDestPoint)->dwTileColor != TILEMGR->GetTile(UnitPos)->dwTileColor)
			if(TILEMGR->GetTile(tDestPoint)->eTileType != TILE_WATER){
				if(TILE_WATER == TILEMGR->GetTile(UnitPos)->eTileType){
					switch(TILEMGR->GetTile(tDestPoint)->eTileType){
					case TILE_OBJ:
					case TILE_WALL:
					case TILE_DWATER:
						SoundRefuse();
						return;
					default:
						break;
					}
				} else if(m_eSkillType == SKILL_LADDER && TILEMGR->GetTile(tDestPoint)->eTileType == TILE_WALL){
					SoundMove();
				} else{
					SoundRefuse();
					return;
				}
			}

		for(POINT* elem : m_DestPtList)
			SafeDelete(elem);
		m_DestPtList.clear();

		if(TILEMGR->PathFind(m_DestPtList, UnitPos, tDestPoint)){
			SoundMove();
		} else{
			SoundRefuse();
		}
		break;
	}
}


void CAlliedUnit::SetFocus(bool _bool){
	m_bFocus = _bool;
}

void CAlliedUnit::SetTarget(CGameObject* _pObj){
	m_pTargetObj = _pObj;

	if(nullptr == m_pTargetObj)
		return;

	POINT pt = { int(m_pTargetObj->GetInfo().fX - SCRLMGR->m_fScrollX), int(m_pTargetObj->GetInfo().fY - SCRLMGR->m_fScrollY) };

	SetDest(pt);
}

bool CAlliedUnit::SetShotPoint(POINT& _pt){
	float fDist = CAlliedUnit::CalculateDist(_pt);

	CAlliedUnit::CalculateAngle(_pt, fDist);

	CGameObject::UpdateAngleState();

	if(fDist < 200.f){
		m_bIsShot = true;
	}
	else
		m_bIsShot = false;

	return m_bIsShot;
}

void CAlliedUnit::SoundRefuse(){
	switch(UnitSound[SOUND_REFUSE]){
	case 0:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_REFUSE1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_REFUSE1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_REFUSE1.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_REFUSE];
		break;
	case 1:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_REFUSE2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_REFUSE2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_REFUSE2.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_REFUSE];
		break;
	case 2:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_REFUSE3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_REFUSE3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_REFUSE3.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
	default:
		UnitSound[SOUND_REFUSE] = 0;
		break;
	}
}

void CAlliedUnit::SoundMove(){
	switch(UnitSound[SOUND_MOVE]){
	case 0:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_MOVE1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_MOVE1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_MOVE1.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_MOVE];
		break;
	case 1:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_MOVE2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_MOVE2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_MOVE2.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_MOVE];
		break;
	case 2:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_MOVE3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_MOVE3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_MOVE3.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_MOVE];
		break;
	case 3:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_MOVE4.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_MOVE4.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_MOVE4.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
	default:
		UnitSound[SOUND_MOVE] = 0;
		break;
	}
}

void CAlliedUnit::SoundAction(){
	switch(UnitSound[SOUND_ACTION]){
	case 0:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ACTION1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ACTION1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ACTION1.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_ACTION];
		break;
	case 1:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ACTION2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ACTION2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ACTION2.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_ACTION];
		break;
	case 2:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ACTION3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ACTION3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ACTION3.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
	default:
		UnitSound[SOUND_ACTION] = 0;
		break;
	}
}

void CAlliedUnit::SoundAttacked(){
	switch(UnitSound[SOUND_ATTACK]){
	case 0:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ATTACK1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ATTACK1.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ATTACK1.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_ATTACK];
		break;
	case 1:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ATTACK2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ATTACK2.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ATTACK2.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
		++UnitSound[SOUND_ATTACK];
		break;
	case 2:
		switch(m_eUnitType){
		case UNIT_GREENBERETS:
			SNDMGR->PlaySound(L"GB_ATTACK3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_MARINE:
			SNDMGR->PlaySound(L"MR_ATTACK3.wav", SNDMGR->PLAYER);
			break;
		case UNIT_DRIVER:
			SNDMGR->PlaySound(L"DR_ATTACK3.wav", SNDMGR->PLAYER);
			break;
		default:
			break;
		}
	default:
		UnitSound[SOUND_ATTACK] = 0;
		break;
	}
}
