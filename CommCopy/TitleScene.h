#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "Scene.h"
class CTitleScene:
	public CScene{

public:
	explicit CTitleScene();
	virtual ~CTitleScene();
	// CScene��(��) ���� ��ӵ�
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__TITLE_SCENE_H__

