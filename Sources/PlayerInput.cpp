#include "PlayerInput.hpp"

void PlayerInput(Mino* mino, Mino* tmpMino, bool* isGrounded, const bool& isAnim) {

	//�����ړ����A���œ���Ȃ��悤�ɁC������͒����5�������Ă����Ă���
	if (keyInputFrames[KEY_INPUT_A] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_A] -= 5;
		if (CanMove(mino, Dir::Left)) {
			//���ɓ�����
			MoveMino(mino, Dir::Left);
		}
	}
	if (keyInputFrames[KEY_INPUT_D] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_D] -= 5;
		if (CanMove(mino, Dir::Right)) {
			//�E�ɓ�����
			MoveMino(mino, Dir::Right);
		}
	}
	if (keyInputFrames[KEY_INPUT_S] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_S] -= 5;
		if (CanMove(mino, Dir::Down)) {
			//���ɓ�����
			MoveMino(mino, Dir::Down);

			//�������ɓ��������ꍇ�͎��R�����̎��Ԃ����Z�b�g
			mino->fallCountTime = 0.0f;
		}
		else {
			//�������ɓ��������Ƃ��Ă������Ȃ��Ƃ������Ƃ͐ڒn�t���O�𗧂Ă�
			*isGrounded = true;
		}
	}


	//�n�[�h�h���b�v
	if (keyInputFrames[KEY_INPUT_W] >= 1 && !isAnim) {

		//�K���Ɉ����āC�A���Ńh���b�v���N���Ȃ��悤�ɂ���
		keyInputFrames[KEY_INPUT_W] -= 100;

		//�ł��邾���~�m�����ɂ��낵������
		while (CanMove(mino, Dir::Down)) {	
			MoveMino(mino, Dir::Down);			
		}

		//�����������������Ƃɂ͂Ȃ�̂ŁC���R�����J�E���g�����Z�b�g
		mino->fallCountTime = 0.0f;

		//�ڒn�t���O�𗧂Ă�
		*isGrounded = true;
	}

	//�����v���̉�]
	if (keyInputFrames[KEY_INPUT_J] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_J] -= 100;//�K���Ɉ������ƂŁC���������ĉ�]���Ȃ��悤�ɂ���
		RotaMino(mino, tmpMino, RotaDir::CounterClockwise);
	}


	//���v���̉�]
	if (keyInputFrames[KEY_INPUT_K] >= 1 && !isAnim) {
		keyInputFrames[KEY_INPUT_K] -= 100;//�K���Ɉ������ƂŁC���������ĉ�]���Ȃ��悤�ɂ���
		RotaMino(mino, tmpMino, RotaDir::Clockwise);
	}
}