#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include "stdafx.h"
#include "Vector3.h"

class ent;

class ent
{
public:
	DWORD vTable; //0x0
	vec3 head; //0x0004
	char _0x0010[36];
	vec3 pos; //0x0034
	vec3 angle; //0x0040
	char _0x004C[37];
	BYTE bScoping; //0x0071
	char _0x0072[134];
	__int32 health; //0x00F8
	__int32 armor; //0x00FC
	char _0x0100[292];
	BYTE bAttacking; //0x0224
	char name[16]; //0x0225
	char _0x0235[247];
	BYTE team; //0x032C
	char _0x032D[11];
	BYTE state; //0x0338
	char _0x0339[59];
};

struct entList
{
	ent* ents[31];
};
