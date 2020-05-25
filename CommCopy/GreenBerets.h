#ifndef __GREEN_BERETS_H__
#define __GREEN_BERETS_H__

#include "AlliedUnit.h"
class CGreenBerets:
	public CAlliedUnit{
private:
	bool m_bIsLadderEnd;
public:
	explicit CGreenBerets();
	virtual ~CGreenBerets();

	// CAlliedUnit을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__GREEN_BERETS_H__

