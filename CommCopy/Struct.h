#ifndef __STRUCT_H__
#define __STRUCT_H__

enum TILE_TYPE;
enum UNIT_TYPE;

typedef struct tagInfo{
	float fCX;
	float fCY;
	float fX;
	float fY;
	float fSpeed;
	float fAngle;
	bool bIsDead;
	int iHp;
}INFO;

typedef struct tagBmpInfo{
	int InitX;
	int InitY;
	int cx;
	int cy;
	int FrameX;
	int FrameY;
	DWORD TransColor;
}BMPINFO;

typedef struct tagTileInfo{
	float fX;
	float fY;
	float fCX;
	float fCY;
	TILE_TYPE eTileType;
	COLORREF dwTileColor;
}TILEINFO;

typedef struct tagAStarNode {
	TILEINFO* pTile;
	float iCostG;
	float iCostH;
	float iCostF;
	tagAStarNode* pParantNode;
}AStarNode;

typedef struct tagBoatRenderStruct{
	POINT pt;
	UNIT_TYPE type;
}BoatStruct;
#endif // !__STRUCT_H__
