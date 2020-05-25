#ifndef __RUBBER_BOAT_H__
#define __RUBBER_BOAT_H__

#include "GameObject.h"
#include "Marine.h"

class CRubberBoat:
	public CGameObject{
private:
	CGameObject* m_Units[UNIT_END];
	float m_fDist;
	bool m_bMarineFrameX;
	list<POINT*> m_PathPt;
	bool m_bFocus;
	bool m_bFoldingFlag;
	time_t m_currTime;
	time_t m_oldTime;

public:
	explicit CRubberBoat();
	virtual ~CRubberBoat();

private:
	void CalculateDist();
	void CalculateAngle();

public:
	bool IsControlable(){ return m_Units[UNIT_MARINE] != nullptr; }
	void SetFocus(bool _bool){ 
		if(m_bIsVisible){
			if(m_Units[UNIT_MARINE] != nullptr){
				m_bFocus = true;
				dynamic_cast<CMarine*>(m_Units[UNIT_MARINE])->SetFocus(true);
			}
		}
	}
	bool SetUnit(UNIT_TYPE _enum,CGameObject* _obj){
		if(m_bIsVisible){
			if(nullptr == m_Units[_enum]){
				m_Units[_enum] = _obj;
				_obj->SetVisible(false);
				return true;
			}
		}
		return false;

	}
	void QuitBoat(UNIT_TYPE _enum){ m_Units[_enum] = nullptr; }
	void SetDest(POINT _pt);
	bool FoldingBoat();
	void OpenBoat();
	bool isUnitIn(){
		for(CGameObject* elem : m_Units)
			if(nullptr != elem)
				return true;
			
		return false;
	}

	// CGameObject을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;

};

#endif // !__RUBBER_BOAT_H__
