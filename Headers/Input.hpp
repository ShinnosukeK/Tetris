#pragma once
#include "DxLib.h"
extern char key[256];
extern char keyPushedState[256];
extern int keyInputFrames[256];

/// <summary>
/// ‚ ‚ékey‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç1C‰Ÿ‚³‚ê‚Ä‚¢‚È‚©‚Á‚½‚ç0
/// </summary>
bool GetPushedKeyStateAll(int keyCode);

/// <summary>
/// ‚ ‚ékey‚ª‰½F‚ÌŠÔ‰Ÿ‚³‚ê‚Ä‚¢‚é‚©B—£‚·‚Æ‘¦0‚É‚È‚éB
/// </summary>
int UpdateKeyInputFrames();