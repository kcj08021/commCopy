#ifndef __MARINE_H__
#define __MARINE_H__

#include "AlliedUnit.h"
class CMarine: public CAlliedUnit{
private:
	bool m_bFoldingBoat;
	
public:
	explicit CMarine();
	virtual ~CMarine();

public:
	void SetFoldingBoat(bool _bool){ m_bFoldingBoat = _bool; }

public:
	bool GetFoldingBoat(){ return m_bFoldingBoat; }

	// CAlliedUnit을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__MARINE_H__
