#ifndef __POLE_H__
#define __POLE_H__

#include "GameObject.h"
class CPole:
	public CGameObject{
public:
	explicit CPole();
	virtual ~CPole();

public:
	void SetSelect(bool _bool);
	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};


#endif // !__POLE_H__
