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

	if (Initialize() != 0) return -1;//DXLib������
	SRand(12345);//����������
	InitField();//�t�B�[���h������
	
	int handle[18];//�~�m�摜�phandle
	LoadMino(handle);//�~�m�摜�ǂݍ���

	Mino mino = Mino();//player�����삷��~�m

	bool isGrounded = false;//�ڒn����p�t���O
	bool isDeleted = false;//���C����������p�t���O
	bool isAnim = false;//�A�j���Đ��̃t���O
	float animTimeSoFar = 0.0f;//�A�j���Đ����̎��ԃJ�E���g
	float animTime = 1.0f;//�A�j���Đ����Ԃ�0.4�b�ɂ���

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS�\��
		Time::DisplayFPS();

		//�ꎞ�I�ɕۑ����Ă����~�m
		Mino tmpMino = mino;
		
		//player���͏���
		PlayerInput(&mino, &tmpMino, &isGrounded, isAnim);

		//�~�m�̎��R�������s���i���͂̌�ɂ��邱�ƂŁC�������̓��͂�����������͎��R�������Ȃ��悤�ɂȂ�j
		Gravitate(&mino, &tmpMino, &isGrounded);

		//���̎��_�Ń~�m�������Ă����
		if (IsMinoPosChanged(&mino, &tmpMino)) {
			//�t�B�[���h�X�V
			UpdateFieldOnMove(&mino, &tmpMino);
		}

		//�ڒn�ɂ��t�B�[���h�X�V
		if (isGrounded) {
			//�ڒn
			GroundMino(&mino, &isDeleted);

			//�ڒn�t���O��|��
			isGrounded = false;

			//�t�B�[���h�X�V
			UpdateField(&mino, mino.minoType);


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
				UpdateField(&mino, mino.minoType);
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
				UpdateField(&mino, mino.minoType);
			}
		}
		

		//�`��
		DrawField(handle);		
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}