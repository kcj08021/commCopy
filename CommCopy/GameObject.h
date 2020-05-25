#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "Enum.h"

class CGameObject{
private:
protected:
	INFO m_tInfo;
	RECT m_tRECT;
	ANGLE_TYPE m_eAngle;
	STATE_TYPE m_eState;
	HDC m_bmpDC;
	BMPINFO m_BmpInfo;
	int m_iFrameX;
	bool m_bIsVisible;

public:
	explicit CGameObject();
	virtual ~CGameObject();

//Get 멤버 함수
public:
	INFO& GetInfo() { return m_tInfo; }
	RECT& GetRect() { return m_tRECT; }
	int GetHp(){ return m_tInfo.iHp; }
	bool IsDead(){ return m_tInfo.bIsDead; }
	bool IsVisible(){ return m_bIsVisible; }

//Set 멤버 함수
public:
	void SetPosition(float _x, float _y){ m_tInfo.fX = _x; m_tInfo.fY = _y; CGameObject::UpdateRect(); }
	void SetAngle(float _angle){ m_tInfo.fAngle = _angle; CGameObject::UpdateAngleState(); }
	void SetVisible(bool _bool){ m_bIsVisible = _bool; }
	void SetDamage(int _iDamage) { m_tInfo.iHp -= _iDamage; }
//기타 멤버 함수
protected:
	float CalculateDist(POINT& _pt);
	float CalculateDist(float _fx, float _fy);
	void CalculateAngle(POINT& _pt, float _fDist);
	void UpdateRect();
	void UpdateAngleState();
	void ConfigState(float& _fSpeed);
	bool IsEquelPt(POINT* _pt1, POINT* _pt2){
		if(_pt1->x == _pt2->x && _pt1->y == _pt2->y)
			return true;
		else
			return false;
	}

//가상 함수
private:
	virtual void Release() = 0;
protected:
public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC _hdc) = 0;
};
#endif // !__GAMEOBJECT_H__
