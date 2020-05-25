#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "Scene.h"
class CMenuScene:
	public CScene{
private:
	enum MENU_BUTTON{
		START_BUTTON, QUIT_BUTTON, BUTTON_END
	};
private:
	RECT m_Button[BUTTON_END];
public:
	explicit CMenuScene();
	virtual ~CMenuScene();

	// CScene을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__MENU_SCENE_H__
