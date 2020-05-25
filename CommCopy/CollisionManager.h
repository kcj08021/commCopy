#ifndef __COLLISION_MANAGER_H__
#define __COLLISION_MANAGER_H__

class CCollisionManager{
	DECLARE_SINGLETON(CCollisionManager);
	
private:
	explicit CCollisionManager();
	virtual ~CCollisionManager();
};

#define COLLMGR CCollisionManager::GetInstance()

#endif // !__COLLISION_MANAGER_H__
