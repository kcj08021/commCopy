#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "Mission01.h"
#include "ClearScene.h"

IMPLEMENT_SINGLETON(CSceneManager);

CSceneManager::CSceneManager()
	: m_CurrScene(nullptr), m_eCurrSceneType(SCENE_TITLE), m_ePrevSceneType(SCENE_TITLE){

}

CSceneManager::~CSceneManager(){
	Release();
}

void CSceneManager::SetScean(const SCENE_TYPE _enum){
	if(m_CurrScene)
		SafeDelete(m_CurrScene);

	switch(_enum){
	case SCENE_TITLE:
		m_CurrScene = new CTitleScene;
		m_CurrScene->Initialize();

		m_ePrevSceneType = m_eCurrSceneType;
		m_eCurrSceneType = SCENE_TITLE;
		break;
	case SCENE_MENU:
		m_CurrScene = new CMenuScene;
		m_CurrScene->Initialize();

		m_ePrevSceneType = m_eCurrSceneType;
		m_eCurrSceneType = SCENE_MENU;
		break;
	case SCENE_MISSION_01:
		m_CurrScene = new CMission01;
		m_CurrScene->Initialize();

		m_ePrevSceneType = m_eCurrSceneType;
		m_eCurrSceneType = SCENE_MISSION_01;
		break;
	case SCENE_CLEAR:
		m_CurrScene = new CClearScene;
		m_CurrScene->Initialize();

		m_ePrevSceneType = m_eCurrSceneType;
		m_eCurrSceneType = SCENE_CLEAR;
		break;
	default:
		break;
	}
}

void CSceneManager::Release(){
	if(m_CurrScene)
		SafeDelete(m_CurrScene);
}

void CSceneManager::Update(){
	if(m_CurrScene)
		m_CurrScene->Update();
}

void CSceneManager::Render(HDC _hdc){
	if(m_CurrScene)
		m_CurrScene->Render(_hdc);
}

