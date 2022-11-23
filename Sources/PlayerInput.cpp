#include "PlayerInput.hpp"

void PlayerInput(Mino* mino, Mino* tmpMino, bool* isAnim) {
	//����
	//if���ɓ����8�����Ă�̂́C
	//������͂�1�t���[���ڂŃ~�m���������C
	//�ȍ~��8�t���[�����������Ȃ��Ɠ����Ȃ��悤�ɂ��邽��
	if (keyInputFrames[KEY_INPUT_A] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_A] -= 5;
		if (CanMove(mino, Dir::Left)) {
			//���ɓ������C�t�B�[���h�X�V
			MoveMino(mino, Dir::Left);
			UpdateFieldOnMove(mino, tmpMino);
		}
	}
	if (keyInputFrames[KEY_INPUT_D] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_D] -= 5;
		if (CanMove(mino, Dir::Right)) {
			//�E�ɓ������C�t�B�[���h�X�V
			MoveMino(mino, Dir::Right);
			UpdateFieldOnMove(mino, tmpMino);
		}
	}
	if (keyInputFrames[KEY_INPUT_S] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_S] -= 5;
		if (CanMove(mino, Dir::Down)) {
			//���ɓ������C�t�B�[���h�X�V
			MoveMino(mino, Dir::Down);
			UpdateFieldOnMove(mino, tmpMino);

			//�������ɓ��������ꍇ�͎��R�����̎��Ԃ����Z�b�g
			mino->fallCountTime = 0.0f;
		}
		else {
			//�������ɓ��������Ƃ��Ă������Ȃ��Ƃ������Ƃ͐ڒn����
			GroundMino(mino, isAnim);
		}
	}

	if (keyInputFrames[KEY_INPUT_W] >= 1 && !*isAnim) {

		//�K���Ɉ����āC�A���Ńh���b�v���N���Ȃ��悤�ɂ���
		keyInputFrames[KEY_INPUT_W] -= 100;

		//�ł��邾���~�m�����ɂ��낵������
		while (CanMove(mino, Dir::Down)) {
			MoveMino(mino, Dir::Down);			
		}

		//�t�B�[���h�̍X�V
		UpdateFieldOnMove(mino, tmpMino);

		//�����������������Ƃɂ͂Ȃ�̂ŁC���R�����J�E���g�����Z�b�g
		mino->fallCountTime = 0.0f;

		//�ڒn
		GroundMino(mino, isAnim);
	}

	//�����v���̉�]
	if (keyInputFrames[KEY_INPUT_J] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_J] -= 100;//�K���Ɉ������ƂŁC���������ĉ�]���Ȃ��悤�ɂ���
		RotaMino(mino, tmpMino, RotaDir::CounterClockwise);
	}


	//���v���̉�]
	if (keyInputFrames[KEY_INPUT_K] >= 1 && !*isAnim) {
		keyInputFrames[KEY_INPUT_K] -= 100;//�K���Ɉ������ƂŁC���������ĉ�]���Ȃ��悤�ɂ���
		RotaMino(mino, tmpMino, RotaDir::Clockwise);
	}
}