#pragma once
#include "Scene.h"
class CMission01:
	public CScene{

public:
	explicit CMission01();
	virtual ~CMission01();
	// CScene��(��) ���� ��ӵ�
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

