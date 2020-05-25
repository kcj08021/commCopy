#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template <typename T>
constexpr void SafeDelete(T& _ptr) {
	if (_ptr) {
		delete _ptr;
		_ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& _ptr) {
	if (_ptr) {
		delete[] _ptr;
		_ptr = nullptr;
	}
}

inline float GetAngleToPoint(POINT& _SrcPt, POINT& _DestPt){
	float fDist = sqrtf(float(SQUERE(_SrcPt.x - _DestPt.x) + SQUERE(_SrcPt.y - _DestPt.y)));
	float fAngle = acosf((_DestPt.x - _SrcPt.x) / fDist);

	if(isnan(fAngle) != 0)
		fAngle = -1 / 4 * PI;

	if(_DestPt.y > _SrcPt.y)
		fAngle *= -1.f;

	return fAngle;
}




#endif // !__FUNCTION_H__
