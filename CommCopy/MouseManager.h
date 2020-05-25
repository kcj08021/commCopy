#ifndef __MOUSE_MANAGER_H__
#define __MOUSE_MANAGER_H__

class CMouseManager{
	DECLARE_SINGLETON(CMouseManager);

private:
	POINT		m_MousePosition;			//���콺 ��ġ
	MOUSEFLAG	m_MouseFlag;				//���콺 �÷���
	MOUSEFLAG	m_MBDownFlag;				//���콺 ���� �÷���
	MOUSEFLAG	m_MBUpFlag;					//���콺 Ǯ�� �÷���
	DWORD		m_dwLBTime;
	DWORD		m_dwRBTime;
	MOUSE_ENUM	m_eMouseType;

private:
	explicit CMouseManager();
	virtual ~CMouseManager();

public:
	POINT& GetPos();
public:
	bool IsClick(MOUSEFLAG _flag);
	bool IsClickEnd(MOUSEFLAG _flag);
	bool IsDoubleClick(MOUSEFLAG _flag);
	bool IsDrag(MOUSEFLAG _flag);

public:
	void SetMouseCursor(MOUSE_ENUM _enum){ m_eMouseType = _enum; }

private:
	void Release();
public:
	void Initialize();
	void Update();
	void Render(HDC _hdc);
};

#define	MOUSEMGR CMouseManager::GetInstance()

#endif // !__MOUSE_MANAGER_H__
