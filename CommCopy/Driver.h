#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "AlliedUnit.h"
class CDriver: public CAlliedUnit{

public:
	explicit CDriver();
	virtual ~CDriver();

	// CAlliedUnit을(를) 통해 상속됨
private:
	virtual void Release() override;
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC _hdc) override;
};

#endif // !__DRIVER_H__
