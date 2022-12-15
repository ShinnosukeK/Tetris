#include "Player.hpp"

void Player::Player_Initialize() {
	mino = Mino();
	isGrounded = false;
	isDeleted = false;
	isAnim = false;
	animTimeSoFar = 0.0f;
	animTime = 1.0f;//�A�j���Đ����Ԃ�0.4�b�ɂ���
}

void Player::Player_Update() {
	//�ꎞ�I�ɕۑ����Ă����~�m
	tmpMino = mino;

	//player���͏���
	PlayerInput(&mino, &isGrounded, isAnim);

	//�~�m�̎��R�������s���i���͂̌�ɂ��邱�ƂŁC�������̓��͂�����������͎��R�������Ȃ��悤�ɂȂ�j
	Gravitate(&mino, &isGrounded);


	//���̎��_�Ń~�m�������Ă����
	if (IsMinoPosChanged(mino, tmpMino)) {
		//�t�B�[���h�X�V
		UpdateFieldOnMove(mino, tmpMino);
	}

	//�ڒn�ɂ��t�B�[���h�X�V
	if (isGrounded) {
		//�ڒn
		GroundMino(&mino, &isDeleted);

		//�ڒn�t���O��|��
		isGrounded = false;

		//�t�B�[���h�X�V
		UpdateField(mino, mino.minoType);


		//���C���������t���O�������Ă����
		if (isDeleted) {
			//���C���������B�����Ńu���b�N�S�̂����ɗ�������̔Ֆʂ��ꎞ�ۑ��B
			DeleteLine();

			//���C���������t���O�͓|��
			isDeleted = false;

			//�A�j���Đ��̃t���O�𗧂Ă�
			isAnim = true;
		}
		//���C���������Ȃ��Ȃ瑦�~�m�����������C�t�B�[���h�X�V����
		else {
			mino.InitMino();
			UpdateField(mino, mino.minoType);
		}
	}

	//�A�j���[�V�����t���O���C��莞�Ԍo������|��
	if (isAnim) {

		//���Ԍv��
		animTimeSoFar += Time::DeltaTime();

		//�v�����Ԃ��w�莞�Ԃ𒴂�����
		if (animTimeSoFar >= animTime) {

			//�t���O�|��
			isAnim = false;

			//�u���b�N�S�̂����ɗ�����悤�C�t�B�[���h���X�V����
			for (int i = 0; i < X_SIZE; i++) {
				for (int j = 0; j < Y_SIZE; j++) {
					field[i][j] = tmpField[i][j];
				}
			}

			//���Ԍv��������
			animTimeSoFar = 0.0f;

			//�~�m��������
			mino.InitMino();

			//�����������~�m�̂��߃t�B�[���h�X�V
			UpdateField(mino, mino.minoType);
		}
	}
}

void Player::Player_Draw(int* handle) {
	DrawField(handle);
}

void Player::Player_Finalize() {

}