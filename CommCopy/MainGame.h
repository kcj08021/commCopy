#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMainGame{
private:
	HDC m_hDC;
	HDC m_memDC;

private:
public:
	explicit CMainGame();
	virtual ~CMainGame();

private:
	void Release();
public:
	void Initialize();
	void Update();
	void Render();
};

#endif // !__MAINGAME_H__