#include "PlayerInput.hpp"

void PlayerInput(Mino* mino, Mino* tmpMino, bool* isAnim) {
	//入力
	//if文に入ると8引いてるのは，
	//初回入力は1フレーム目でミノが動くが，
	//以降は8フレーム押し続けないと動かないようにするため
	if (keyInputFrames[KEY_INPUT_A] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_A] -= 5;
		if (CanMove(mino, Dir::Left)) {
			//左に動かし，フィールド更新
			MoveMino(mino, Dir::Left);
			UpdateFieldOnMove(mino, tmpMino);
		}
	}
	if (keyInputFrames[KEY_INPUT_D] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_D] -= 5;
		if (CanMove(mino, Dir::Right)) {
			//右に動かし，フィールド更新
			MoveMino(mino, Dir::Right);
			UpdateFieldOnMove(mino, tmpMino);
		}
	}
	if (keyInputFrames[KEY_INPUT_S] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_S] -= 5;
		if (CanMove(mino, Dir::Down)) {
			//下に動かし，フィールド更新
			MoveMino(mino, Dir::Down);
			UpdateFieldOnMove(mino, tmpMino);

			//下方向に動かした場合は自由落下の時間をリセット
			mino->fallCountTime = 0.0f;
		}
		else {
			//下方向に動かそうとしても動けないということは接地する
			GroundMino(mino, isAnim);
		}
	}

	if (keyInputFrames[KEY_INPUT_W] >= 1 && !*isAnim) {

		//適当に引いて，連続でドロップが起きないようにする
		keyInputFrames[KEY_INPUT_W] -= 100;

		//できるだけミノを下におろし続ける
		while (CanMove(mino, Dir::Down)) {
			MoveMino(mino, Dir::Down);			
		}

		//フィールドの更新
		UpdateFieldOnMove(mino, tmpMino);

		//下方向を押したことにはなるので，自由落下カウントをリセット
		mino->fallCountTime = 0.0f;

		//接地
		GroundMino(mino, isAnim);
	}

	//反時計回りの回転
	if (keyInputFrames[KEY_INPUT_J] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_J] -= 100;//適当に引くことで，長押しして回転しないようにする
		RotaMino(mino, tmpMino, RotaDir::CounterClockwise);
	}


	//時計回りの回転
	if (keyInputFrames[KEY_INPUT_K] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_K] -= 100;//適当に引くことで，長押しして回転しないようにする
		RotaMino(mino, tmpMino, RotaDir::Clockwise);
	}
}