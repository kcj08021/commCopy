#ifndef __EFFECT_MANAGER_H__
#define __EFFECT_MANAGER_H__
class CEffectManager{
	DECLARE_SINGLETON(CEffectManager);
private:
	list<CGameObject*>* m_pEffectList;

private:
	explicit CEffectManager();
	virtual ~CEffectManager();

public:
	void LoadEffect(EFFECT_TYPE _enum, POINT& _pt);
	void EndlessEffect(EFFECT_TYPE _enum, POINT& _pt);
	void LoopEffect(EFFECT_TYPE _enum, POINT& _pt);
	void ErasesAllEffect();

private:
	void Release();
public:
	void Initialize();
	void Update();

};

#define EFCTMGR CEffectManager::GetInstance()

#endif // !__EFFECT_MANAGER_H__
