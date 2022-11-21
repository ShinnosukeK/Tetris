#include "Time.hpp"

//static変数の初期化
LONGLONG Time::nowTime = 0;
LONGLONG Time::time = 0;
LONGLONG Time::fpsCheckTime = 0;
float Time::deltaTime = 0.0f;
int Time::fps = 0;
int Time::fpsCount = 0;


void Time::CountFPS() {

	//現時刻保存
	Time::nowTime = GetNowHiPerformanceCount();
	
	//経過時間計測
	Time::deltaTime = (Time::nowTime - Time::time) / 1000000.0f;

	//次のフレームで使う基準時刻として保存	
	Time::time = Time::nowTime;

	Time::fpsCount++;

	//現時刻-計測開始時刻が1sを超えたら
	if (Time::nowTime - Time::fpsCheckTime > 1000000) {

		//FPSを決定
		Time::fps = Time::fpsCount;		

		//FPS計測変数をリセット
		Time::fpsCount = 0;

		//次回のFPS計測の際の基準時刻
		Time::fpsCheckTime = Time::nowTime;
	}
}

int Time::FPS() {
	return Time::fps;
}

float Time::DeltaTime() {
	return Time::deltaTime;
}