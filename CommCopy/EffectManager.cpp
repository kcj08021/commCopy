#include "stdafx.h"
#include "EffectManager.h"
#include "Effect.h"

IMPLEMENT_SINGLETON(CEffectManager);

CEffectManager::CEffectManager(): m_pEffectList(nullptr){

}

CEffectManager::~CEffectManager(){
	Release();
}

void CEffectManager::LoadEffect(EFFECT_TYPE _enum, POINT& _pt){
	CEffect* pObj = new CEffect;
	pObj->Initialize();
	pObj->SetEffect(_enum);
	pObj->SetLoop(false);
	pObj->SetIsEnded(true);
	pObj->SetPosition(float(_pt.x) + SCRLMGR->m_fScrollX, float(_pt.y) + SCRLMGR->m_fScrollY);

	m_pEffectList->push_back(pObj);
}

void CEffectManager::EndlessEffect(EFFECT_TYPE _enum, POINT& _pt){
	CEffect* pObj = new CEffect;
	pObj->Initialize();
	pObj->SetEffect(_enum);
	pObj->SetLoop(false);
	pObj->SetIsEnded(false);
	pObj->SetPosition(float(_pt.x) + SCRLMGR->m_fScrollX, float(_pt.y) + SCRLMGR->m_fScrollY);

	m_pEffectList->push_back(pObj);
}

void CEffectManager::LoopEffect(EFFECT_TYPE _enum, POINT& _pt){
	CEffect* pObj = new CEffect;
	pObj->Initialize();
	pObj->SetEffect(_enum);
	pObj->SetLoop(true);
	pObj->SetPosition(float(_pt.x) + SCRLMGR->m_fScrollX, float(_pt.y) + SCRLMGR->m_fScrollY);

	m_pEffectList->push_back(pObj);
}

void CEffectManager::ErasesAllEffect(){
}

void CEffectManager::Release(){
}

void CEffectManager::Initialize(){
	m_pEffectList = &OBJMGR->GetList(OBJ_EFFECT);
}

void CEffectManager::Update(){
	for(OBJ_LIST::iterator iter = m_pEffectList->begin(); iter != m_pEffectList->end(); ++iter){
		if((*iter)->IsDead())
			SafeDelete(*iter);

		iter = m_pEffectList->erase(iter);

		if(iter == m_pEffectList->end())
			break;
	}
}
