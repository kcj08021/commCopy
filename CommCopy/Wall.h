#ifndef __WALL_H__
#define __WALL_H__

#include "GameObject.h"
class CWall:
	public CGameObject{
public:
	explicit CWall();
	virtual ~CWall();

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__WALL_H__
