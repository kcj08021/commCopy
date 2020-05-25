#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

typedef list<CGameObject*> OBJ_LIST;

class CObjectManager{
	DECLARE_SINGLETON(CObjectManager);

private:
	list<CGameObject*> m_ObjList[OBJ_END];
	list<CGameObject*> m_RenderList[RENDER_END];

private:
	explicit CObjectManager();
	virtual ~CObjectManager();

public:
	OBJ_LIST& GetList(const OBJ_TYPE _enum);
	OBJ_LIST& GetAlliedList();

public:
	void AddObject(OBJ_TYPE _enum, CGameObject* _pObj);

private:
	void UnitControl();
	void UnitSelect();

private:
	void Release();
public:
	void Initialize();
	int Update();
	void Render(HDC _hdc);
};

#define OBJMGR CObjectManager::GetInstance()

#endif // !__OBJECT_MANAGER_H__



