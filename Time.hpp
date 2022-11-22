#pragma once
#include "DxLib.h"

class Time {
private:
	static LONGLONG nowTime;//現フレームの時刻
	static LONGLONG time;//1フレーム前の時刻
	static LONGLONG fpsCheckTime;//FPS計測用のスタート時刻
	static float deltaTime;//フレーム間の時間
	static int fps;
	static int fpsCount;//経過フレームを数えていくための変数
public:
	/// <summary>
	/// FPSを計測（毎フレーム呼び出し続けること）
	/// </summary>
	static void CountFPS();

	/// <summary>
	/// FPSの表示
	/// </summary>
	static void DisplayFPS();

	static int FPS();
	static float DeltaTime();
};