#ifndef __TILE_MANAGER_H__
#define __TILE_MANAGER_H__

class CTileManager{
	DECLARE_SINGLETON(CTileManager);

private:
	int m_TileSizeX;
	int m_TileSizeY;
	vector<TILEINFO*> m_vecTileArray;
	HDC m_TileMapDC;

private:
	explicit CTileManager();
	virtual ~CTileManager();

public:
	void CreateTile(int _iMapSizeX, int iMapSizeY);
	bool PathFind(list<POINT*>& _listDest, POINT& _srcPoint, POINT& _destPoint);
	bool PathFindWater(list<POINT*>& _listDest, POINT& _srcPoint, POINT& _destPoint);


public:
	void SetTileMap(HDC _bmpDC){ m_TileMapDC = _bmpDC; }

public:
	TILEINFO* GetTile(const float _x, const float _y) const;
	TILEINFO* GetTile(const POINT& _pt) const;
private:
	void Release();
public:
	void Update();
	void Render(HDC _hdc);
};

#define TILEMGR CTileManager::GetInstance()

#endif // !__TILE_MANAGER_H__

