// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//���
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

//�Ŵ���
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

//Visual Leak Detector; �޸� ���� �˻�
#ifdef _DEBUG
#include "vld.h"
#endif
