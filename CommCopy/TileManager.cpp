#include "stdafx.h"
#include "TileManager.h"

IMPLEMENT_SINGLETON(CTileManager);

CTileManager::CTileManager():m_TileSizeX(0), m_TileSizeY(0){
	INIT_STRUCT(m_TileMapDC);
}

CTileManager::~CTileManager(){
	Release();
}

void CTileManager::CreateTile(int _iMapSizeX, int _iMapSizeY){
	m_TileSizeX = int(_iMapSizeX / TILE_CX);
	m_TileSizeY = int(_iMapSizeY / TILE_CY);

	TILEINFO* pTile = nullptr;

	for(int i = 0; i < m_TileSizeY; ++i){
		for(int j = 0; j < m_TileSizeX; ++j){
			pTile = new TILEINFO;

			pTile->fX = TILE_CX * 0.5f + TILE_CX * j;
			pTile->fY = TILE_CY * 0.5f + TILE_CY * i + float(GAP_Y);
			pTile->fCX = (float)TILE_CX;
			pTile->fCY = (float)TILE_CY;

			if(nullptr != m_TileMapDC){
				pTile->dwTileColor = GetPixel(m_TileMapDC, j, i);

				switch(pTile->dwTileColor){
				case RGB(0, 0, 0):
					pTile->eTileType = TILE_OBJ;
					break;
				case RGB(128, 128, 128):
					pTile->eTileType = TILE_HOUSE;
					break;
				case RGB(0, 0, 255):
					pTile->eTileType = TILE_DWATER;
					break;
				case RGB(0,255,255):
					pTile->eTileType = TILE_WATER;
					break;
				case RGB(181,230,29):
					pTile->eTileType = TILE_WALL;
					break;
				default:
					pTile->eTileType = TILE_NULL;
					break;
				}
			}
			m_vecTileArray.push_back(pTile);
		}
	}
}

bool CTileManager::PathFind(list<POINT*>& _listDest, POINT& _srcPoint, POINT& _destPoint){
	_listDest.clear();

	list<AStarNode*> ClosedList;
	list<AStarNode*> OpenedList;

	TILEINFO* DestTile = TILEMGR->GetTile(_destPoint);
	TILEINFO* CurrTile = TILEMGR->GetTile(_srcPoint);

	AStarNode* currNode = new AStarNode{ CurrTile , 0, 0,0, nullptr };
	ClosedList.push_back(currNode);

	while(ClosedList.back()->pTile != DestTile){
		if(ClosedList.size() > 500){
			for(AStarNode* elem : OpenedList){
				SafeDelete(elem);
			}
			OpenedList.clear();

			for(AStarNode* elem : ClosedList){
				SafeDelete(elem);
			}
			ClosedList.clear();

			return false;
		}

		CurrTile = currNode->pTile;
		for(int i = -10; i <= 10; i += 10){
			for(int j = -10; j <= 10; j += 10){
				if(0 == i && 0 == j)
					continue;

				TILEINFO* selectTile = TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY + j);

				for(AStarNode* elem : ClosedList)
					if(elem->pTile == selectTile){
						selectTile = nullptr;
						break;
					}

				if(nullptr == selectTile)
					continue;

				if(TILE_NULL != selectTile->eTileType && TILE_WATER != selectTile->eTileType && TILE_WALL != selectTile->eTileType)
					continue;

				/*if(TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY)->eTileType != TILE_NULL&& TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY)->eTileType != TILE_WATER)
					continue;

				if(TILEMGR->GetTile(CurrTile->fX, CurrTile->fY + j)->eTileType != TILE_NULL && TILEMGR->GetTile(CurrTile->fX, CurrTile->fY + j)->eTileType != TILE_WATER)
					continue;*/

				float iG = i == 0 || j == 0 ? currNode->iCostG + 10.f : currNode->iCostG + 14.f;
				float iH = abs(DestTile->fX - selectTile->fX) + abs(DestTile->fY - selectTile->fY);
				AStarNode* Node = new AStarNode{ selectTile, iG, iH, iG + iH, currNode };

				for(AStarNode*& elem : OpenedList){
					if(elem->pTile == Node->pTile)
						if(elem->iCostG > Node->iCostG){
							SafeDelete(elem);
							elem = Node;
							Node = nullptr;
							break;
						} else{
							SafeDelete(Node);
							break;
						}
				}
				if(nullptr != Node)
					OpenedList.push_back(Node);
			}
		}

		OpenedList.sort(FCostLess());

		currNode = OpenedList.front();
		ClosedList.push_back(currNode);

		OpenedList.pop_front();
	}

	while(nullptr != currNode){
		TILEINFO* tile = currNode->pTile;
		POINT* pt = new POINT;
		pt->x = int(tile->fX);
		pt->y = int(tile->fY);

		_listDest.push_front(pt);

		currNode = currNode->pParantNode;
	}

	for(AStarNode* elem : OpenedList){
		SafeDelete(elem);
	}
	OpenedList.clear();

	for(AStarNode* elem : ClosedList){
		SafeDelete(elem);
	}
	ClosedList.clear();

	return true;
}

bool CTileManager::PathFindWater(list<POINT*>& _listDest, POINT& _srcPoint, POINT& _destPoint){
	_listDest.clear();

	list<AStarNode*> ClosedList;
	list<AStarNode*> OpenedList;

	TILEINFO* DestTile = TILEMGR->GetTile(_destPoint);
	TILEINFO* CurrTile = TILEMGR->GetTile(_srcPoint);

	AStarNode* currNode = new AStarNode{ CurrTile , 0, 0,0, nullptr };
	ClosedList.push_back(currNode);

	while(ClosedList.back()->pTile != DestTile){
		CurrTile = currNode->pTile;
		for(int i = -10; i <= 10; i += 10){
			for(int j = -10; j <= 10; j += 10){
				if(0 == i && 0 == j)
					continue;

				TILEINFO* selectTile = TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY + j);

				for(AStarNode* elem : ClosedList)
					if(elem->pTile == selectTile){
						selectTile = nullptr;
						break;
					}

				if(nullptr == selectTile)
					continue;

				if(TILE_DWATER != selectTile->eTileType && TILE_WATER != selectTile->eTileType)
					continue;

				/*if(TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY)->eTileType != TILE_NULL&& TILEMGR->GetTile(CurrTile->fX + i, CurrTile->fY)->eTileType != TILE_WATER)
					continue;

				if(TILEMGR->GetTile(CurrTile->fX, CurrTile->fY + j)->eTileType != TILE_NULL && TILEMGR->GetTile(CurrTile->fX, CurrTile->fY + j)->eTileType != TILE_WATER)
					continue;*/

				float iG = i == 0 || j == 0 ? currNode->iCostG + 10.f : currNode->iCostG + 14.f;
				float iH = abs(DestTile->fX - selectTile->fX) + abs(DestTile->fY - selectTile->fY);
				AStarNode* Node = new AStarNode{ selectTile, iG, iH, iG + iH, currNode };

				for(AStarNode*& elem : OpenedList){
					if(elem->pTile == Node->pTile)
						if(elem->iCostG > Node->iCostG){
							SafeDelete(elem);
							elem = Node;
							Node = nullptr;
							break;
						} else{
							SafeDelete(Node);
							break;
						}
				}
				if(nullptr != Node)
					OpenedList.push_back(Node);
			}
		}

		if(OpenedList.size() == 0)
			return false;

		OpenedList.sort(FCostLess());

		currNode = OpenedList.front();
		ClosedList.push_back(currNode);

		OpenedList.pop_front();
	}

	while(nullptr != currNode){
		TILEINFO* tile = currNode->pTile;
		POINT* pt = new POINT;
		pt->x = int(tile->fX);
		pt->y = int(tile->fY);

		_listDest.push_front(pt);

		currNode = currNode->pParantNode;
	}

	for(AStarNode* elem : OpenedList){
		SafeDelete(elem);
	}
	OpenedList.clear();

	for(AStarNode* elem : ClosedList){
		SafeDelete(elem);
	}
	ClosedList.clear();

	return true;
}

TILEINFO* CTileManager::GetTile(const float _x, const float _y) const{
	int iIndexX = int(_x) / 10;
	int iIndexY = int(_y - GAP_Y) / 10;

	if(unsigned(m_TileSizeX * iIndexY + iIndexX) >= m_vecTileArray.size() || m_TileSizeX * iIndexY + iIndexX < 0)
		return nullptr;

	return m_vecTileArray[m_TileSizeX * iIndexY + iIndexX];
}

TILEINFO* CTileManager::GetTile(const POINT& _pt) const{
	int iIndexX = int(_pt.x) / 10;
	int iIndexY = int(_pt.y - GAP_Y) / 10;

	if(unsigned(m_TileSizeX * iIndexY + iIndexX) >= m_vecTileArray.size() || m_TileSizeX * iIndexY + iIndexX < 0)
		return nullptr;

	return m_vecTileArray[m_TileSizeX * iIndexY + iIndexX];
}



void CTileManager::Release(){
	for(TILEINFO* elem : m_vecTileArray)
		SafeDelete(elem);

	m_vecTileArray.clear();
}

void CTileManager::Update(){
}

void CTileManager::Render(HDC _hdc){
	RECT rc = {};
	int iRow = int(SCRLMGR->m_fScrollY / TILE_CY);
	int iCol = int(SCRLMGR->m_fScrollX / TILE_CX);
	int iRowMax = iRow + int((WINCY - GAP_Y) / TILE_CY);
	int iColMax = iCol + int((WINCX - GAP_X) / TILE_CX);

	if(KEYMGR->IsKeyPressing(KEY_CHAR_A)){
		for(int i = iRow; i < iRowMax; ++i)
			for(int j = iCol; j < iColMax; ++j){
				int iTileIndex = i * m_TileSizeX + j;
				if(m_vecTileArray.size() <= size_t(iTileIndex))
					continue;

				rc.left = LONG(m_vecTileArray[iTileIndex]->fX - TILE_CX / 2 - SCRLMGR->m_fScrollX);
				rc.right = LONG(m_vecTileArray[iTileIndex]->fX + TILE_CX / 2 - SCRLMGR->m_fScrollX);
				rc.top = LONG(m_vecTileArray[iTileIndex]->fY - TILE_CY / 2 - SCRLMGR->m_fScrollY);
				rc.bottom = LONG(m_vecTileArray[iTileIndex]->fY + TILE_CY / 2 - SCRLMGR->m_fScrollY);

				HBRUSH brush = CreateSolidBrush(m_vecTileArray[iTileIndex]->dwTileColor);
				HBRUSH oldBrush = (HBRUSH)SelectObject(_hdc, brush);

				Rectangle(_hdc, rc.left, rc.top, rc.right, rc.bottom);

				SelectObject(_hdc, oldBrush);
				DeleteObject(brush);
			}
	}
}
