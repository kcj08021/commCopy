#ifndef __BERREL_H__
#define __BERREL_H__

#include "GameObject.h"
class CBarrel :
	public CGameObject {
public:
	explicit CBarrel();
	virtual ~CBarrel();

	// CGameObject��(��) ���� ��ӵ�
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__BERREL_H__


