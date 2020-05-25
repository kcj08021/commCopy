#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

class CKeyManager{
	DECLARE_SINGLETON(CKeyManager);

//��� ����
private:
	KEYFLAG m_KeyFlag;
	KEYFLAG m_KeyDownFlag;
	KEYFLAG m_KeyUpFlag;

//������ �� �Ҹ���
private:
	explicit CKeyManager();
	virtual ~CKeyManager();
//��� �Լ�
public:
	void Update();
	bool IsKeyPressing(KEYFLAG _key);
	bool IsKeyDown(KEYFLAG _key);
	bool IsKeyUp(KEYFLAG _key);
};

#define KEYMGR CKeyManager::GetInstance()
#endif // !__KEY_MANAGER_H__
