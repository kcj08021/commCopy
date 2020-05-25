#ifndef __SCENE_H__
#define __SCENE_H__

class CScene{
private:

public:
	explicit CScene();
	virtual ~CScene();

private:
	virtual void Release()=0;
public:
	virtual void Initialize()=0;
	virtual int Update()=0;
	virtual void Render(HDC _hdc)=0;
};

#endif // !__SCEAN_H__



