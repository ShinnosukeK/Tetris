#include "../DxLib/DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"
#include "Timer.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (Initialize() != 0) return -1;//DXLib初期化
	SRand(123456);//乱数初期化
	InitField();//フィールド初期化
	
	int handle[11];//ミノ画像用handle
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);//ミノ画像読み込み

	Mino mino = Mino();//playerが操作するミノ

	Timer timer;//FPS計測用のインスタンス

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS計測と出力
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", timer.GetFPS());
		timer.CountFPS();

		Mino tmpMino = mino;//一時的に保存しておく用のミノ

		
		//入力
		if (keyInputFrames[KEY_INPUT_A] >= 1) {
			if (CanMove(&mino, Dir::Left)) {
				MoveMino(&mino, Dir::Left);
			}			
		}
		if (keyInputFrames[KEY_INPUT_S] >= 1) {
			if (CanMove(&mino, Dir::Down)) {
				MoveMino(&mino, Dir::Down);
				mino.fallCountTime = 0.0f;//下方向に動かした場合は自由落下の時間をリセット
			}
		}
		if (keyInputFrames[KEY_INPUT_D] >= 1) {
			if (CanMove(&mino, Dir::Right)) {
				MoveMino(&mino, Dir::Right);
			}
		}

		//ミノの自由落下を行う（入力の後にあることで，下方向の入力があった直後は自由落下しないようになる）
		Gravitate(&mino, &timer);
		
		//更新
		UpdateField(mino,tmpMino);
		DrawField(handle);
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}