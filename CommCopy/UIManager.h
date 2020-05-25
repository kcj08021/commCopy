#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

class CUIManager {
	DECLARE_SINGLETON(CUIManager);
private:
	int m_UnitPictueFrame[UNIT_END];
	RECT m_UnitButton[UNIT_END];
	RECT m_ProneStandButton[UI_STAND_PROEN_END];
	RECT m_SightButton;
	RECT m_InvenButton[UI_BUTTON_END];
	bool m_bInvenButton[UI_BUTTON_END];
	bool m_bIsMouseOnSight;

private:
	explicit CUIManager();
	virtual ~CUIManager();

private:
	void EnemySight(bool _bool);

public:
	void Initialize();
	void Update();

	void Render(HDC _hdc);
};

#define UIMGR CUIManager::GetInstance()

#endif // !__UI_MANAGER_H__
