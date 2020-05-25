#ifndef __MAP_H__
#define __MAP_H__

#include "GameObject.h"
class CMap: public CGameObject{
public:
	explicit CMap();
	virtual ~CMap();

	// CGameObject��(��) ���� ��ӵ�
private:
	void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__MAP_H__

