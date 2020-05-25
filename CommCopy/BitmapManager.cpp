#include "stdafx.h"
#include "BitmapManager.h"
#include "Bitmap.h"

IMPLEMENT_SINGLETON(CBitmapManager);

CBitmapManager::CBitmapManager(){
}

CBitmapManager::~CBitmapManager(){
	Release();
}

void CBitmapManager::AddBMP(const wstring& _szKey, const wstring& _szFilePath){
	auto find_iter = m_BmpMap.find(_szKey);

	if(m_BmpMap.end() != find_iter)
		return;

	CBitmap* pBmp = new CBitmap;
	pBmp->AddBitmap(_szFilePath);

	m_BmpMap.insert({_szKey,pBmp});
}

void CBitmapManager::SetBmpInfo(const wstring& _szKey, int _iFrameX, int _iFrameY, DWORD _rgb){
	map<wstring, CBitmap*>::iterator find_iter = m_BmpMap.find(_szKey);

	if(m_BmpMap.end() == find_iter)
		return;

	find_iter->second->SetBmpInfo(_iFrameX, _iFrameY, _rgb);
}

HDC CBitmapManager::GetBmpDC(const wstring& _szKey) const{
	map<wstring, CBitmap*>::const_iterator find_iter = m_BmpMap.find(_szKey);

	if(m_BmpMap.end() == find_iter)
		return nullptr;

	return find_iter->second->GetBitmapDC();
}

BMPINFO CBitmapManager::GetBmpInfo(const wstring& _szKey) const{
	map<wstring, CBitmap*>::const_iterator find_iter = m_BmpMap.find(_szKey);

	if(m_BmpMap.end() == find_iter)
		return BMPINFO();

	return find_iter->second->GetBmpInfo();
}

void CBitmapManager::Release(){
	for(map<wstring, CBitmap*>::value_type& elem : m_BmpMap){
		SafeDelete(elem.second);
	}
	m_BmpMap.clear();
}
