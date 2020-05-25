#ifndef __ALLIED_UNIT_H__
#define __ALLIED_UNIT_H__

#include "GameObject.h"
class CAlliedUnit:
	public CGameObject{

protected:
	list<POINT*> m_DestPtList;
	CGameObject* m_pTargetObj;
	float m_fDist;
	bool m_bFocus;
	SKILL_TYPE m_eSkillType;
	bool m_bIsShot;
	UNIT_TYPE m_eUnitType;
	int UnitSound[SOUND_END];
public:
	void SetDest(POINT& _pt);
	void SetFocus(bool _bool);
	void SetState(STATE_TYPE _enum){ m_eState = _enum; }
	void SetSkill(SKILL_TYPE _skill){ m_eSkillType = _skill; }
	void SetTarget(CGameObject* _pObj);
	bool SetShotPoint(POINT& _pt);

public:
	void SoundRefuse();
	void SoundMove();
	void SoundAction();
	void SoundAttacked();

public:
	bool GetFocus(){ return m_bFocus; }
	SKILL_TYPE GetSkill(){ return m_eSkillType; }
	STATE_TYPE GetState(){ return m_eState; }
	CGameObject* GetTarget(){ return m_pTargetObj; }
	UNIT_TYPE GetUnitType(){ return m_eUnitType; }

protected:
	//이동해야 하는 목표에 대한 계산
	void CalculateDist();
	float CalculateDist(POINT& _pt);
	void CalculateAngle();
	void CalculateAngle(POINT& _pt, float _fDist);

public:
	explicit CAlliedUnit();
	virtual ~CAlliedUnit();

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override = 0;
public:
	virtual void Initialize() override = 0;
	virtual int Update() override = 0;
	virtual void Render(HDC _hdc) override = 0;
}; 

#endif // !__ALLIED_UNIT_H__
