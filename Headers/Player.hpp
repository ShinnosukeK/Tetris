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
	Mino mino;//player�����삷��~�m
	Mino tmpMino;//�ꎞ�ۑ��p�̃~�m
	bool isGrounded;//�ڒn����p�t���O
	bool isDeleted;//���C����������p�t���O
	bool isAnim;//�A�j���Đ��̃t���O
	float animTimeSoFar;//�A�j���Đ����̎��ԃJ�E���g
	float animTime;//�A�j���Đ�����
};