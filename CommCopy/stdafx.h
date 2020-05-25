// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <io.h>

//STL
#include <list>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//헤더
#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "AbstractFactory.h"
#include "Function.h"
#include "Enum.h"
#include "Functor.h"

//fmod
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

//매니저
#include "ObjectManager.h"
#include "KeyManager.h"
#include "BitmapManager.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "ScrollManager.h"
#include "TileManager.h"
#include "UnitManager.h"
#include "UIManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

//Visual Leak Detector; 메모리 누수 검사
#ifdef _DEBUG
#include "vld.h"
#endif
