#ifndef __TREE_H__
#define __TREE_H__

#include "GameObject.h"
class CTree:
	public CGameObject{
public:
	explicit CTree();
	virtual ~CTree();

public:
	void SetTree(bool _bool);


	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;

};

#endif // !__TREE_H__
