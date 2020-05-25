#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
class CEnemy: public CGameObject{
private:
	vector<POINT*> m_RallyPt;
	list<POINT*> m_PathPt;
	int m_iRallyIndex;
	time_t m_currTime;
	time_t m_oldTime;
	bool m_DeadSelect;
	bool m_bIsShot;
	bool m_bIsSight;

	INFO m_tBackupInfo;

	CGameObject* m_DetectedUnit;
	bool m_bDetectUnit;
	bool m_bIsCheckFire;

public:
	explicit CEnemy();
	virtual ~CEnemy();

public:
	void AddRallyPt(int _x, int _y) {
		POINT* pt = new POINT{ _x, _y };
		m_RallyPt.push_back(pt);
	}
	void SetTarget(POINT& pt);
	void SetSightOnOff(bool _bool){ m_bIsSight = _bool; }
	void Detect();

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__ENEMY_H__
