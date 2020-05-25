#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "SingletonDefine.h"
#include "KeyCodeDefine.h"
#include "FlagDefine.h"
#include "FilePath.h"

#define WINCX 800
#define WINCY 600
#define GAP_X 30
#define GAP_Y 45

#define PI 3.141592f

#define IMAGE_SET_TIMING 6

#define TILE_CX 10.f
#define TILE_CY 10.f

//제곱
#define SQUERE(val) ((val) * (val))

//각도->라디안 변환
#define RADIAN(Degree) ((Degree) * PI / 180.f)

//라디안->각도 변환
#define DEGREE(Radian) ((Radian) * 180.f / PI)

#include <string.h>
#define INIT_ARRAY(arr) memset(arr, 0, sizeof(arr));
#define INIT_STRUCT(st) memset(&st, 0, sizeof(st));

#endif // !__DEFINE_H__
