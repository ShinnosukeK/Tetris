#pragma once
#include "Mino.hpp"
#include "PlayerInput.hpp"
#include "Movement.hpp"

class Player {
public:
	void Player_Initialize();
	void Player_Update();
	void Player_Draw(int* handle);
	void Player_Finalize();
private:
	Mino mino;//playerが操作するミノ
	Mino tmpMino;//一時保存用のミノ
	bool isGrounded;//接地判定用フラグ
	bool isDeleted;//ライン消し判定用フラグ
	bool isAnim;//アニメ再生のフラグ
	float animTimeSoFar;//アニメ再生中の時間カウント
	float animTime;//アニメ再生時間
};