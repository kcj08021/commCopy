#ifndef __FLAGDEFINE_H__
#define __FLAGDEFINE_H__

//입력키에 대한 플래그
typedef DWORD KEYFLAG;		//플래그 저장위한 타입 재정의(2바이트)

//키보드
#define KEY_NULL			0x00000000
#define KEY_UP				0x00000001
#define KEY_DOWN			0x00000002
#define KEY_LEFT			0x00000004
#define KEY_RIGHT			0x00000008
#define KEY_CHAR_X			0x00000010
#define KEY_CHAR_Z			0x00000020
#define KEY_CHAR_C			0X00000040
#define KEY_CHAR_A			0x00000080
#define KEY_CHAR_S			0x00000100
#define KEY_CHAR_D			0x00000200
#define KEY_CHAR_G			0x00001000
#define KEY_CHAR_H			0x00002000
#define KEY_CHAR_U			0x00004000

#define KEY_CHAR_1			0x00008000
#define KEY_CHAR_2			0x00010000
#define KEY_CHAR_3			0x00020000
#define KEY_CHAR_0			0x00040000


#define KEY_SHIFT			0x00100000
#define KEY_CTRL			0x00200000
#define KEY_RETURN			0x00400000

//마우스
typedef unsigned char MOUSEFLAG;
#define MOUSE_NULL		0x00
#define MOUSE_LBCLICK	0x01
#define MOUSE_RBCLICK	0x02
#define MOUSE_LBDCLICK	0x04
#define MOUSE_RBDCLICK	0x08

//유닛 기술 플래그
typedef unsigned short UNITSKILLFLAG;
#define UNITFLAG_NULL		0x0000
#define UNITFLAG_KNIFE		0x0001
#define UNITFLAG_PISTOL		0x0002
#define UNITFLAG_CARRY		0x0004
#define UNITFLAG_HARPOON	0x0010
#define UNITFLAG_SMG		0x0020
#define UNITFLAG_DIVE		0X0040
#define UNITFLAG_QUITBOAT	0X0100

#endif // !__FLAGDEFINE_H__
