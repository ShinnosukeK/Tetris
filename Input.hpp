#pragma once
#include "DxLib.h"
extern char key[256];
extern char keyPushedState[256];
extern int keyInputFrames[256];

/// <summary>
/// ����key��������Ă�����1�C������Ă��Ȃ�������0
/// </summary>
bool GetPushedKeyStateAll(int keyCode);

/// <summary>
/// ����key����F�̊ԉ�����Ă��邩�B�����Ƒ�0�ɂȂ�B
/// </summary>
int UpdateKeyInputFrames();