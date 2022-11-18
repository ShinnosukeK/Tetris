#pragma once
#include "DxLib.h"

class Timer {
private:
	LONGLONG nowTime;//現フレームの時刻
	LONGLONG time;//1フレーム前の時刻
	LONGLONG fpsCheckTime;//FPS計測用のスタート時刻
	float deltaTime;//フレーム間の時間
	int fps;
	int fpsCount;//経過フレームを数えていくための変数

public:
	/// <summary>
	/// タイマーの初期化
	/// </summary>
	void InitTimer();

	/// <summary>
	/// FPSを計測（毎フレーム呼び出し続けること）
	/// </summary>
	void CountFPS();

	int GetFPS();
	float GetDeltaTime();
};

