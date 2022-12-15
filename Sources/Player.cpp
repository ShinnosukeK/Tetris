#include "Player.hpp"

void Player::Player_Initialize() {
	mino = Mino();
	isGrounded = false;
	isDeleted = false;
	isAnim = false;
	animTimeSoFar = 0.0f;
	animTime = 1.0f;//アニメ再生時間は0.4秒にする
}

void Player::Player_Update() {
	//一時的に保存しておくミノ
	tmpMino = mino;

	//player入力処理
	PlayerInput(&mino, &isGrounded, isAnim);

	//ミノの自由落下を行う（入力の後にあることで，下方向の入力があった直後は自由落下しないようになる）
	Gravitate(&mino, &isGrounded);


	//この時点でミノが動いていれば
	if (IsMinoPosChanged(mino, tmpMino)) {
		//フィールド更新
		UpdateFieldOnMove(mino, tmpMino);
	}

	//接地によるフィールド更新
	if (isGrounded) {
		//接地
		GroundMino(&mino, &isDeleted);

		//接地フラグを倒す
		isGrounded = false;

		//フィールド更新
		UpdateField(mino, mino.minoType);


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
			UpdateField(mino, mino.minoType);
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
			UpdateField(mino, mino.minoType);
		}
	}
}

void Player::Player_Draw(int* handle) {
	DrawField(handle);
}

void Player::Player_Finalize() {

}