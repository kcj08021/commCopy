#ifndef __WALL_H__
#define __WALL_H__

#include "GameObject.h"
class CWall:
	public CGameObject{
public:
	explicit CWall();
	virtual ~CWall();

	// CGameObject��(��) ���� ��ӵ�
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__WALL_H__
