#ifndef __ABSTRACT_FACTORY_H__
#define __ABSTRACT_FACTORY_H__

#include "GameObject.h"

template <typename T>
class CAbstractFactory{
public:
	static CGameObject* CreateObject(){
		CGameObject* obj = new T;
		obj->Initialize();

		return obj;
	}

	static CGameObject* CreateObject(float _fx, float _fy){
		CGameObject* obj = new T;
		obj->Initialize();
		obj->SetPosition(_fx, _fy);

		return obj;
	}
};

#endif // !__ABSTRACT_FACTORY_H__


