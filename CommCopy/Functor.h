#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__
#include "Struct.h"
#include "BitmapManager.h"
#include "AlliedUnit.h"

template <typename T>
class IsUnitFocus{
public:
	bool operator()(T _obj){
		return dynamic_cast<CAlliedUnit*>(_obj)->GetFocus();
	}
};

class FCostLess{
public:
	bool operator()(AStarNode* _dest, AStarNode* _src){
		return _dest->iCostF < _src->iCostF;
	}
};

class BoatGreater{
public:
	bool operator()(BoatStruct*& _dest, BoatStruct*& _src){
		return _dest->pt.y < _src->pt.y;
	}

};

class CRenderLess{
public:
	bool operator()(CGameObject* _SrcObj, CGameObject* _DestObj){
		return _SrcObj->GetInfo().fY < _DestObj->GetInfo().fY;
	}
};

#endif // !__FUNCTOR_H__


