#ifndef __RADIO_TOWER_H__
#define __RADIO_TOWER_H__


#include "GameObject.h"
class CRadioTower:
	public CGameObject{
private:
	time_t m_CurrTime;
	time_t m_OldTime;

public:
	explicit CRadioTower();
	virtual  ~CRadioTower();

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};



#endif // !__RADIO_TOWER_H__
