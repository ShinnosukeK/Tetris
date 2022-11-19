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
	
	int handle[18];//ミノ画像用handle
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);//ミノ画像読み込み
	for (int i = 11; i < 18; i++) {
		//Grounded_Zミノ(handle[11])からGrounded_Tミノ(handle[17])までは，
		//Zミノ(handle[0])からTミノ(handle[6])の同じ画像を当てる
		handle[i] = handle[i - 11];
	}

	Mino mino = Mino();//playerが操作するミノ

	Timer timer;//FPS計測用のインスタンス

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS計測と出力
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", timer.GetFPS());
		timer.CountFPS();

		Mino tmpMino = mino;//一時的に保存しておく用のミノ

		//入力
		//if文に入ると8引いてるのは，
		//初回入力は1フレーム目でミノが動くが，
		//以降は8フレーム押し続けないと動かないようにするため
		if (keyInputFrames[KEY_INPUT_A] >= 1) {
			//keyInputFrames[KEY_INPUT_A] -= 8;
			if (CanMove(&mino, Dir::Left)) {
				//左に動かし，フィールド更新
				MoveMino(&mino, Dir::Left);
				UpdateFieldOnMove(&mino, &tmpMino);
			}						
		}
		if (keyInputFrames[KEY_INPUT_D] >= 1) {
			//keyInputFrames[KEY_INPUT_D] -= 8;
			if (CanMove(&mino, Dir::Right)) {
				//右に動かし，フィールド更新
				MoveMino(&mino, Dir::Right);
				UpdateFieldOnMove(&mino, &tmpMino);
			}
		}
		if (keyInputFrames[KEY_INPUT_S] >= 1) {
			keyInputFrames[KEY_INPUT_S] -= 8;
			if (CanMove(&mino, Dir::Down)) {
				//下に動かし，フィールド更新
				MoveMino(&mino, Dir::Down);	
				UpdateFieldOnMove(&mino, &tmpMino);

				//下方向に動かした場合は自由落下の時間をリセット
				mino.fallCountTime = 0.0f;
			}
			else {
				//下方向に動かそうとしても動けないということは接地する
				GroundMino(&mino);				
			}
		}

		//ミノの自由落下を行う（入力の後にあることで，下方向の入力があった直後は自由落下しないようになる）
		//Gravitate(&mino, &tmpMino, &timer);

		//描画
		DrawField(handle);
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}