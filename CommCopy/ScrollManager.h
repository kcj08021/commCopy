#ifndef __SCROLL_MANAGER_H__
#define __SCROLL_MANAGER_H__

class CScrollManager{
	DECLARE_SINGLETON(CScrollManager);

public:
	float m_fScrollX;
	float m_fScrollY;

private:
	float m_fScrollMaxX;
	float m_fScrollMaxY;
	float m_fScrollMinX;
	float m_fScrollMinY;

private:
	explicit CScrollManager();
	virtual ~CScrollManager();

//Set 함수
public:
	void SetScrollMaxValue(const float _x, const float _y);
	void SetScrollMinValue(const float _x, const float _y);
	void SetScrollValue(float _x, float _y);

//Get 함수
public:
	inline const float GetScrollMaxX() const { 
		return m_fScrollMaxX; 
	} 
	inline const float GetScrollMaxY() const { 
		return m_fScrollMaxY; 
	}
	inline const float GetScrollMinX() const {
		return m_fScrollMinX;
	}
	inline const float GetScrollMinY() const {
		return m_fScrollMinY;
	}

public:
	void Initialize();
	void Update();
};

#define SCRLMGR CScrollManager::GetInstance()

#endif // !__SCROLL_MANAGER_H__
