#ifndef __UNIT_MANAGER_H__
#define __UNIT_MANAGER_H__

class CUnitManager{
	DECLARE_SINGLETON(CUnitManager);
private:
	CGameObject* m_UnitArray[UNIT_END];
	list<CGameObject*>* m_pEnemyList;
	list<CGameObject*>* m_pVehicleList;
	RECT m_SelectRC;
	UNIT_TYPE m_eUnitType;
	UNITSKILLFLAG m_UnitSkill;
	int m_iMultiSound;
private:
	explicit CUnitManager();
	virtual ~CUnitManager();

public:
	void SetUnit(UNIT_TYPE _enum, CGameObject* _obj){
		if(nullptr == m_UnitArray[_enum]){
			m_UnitArray[_enum] = _obj;
			OBJMGR->AddObject(OBJ_ALLIED, _obj);
		}
	}
	void SetEnemyList(){ m_pEnemyList = &OBJMGR->GetList(OBJ_ENEMY); }
	void SetVehicleList(){ m_pVehicleList = &OBJMGR->GetList(OBJ_VEHICLE); }


//À¯´Ö ¸í·Éµé
private:
	void UnitSelect();
	void UnitControl();
	void Prone();
	void Move();
	void Knife();
	void Gun();
	void Carry();
	void Dive();
	void Harpoon();
	void QuitVehicle();

private:
	void Release();
public:
	void Initialize();
	void Update();
	void Render(HDC	_hdc);


	friend class CUIManager;
};

#define UNITMGR CUnitManager::GetInstance()

#endif // !__UNIT_MANAGER_H__
