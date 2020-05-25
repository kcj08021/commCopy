#include "stdafx.h"
#include "CollisionManager.h"
#include "GameObject.h"

CCollsionMgr::CCollsionMgr(){
}


CCollsionMgr::~CCollsionMgr(){
}

void CCollsionMgr::CollisionRect(CGameObject* dstObj, CGameObject* srcObj){
	RECT rc = {};
	if(nullptr == dstObj || nullptr == srcObj)
		return;

			// BOOL IntersectRect(RECT* pOut, const RECT* pIn1, const RECT* pIn2)
			// �� �簢���� �浹�� �˻��ϴ� API �Լ�
	if(IntersectRect(&rc, &(dstObj->GetRect()), &(srcObj->GetRect()))){
		dstObj->SetDamage(true);
		srcObj->SetDead(true);
	}

}

void CCollsionMgr::CollisionRectEX(CGameObject* dstObj, CGameObject* srcObj){
	if(nullptr == dstObj || nullptr == srcObj)
		return;

	float fMoveX = 0.f, fMoveY = 0.f;

	if(CheckRect(dstObj, srcObj, &fMoveX, &fMoveY)){
		float fX = dstObj->GetInfo().fX;
		float fY = dstObj->GetInfo().fY;

		if(fMoveX > fMoveY) // �İ�� ���̰� ª�� ������ �о ��.
		{
			// Y�� �о��
			if(dstObj->GetInfo().fY > fY){
				// ���� �о ��.						
				dstObj->SetPos(fX, fY - fMoveY);
			} else
				dstObj->SetPos(fX, fY + fMoveY);
		} else{
			// X�� �о��
			if(dstObj->GetInfo().fX > fX)
				dstObj->SetPos(fX - fMoveX, fY);
			else
				dstObj->SetPos(fX + fMoveX, fY);
		}
	}

}

void CCollsionMgr::CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst){
	for(auto& pDest : dstLst){
		for(auto& pSource : srcLst){
			if(CheckSphere(pDest, pSource)){
				pDest->SetDamage(pSource->GetDamage());
				pSource->SetDamage(pDest->GetDamage());
			}
		}
	}
}

bool CCollsionMgr::CheckRect(const CGameObject* pDest, const CGameObject* pSource,
	float* pMoveX, float* pMoveY){
	if(nullptr == pDest || nullptr == pSource)
		return false;
	// �� �簢���� X�� ���� ������ ��	
	float fRadiusX = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;

	// �� �簢���� X�� �Ÿ��� ���� ������ ����.
	// fabs(X): X�� ���� ���� ���ϴ� �Լ�. <math.h>���� ����.
	float fDistX = fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);

	// �� �簢���� Y�� ���� ������ ��.
	float fRadiusY = pDest->GetInfo().fCY * 0.5f + pSource->GetInfo().fCY * 0.5f;

	// �� �簢���� Y�� �Ÿ�
	float fDistY = fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);

	if(fRadiusX >= fDistX && fRadiusY >= fDistY){
		// �İ�� x, y ����
		*pMoveX = fRadiusX - fDistX;
		*pMoveY = fRadiusY - fDistY;

		return true;
	}

	return false;
}

bool CCollsionMgr::CheckSphere(const CGameObject* pDest, const CGameObject* pSource){
	if(nullptr == pDest || nullptr == pSource)
		return false;
	// ������ ��
	float fSumRad = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;

	// ���� �� �Ÿ�
	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// ��Ÿ���	
	float d = sqrtf(w * w + h * h);

	return d <= fSumRad;
}
