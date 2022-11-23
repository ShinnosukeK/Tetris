#include "DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"
#include "Time.hpp"
#include "Picture.hpp"
#include "PlayerInput.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (Initialize() != 0) return -1;//DXLib初期化
	SRand(12345);//乱数初期化
	InitField();//フィールド初期化
	
	int handle[18];//ミノ画像用handle
	LoadMino(handle);//ミノ画像読み込み

	Mino mino = Mino();//playerが操作するミノ

	bool isGrounded = false;//接地判定用フラグ
	bool isDeleted = false;//ライン消し判定用フラグ
	bool isAnim = false;//アニメ再生のフラグ
	float animTimeSoFar = 0.0f;//アニメ再生中の時間カウント
	float animTime = 1.0f;//アニメ再生時間は0.4秒にする

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS表示
		Time::DisplayFPS();

		//一時的に保存しておくミノ
		Mino tmpMino = mino;
		
		//player入力処理
		PlayerInput(&mino, &tmpMino, &isGrounded, isAnim);

		//ミノの自由落下を行う（入力の後にあることで，下方向の入力があった直後は自由落下しないようになる）
		Gravitate(&mino, &tmpMino, &isGrounded);

		//この時点でミノが動いていれば
		if (IsMinoPosChanged(&mino, &tmpMino)) {
			//フィールド更新
			UpdateFieldOnMove(&mino, &tmpMino);
		}

		//接地によるフィールド更新
		if (isGrounded) {
			//接地
			GroundMino(&mino, &isDeleted);

			//接地フラグを倒す
			isGrounded = false;

			//フィールド更新
			UpdateField(&mino, mino.minoType);


			//ラインを消すフラグが立っていれば
			if (isDeleted) {
				//ラインを消す。ここでブロック全体が下に落ちた後の盤面を一時保存。
				DeleteLine();

				//ラインを消すフラグは倒す
				isDeleted = false;

				//アニメ再生のフラグを立てる
				isAnim = true;				
			}
			//ラインを消さないなら即ミノを初期化し，フィールド更新する
			else {
				mino.InitMino();
				UpdateField(&mino, mino.minoType);
			}
		}				

		//アニメーションフラグを，一定時間経ったら倒す
		if (isAnim) {

			//時間計測
			animTimeSoFar += Time::DeltaTime();

			//計測時間が指定時間を超えたら
			if (animTimeSoFar >= animTime) {

				//フラグ倒す
				isAnim = false;

				//ブロック全体が下に落ちるよう，フィールドを更新する
				for (int i = 0; i < X_SIZE; i++) {
					for (int j = 0; j < Y_SIZE; j++) {
						field[i][j] = tmpField[i][j];
					}
				}

				//時間計測初期化
				animTimeSoFar = 0.0f;

				//ミノを初期化
				mino.InitMino();

				//初期化したミノのためフィールド更新
				UpdateField(&mino, mino.minoType);
			}
		}
		

		//描画
		DrawField(handle);		
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}