#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "GameObject.h"
class CEffect:
	public CGameObject{
private:
	EFFECT_TYPE m_etype;
	bool m_bIsLoop;
	bool m_bIsEnded;
public:
	explicit CEffect();
	virtual ~CEffect();

public:
	void SetEffect(EFFECT_TYPE _enum);
	void SetLoop(bool _bool){ m_bIsLoop = _bool; }
	void SetIsEnded(bool _bool){ m_bIsEnded = _bool; }

private:
	// CGameObject을(를) 통해 상속됨
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif //! __EFFECT_H__
