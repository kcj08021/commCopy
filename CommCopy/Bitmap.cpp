#include "stdafx.h"
#include "Bitmap.h"

CBitmap::CBitmap(){
	INIT_STRUCT(m_Bitmap);
	INIT_STRUCT(m_BitmapDC);
	INIT_STRUCT(m_OldBitmap);
	INIT_STRUCT(m_tBmpInfo);
}

CBitmap::~CBitmap(){
	Release();
}

HDC CBitmap::GetBitmapDC() const{
	return m_BitmapDC;
}

void CBitmap::AddBitmap(const wstring _FilePath){
	BITMAP bitmap;

	HDC memDC = GetDC(g_hWnd);
	m_BitmapDC = CreateCompatibleDC(memDC);

	m_Bitmap = static_cast<HBITMAP>(LoadImage(NULL, _FilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	GetObject((HBITMAP)m_Bitmap, sizeof(BITMAP), &bitmap);

	m_tBmpInfo.cx = m_tBmpInfo.InitX = bitmap.bmWidth;
	m_tBmpInfo.cy = m_tBmpInfo.InitY = bitmap.bmHeight;

	m_OldBitmap = static_cast<HBITMAP>(SelectObject(m_BitmapDC, m_Bitmap));

	ReleaseDC(g_hWnd, memDC);
}

void CBitmap::SetBmpInfo(int _iFrameX, int _iFrameY, DWORD _rgb){
	m_tBmpInfo.FrameX = _iFrameX;
	m_tBmpInfo.FrameY = _iFrameY;
	m_tBmpInfo.cx = m_tBmpInfo.InitX/_iFrameX;
	m_tBmpInfo.cy = m_tBmpInfo.InitY/_iFrameY;

	m_tBmpInfo.TransColor = _rgb;
}

void CBitmap::Release(){
	SelectObject(m_BitmapDC, m_OldBitmap);
	DeleteDC(m_BitmapDC);
	DeleteObject(m_Bitmap);
	DeleteObject(m_OldBitmap);
}
