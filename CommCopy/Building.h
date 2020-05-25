#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "GameObject.h"
class CBuilding:
	public CGameObject{
public:
	explicit CBuilding();
	virtual ~CBuilding();
public:
	void SetBuilding(BUILDING_TYPE _enum);
	// CGameObject��(��) ���� ��ӵ�
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};
#endif // !__BUILDING_H__


