#pragma once
#include "DxLib.h"
extern char key[256];
extern char keyPushedState[256];
extern int keyInputFrames[256];

/// <summary>
/// あるkeyが押されていたら1，押されていなかったら0
/// </summary>
bool GetPushedKeyStateAll(int keyCode);

/// <summary>
/// あるkeyが何Fの間押されているか。離すと即0になる。
/// </summary>
int UpdateKeyInputFrames();