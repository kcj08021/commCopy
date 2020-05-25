#ifndef __CONTROL_BACKGROUND_H__
#define __CONTROL_BACKGROUND_H__


#include "GameObject.h"
class CControlBackground: public CGameObject{
private:
	
public:
	explicit CControlBackground();
	virtual ~CControlBackground();

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__CONTROL_BACKGROUND_H__

