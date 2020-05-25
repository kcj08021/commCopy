#include "stdafx.h"
#include "KeyManager.h"

IMPLEMENT_SINGLETON(CKeyManager);

CKeyManager::CKeyManager()
	: m_KeyFlag(KEY_NULL), m_KeyDownFlag(KEY_NULL), m_KeyUpFlag(KEY_NULL){

}

CKeyManager::~CKeyManager(){

}

void CKeyManager::Update(){
	m_KeyFlag = KEY_NULL;

	if(GetAsyncKeyState(VK_UP) & 0x8000)
		m_KeyFlag |= KEY_UP;
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_KeyFlag |= KEY_DOWN;
	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_KeyFlag |= KEY_LEFT;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_KeyFlag |= KEY_RIGHT;
	if(GetAsyncKeyState(CHAR_Z) & 0x8000)
		m_KeyFlag |= KEY_CHAR_Z;
	if(GetAsyncKeyState(CHAR_X) & 0x8000)
		m_KeyFlag |= KEY_CHAR_X;
	if(GetAsyncKeyState(CHAR_C) & 0x8000)
		m_KeyFlag |= KEY_CHAR_C;
	if(GetAsyncKeyState(CHAR_A) & 0x8000)
		m_KeyFlag |= KEY_CHAR_A;
	if(GetAsyncKeyState(CHAR_S) & 0x8000)
		m_KeyFlag |= KEY_CHAR_S;
	if(GetAsyncKeyState(CHAR_S) & 0x8000)
		m_KeyFlag |= KEY_CHAR_S;
	if(GetAsyncKeyState(CHAR_D) & 0x8000)
		m_KeyFlag |= KEY_CHAR_D;
	if(GetAsyncKeyState(CHAR_G) & 0x8000)
		m_KeyFlag |= KEY_CHAR_G;
	if(GetAsyncKeyState(CHAR_H) & 0x8000)
		m_KeyFlag |= KEY_CHAR_H;
	if(GetAsyncKeyState(CHAR_U) & 0x8000)
		m_KeyFlag |= KEY_CHAR_U;
	if(GetAsyncKeyState(CHAR_1) & 0x8000)
		m_KeyFlag |= KEY_CHAR_1;
	if(GetAsyncKeyState(CHAR_2) & 0x8000)
		m_KeyFlag |= KEY_CHAR_2;
	if(GetAsyncKeyState(CHAR_3) & 0x8000)
		m_KeyFlag |= KEY_CHAR_3;
	if(GetAsyncKeyState(CHAR_0) & 0x8000)
		m_KeyFlag |= KEY_CHAR_0;
	if(GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_KeyFlag |= KEY_SHIFT;
	if(GetAsyncKeyState(VK_CONTROL) & 0x8000)
		m_KeyFlag |= KEY_CTRL;
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_KeyFlag |= KEY_RETURN;

}

bool CKeyManager::IsKeyPressing(KEYFLAG _key){
	if(m_KeyFlag & _key)
		return true;
		
	return false;
}

bool CKeyManager::IsKeyDown(KEYFLAG _key){
	if(!(m_KeyDownFlag & _key) && (m_KeyFlag & _key)){
		m_KeyDownFlag |= _key;
		return true;
	}

	if((m_KeyDownFlag & _key) && !(m_KeyFlag & _key)){
		m_KeyDownFlag ^= _key;
		return false;
	}

	return false;
}

bool CKeyManager::IsKeyUp(KEYFLAG _key){
	if((m_KeyUpFlag & _key) && !(m_KeyFlag & _key)){
		m_KeyUpFlag ^= _key;
		return true;
	}

	if(!(m_KeyUpFlag & _key) && (m_KeyFlag & _key)){
		m_KeyUpFlag |= _key;
		return false;
	}

	return false;
}
