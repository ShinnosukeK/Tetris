#include "Timer.hpp"

void Timer::InitTimer() {
	time = GetNowHiPerformanceCount();//ゲームループに入る前の時刻保存
	fpsCheckTime = GetNowHiPerformanceCount();//初回のFPS計測の際の基準時刻
	fps = 0;
	fpsCount = 0;
	deltaTime = 0.000001f;//仮の値
}

void Timer::CountFPS() {

	//現時刻保存
	nowTime = GetNowHiPerformanceCount();
	
	//経過時間計測
	deltaTime = (nowTime - time) / 1000000.0f;

	//次のフレームで使う基準時刻として保存	
	time = nowTime;

	fpsCount++;

	//現時刻-計測開始時刻が1sを超えたら
	if (nowTime - fpsCheckTime > 1000000) {

		//FPSを決定
		fps = fpsCount;		

		//FPS計測変数をリセット
		fpsCount = 0;

		//次回のFPS計測の際の基準時刻
		fpsCheckTime = nowTime;
	}
}

int Timer::GetFPS() {
	return this->fps;
}

float Timer::GetDeltaTime() {
	return this->deltaTime;
}