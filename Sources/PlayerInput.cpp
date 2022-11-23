#include "PlayerInput.hpp"

void PlayerInput(Mino* mino, Mino* tmpMino, bool* isGrounded, const bool& isAnim) {

	//横下移動が連続で入らないように，初回入力直後に5を引いてあげている
	if (keyInputFrames[KEY_INPUT_A] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_A] -= 5;
		if (CanMove(mino, Dir::Left)) {
			//左に動かす
			MoveMino(mino, Dir::Left);
		}
	}
	if (keyInputFrames[KEY_INPUT_D] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_D] -= 5;
		if (CanMove(mino, Dir::Right)) {
			//右に動かす
			MoveMino(mino, Dir::Right);
		}
	}
	if (keyInputFrames[KEY_INPUT_S] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_S] -= 5;
		if (CanMove(mino, Dir::Down)) {
			//下に動かす
			MoveMino(mino, Dir::Down);

			//下方向に動かした場合は自由落下の時間をリセット
			mino->fallCountTime = 0.0f;
		}
		else {
			//下方向に動かそうとしても動けないということは接地フラグを立てる
			*isGrounded = true;
		}
	}


	//ハードドロップ
	if (keyInputFrames[KEY_INPUT_W] >= 1 && !isAnim) {

		//適当に引いて，連続でドロップが起きないようにする
		keyInputFrames[KEY_INPUT_W] -= 100;

		//できるだけミノを下におろし続ける
		while (CanMove(mino, Dir::Down)) {	
			MoveMino(mino, Dir::Down);			
		}

		//下方向を押したことにはなるので，自由落下カウントをリセット
		mino->fallCountTime = 0.0f;

		//接地フラグを立てる
		*isGrounded = true;
	}

	//反時計回りの回転
	if (keyInputFrames[KEY_INPUT_J] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_J] -= 100;//適当に引くことで，長押しして回転しないようにする
		RotaMino(mino, tmpMino, RotaDir::CounterClockwise);
	}


	//時計回りの回転
	if (keyInputFrames[KEY_INPUT_K] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_K] -= 100;//適当に引くことで，長押しして回転しないようにする
		RotaMino(mino, tmpMino, RotaDir::Clockwise);
	}
}