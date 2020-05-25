#include "stdafx.h"
#include "Mission01.h"
#include "GreenBerets.h"
#include "Driver.h"
#include "Marine.h"
#include "ControlBackground.h"
#include "Map.h"
#include "Enemy.h"
#include "RubberBoat.h"
#include "Barrel.h"
#include "Tree.h"
#include "Pole.h"
#include "Wall.h"
#include "Building.h"
#include "RadioTower.h"



CMission01::CMission01(){

}

CMission01::~CMission01(){
	Release();
}

void CMission01::Release(){
	SCRLMGR->DestroyInstance();
	TILEMGR->DestroyInstance();
	MOUSEMGR->SetMouseCursor(MOUSE_DEFAULT);
}

void CMission01::Initialize(){
	//UI
	CGameObject* pObj = CAbstractFactory<CControlBackground>::CreateObject();
	OBJMGR->AddObject(OBJ_UI, pObj);

	//맵
	pObj = CAbstractFactory<CMap>::CreateObject();
	OBJMGR->AddObject(OBJ_MAP, pObj);

	//플레이어 유닛
	pObj = CAbstractFactory<CGreenBerets>::CreateObject(1250.f,2350.f);
	UNITMGR->SetUnit(UNIT_GREENBERETS, pObj);

	pObj = CAbstractFactory<CMarine>::CreateObject(1310.f,1320.f);
	UNITMGR->SetUnit(UNIT_MARINE, pObj);

	pObj = CAbstractFactory<CDriver>::CreateObject(1430.f, 1900.f);
	UNITMGR->SetUnit(UNIT_DRIVER, pObj);

	//맵 오브젝트

	//벽
	pObj = CAbstractFactory<CWall>::CreateObject(437.f, 1847.f);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);


	//기름통
	pObj = CAbstractFactory<CBarrel>::CreateObject(1150.f, 2420.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);

	pObj = CAbstractFactory<CBarrel>::CreateObject(510.f, 240.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);

	pObj = CAbstractFactory<CBarrel>::CreateObject(560.f, 500.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);

	pObj = CAbstractFactory<CBarrel>::CreateObject(280.f, 100.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);

	pObj = CAbstractFactory<CBarrel>::CreateObject(920.f, 300.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);

	pObj = CAbstractFactory<CBarrel>::CreateObject(750.f, 80.f);
	OBJMGR->AddObject(OBJ_USEOBJ, pObj);


	//목표
	pObj = CAbstractFactory<CRadioTower>::CreateObject(295.f, 310.f);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	//고무보트
	pObj = CAbstractFactory<CRubberBoat>::CreateObject(950.f, 920.f);
	OBJMGR->AddObject(OBJ_VEHICLE, pObj);




	//나무
	pObj = CAbstractFactory<CTree>::CreateObject(130.f, 330.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(45.f, 870.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(130.f, 800.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(295.f, 890.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(650.f, 140.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(470.f, 1110.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(30.f, 1265.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(160.f, 1385.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1235.f, 770.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(850.f, 1090.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1350.f, 1305.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1400.f, 2015.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(880.f, 2380.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(515.f, 2435.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(190.f, 2265.f);
	dynamic_cast<CTree*>(pObj)->SetTree(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);


	pObj = CAbstractFactory<CTree>::CreateObject(890.f, 210.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1445.f, 780.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(940.f, 1190.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1430.f, 1070.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1190.f, 1330.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(845.f, 1660.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);


	pObj = CAbstractFactory<CTree>::CreateObject(995.f, 1970.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(710.f, 1980.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(185.f, 1830.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(65.f, 1990.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(777.f, 2230.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1175.f, 2350.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CTree>::CreateObject(1380.f, 2430.f);
	dynamic_cast<CTree*>(pObj)->SetTree(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);



	//전봇대
	pObj = CAbstractFactory<CPole>::CreateObject(290.f, 1970.f);
	dynamic_cast<CPole*>(pObj)->SetSelect(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CPole>::CreateObject(1242.f, 2125.f);
	dynamic_cast<CPole*>(pObj)->SetSelect(true);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CPole>::CreateObject(820.f, 1900.f);
	dynamic_cast<CPole*>(pObj)->SetSelect(false);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);


	//건물
	pObj = CAbstractFactory<CBuilding>::CreateObject(280.f, 670.f);
	dynamic_cast<CBuilding*>(pObj)->SetBuilding(BUILDING_ONE);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CBuilding>::CreateObject(710.f, 490.f);
	dynamic_cast<CBuilding*>(pObj)->SetBuilding(BUILDING_TWO);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);

	pObj = CAbstractFactory<CBuilding>::CreateObject(680.f, 1778.f);
	dynamic_cast<CBuilding*>(pObj)->SetBuilding(BUILDING_THREE);
	OBJMGR->AddObject(OBJ_MAPOBJ, pObj);




	//적 유닛
	//고정
	pObj = CAbstractFactory<CEnemy>::CreateObject(90.f, 440.f);
	pObj->SetAngle(RADIAN(0.f));
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(930.f, 370.f);
	pObj->SetAngle(RADIAN(-45.f));
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(620.f,1810.f);
	pObj->SetAngle(RADIAN(-45.f));
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(1040.f, 900.f);
	pObj->SetAngle(RADIAN(135.f));
	OBJMGR->AddObject(OBJ_ENEMY, pObj);


	////이동
	pObj = CAbstractFactory<CEnemy>::CreateObject(300.f, 130.f);
	pObj->SetAngle(RADIAN(180.f));
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(300, 170);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(530, 480);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(160, 390);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(320.f, 170.f);
	pObj->SetAngle(RADIAN(180.f));
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(320, 170);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(560, 480);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(180, 360);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(450.f, 2300.f);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(180, 1950);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(450, 2300);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(1020.f, 950.f);
	pObj->SetAngle(RADIAN(180.f));
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1270, 1130);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1020, 950);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(770.f, 1870.f);
	pObj->SetAngle(RADIAN(180.f));
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(770, 1870);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1130, 2050);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(1060.f, 900.f);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1060, 900);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1360, 750);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);

	pObj = CAbstractFactory<CEnemy>::CreateObject(810.f, 1760.f);
	pObj->SetAngle(RADIAN(180.f));
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(810, 1800);
	dynamic_cast<CEnemy*>(pObj)->AddRallyPt(1160, 2010);
	OBJMGR->AddObject(OBJ_ENEMY, pObj);



	SCRLMGR->Initialize();
	SCRLMGR->m_fScrollX = SCRLMGR->GetScrollMaxX();
	SCRLMGR->m_fScrollY = SCRLMGR->GetScrollMaxY();

	SNDMGR->PlaySound(L"BGM_START.wav", SNDMGR->BGM);
}

int CMission01::Update(){
	SCRLMGR->Update();
	UIMGR->Update();
	UNITMGR->Update();
	OBJMGR->Update();
	return 0;
}

void CMission01::Render(HDC _hdc){
	OBJMGR->Render(_hdc);
}
