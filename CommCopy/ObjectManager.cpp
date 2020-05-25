#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "AlliedUnit.h"

IMPLEMENT_SINGLETON(CObjectManager);

CObjectManager::CObjectManager(){

}

CObjectManager::~CObjectManager(){
	Release();
}

OBJ_LIST& CObjectManager::GetList(const OBJ_TYPE _enum){
	return m_ObjList[_enum];
}

OBJ_LIST& CObjectManager::GetAlliedList(){
	return m_ObjList[OBJ_ALLIED];
}

void CObjectManager::AddObject(OBJ_TYPE _enum, CGameObject* _pObj){
	m_ObjList[_enum].push_back(_pObj);
}

void CObjectManager::Release(){
	for(OBJ_LIST& eList : m_ObjList){
		for(CGameObject* pObj : eList){
			if(pObj)
				SafeDelete(pObj);
		}
		eList.clear();
	}
}

void CObjectManager::Initialize(){

}

int CObjectManager::Update(){

	for(OBJ_LIST& eList : m_ObjList){
		for(CGameObject* pObj : eList){
			pObj->Update();
		}
	}
	return 0;
}

void CObjectManager::Render(HDC _hdc){
	RECT rcClient = {};
	RECT rc = {};
	GetClientRect(g_hWnd, &rcClient);

	for(int i = 0; i < OBJ_END; ++i){
		switch(OBJ_TYPE(i)){
		case OBJ_MAP:
			for(CGameObject* elem : m_ObjList[i])
				m_RenderList[RENDER_BACKGRUOND].push_back(elem);
			continue;
		case OBJ_ALLIED:
			for(CGameObject* elem : m_ObjList[i])
				if(elem->IsDead())
					m_RenderList[RENDER_DEADOBJECT].push_back(elem);
				else
					m_RenderList[RENDER_GAMEOBJECT].push_back(elem);
			continue;
		case OBJ_ENEMY:
			for(CGameObject* elem : m_ObjList[i])
				if(elem->IsDead())
					m_RenderList[RENDER_DEADOBJECT].push_back(elem);
				else
					m_RenderList[RENDER_GAMEOBJECT].push_back(elem);
			continue;
		case OBJ_VEHICLE:
			for(CGameObject* elem : m_ObjList[i])
				if(elem->IsDead())
					m_RenderList[RENDER_DEADOBJECT].push_back(elem);
				else
					m_RenderList[RENDER_GAMEOBJECT].push_back(elem);
			continue;
		case OBJ_USEOBJ:
			for(CGameObject* elem : m_ObjList[i])
				if(elem->IsDead())
					m_RenderList[RENDER_DEADOBJECT].push_back(elem);
				else
					m_RenderList[RENDER_GAMEOBJECT].push_back(elem);
			continue;
		case OBJ_MAPOBJ:
			for(CGameObject* elem : m_ObjList[i])
				m_RenderList[RENDER_GAMEOBJECT].push_back(elem);
			continue;
		case OBJ_EFFECT:
			for(CGameObject* elem : m_ObjList[i])
				m_RenderList[RENDER_EFFECT].push_back(elem);
			continue;
		case OBJ_UI:
			for(CGameObject* elem : m_ObjList[i])
				m_RenderList[RENDER_UI].push_back(elem);
			continue;
		default:
			continue;
		}
	}
		
	for(int i = 0; i < RENDER_END; ++i){


		if(int(RENDER_GAMEOBJECT) == i){
			m_RenderList[i].sort(CRenderLess());
			for(CGameObject* elem : m_RenderList[i])
				if(IntersectRect(&rc, &rcClient, &elem->GetRect()))
					elem->Render(_hdc);
		} else{
			for(CGameObject* elem : m_RenderList[i])
					elem->Render(_hdc);
		}

		if(int(RENDER_UI) == i){
			UIMGR->Render(_hdc);
			UNITMGR->Render(_hdc);
		}
		
		if(int(RENDER_BACKGRUOND) == i)
			TILEMGR->Render(_hdc);
	}

	for(int i = 0; i < RENDER_END; ++i)
		m_RenderList[i].clear();
}