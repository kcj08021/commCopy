#ifndef __BITMAP_H__
#define __BITMAP_H__

class CBitmap{
private:
	HDC m_BitmapDC;
	HBITMAP m_Bitmap;
	HBITMAP m_OldBitmap;
	BMPINFO m_tBmpInfo;

public:
	explicit CBitmap();
	virtual ~CBitmap();
public:
	void AddBitmap(const wstring _FilePath);
	void SetBmpInfo(int _iFrameX, int _iFrameY, DWORD _rgb);

public:
	HDC GetBitmapDC() const;
	BMPINFO& GetBmpInfo(){ return m_tBmpInfo; }

public:
	void Release();
};
#endif // !__BITMAP_H__
