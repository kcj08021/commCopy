#ifndef __CLEAR_SCENE_H__
#define __CLEAR_SCENE_H__

#include "Scene.h"
class CClearScene:
	public CScene{
private:
	RECT m_Button;

public:
	explicit CClearScene();
	virtual ~CClearScene();

	// CScene을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__CLEAR_SCENE


