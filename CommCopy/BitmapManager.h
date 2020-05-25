#ifndef __BITMAP_MANAGER_H__
#define __BITMAP_MANAGER_H__

class CBitmap;

class CBitmapManager{
	DECLARE_SINGLETON(CBitmapManager);
private:
	map<wstring, CBitmap*> m_BmpMap;

private:
	explicit CBitmapManager();
	virtual ~CBitmapManager();

public:
	void AddBMP(const wstring& _szKey, const wstring& _szFilePath);
	void SetBmpInfo(const wstring& _szKey, int  _iFrameX, int _iFrameY, DWORD _rgb);

public:
	HDC GetBmpDC(const wstring& _szKey) const;
	BMPINFO GetBmpInfo(const wstring& _szKey) const;

private:
	void Release();

};

#define BMPMGR CBitmapManager::GetInstance()

#endif // !__BITMAP_MANAGER_H__
