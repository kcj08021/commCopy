#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__
class CScene;

class CSceneManager{
	DECLARE_SINGLETON(CSceneManager);

private:
	CScene* m_CurrScene;
	SCENE_TYPE m_eCurrSceneType;
	SCENE_TYPE m_ePrevSceneType;

private:
	explicit CSceneManager();
	virtual ~CSceneManager();

//¸â¹ö ÇÔ¼ö
public:
	void SetScean(const SCENE_TYPE _enum);

private:
	void Release();
public:
	void Update();
	void Render(HDC _hdc);
};

#define SCNMGR CSceneManager::GetInstance()

#endif // !__SCENE_MANAGER_H__

