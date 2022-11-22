#include "../DxLib/DxLib.h"
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

	bool isAnim = false;//�A�j�������s����Ă��邩�ǂ����̃t���O
	float animTimeSoFar = 0.0f;//�A�j���Đ����̎��ԃJ�E���g
	float animTime = 1.0f;//�A�j���Đ����Ԃ�0.4�b�ɂ���

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS�\��
		Time::DisplayFPS();

		//�ꎞ�I�ɕۑ����Ă����~�m
		Mino tmpMino = mino;
		
		//player���͏���
		PlayerInput(&mino, &tmpMino, &isAnim);

		//�~�m�̎��R�������s���i���͂̌�ɂ��邱�ƂŁC�������̓��͂�����������͎��R�������Ȃ��悤�ɂȂ�j
		Gravitate(&mino, &tmpMino, &isAnim);

		//�A�j���[�V�����t���O���C��莞�Ԍo������|��
		if (isAnim) {

			//���Ԍv��
			animTimeSoFar += Time::DeltaTime();

			//�v�����Ԃ��w�莞�Ԃ𒴂�����
			if (animTimeSoFar >= animTime) {

				//�t���O�|��
				isAnim = false;

				//�A�j�����I�������̂ŁC�t�B�[���h���X�V����
				for (int i = 0; i < X_SIZE; i++) {
					for (int j = 0; j < Y_SIZE; j++) {
						field[i][j] = tmpField[i][j];
					}
				}

				animTimeSoFar = 0.0f;

				mino.InitMino();//�~�m�̏�����
			}
		}

		//�`��
		DrawField(handle);		
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}