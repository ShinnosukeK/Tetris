#include "../DxLib/DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"
#include "Time.hpp"
#include "Picture.hpp"

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

		//FPS�v���Əo��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", Time::FPS());
		Time::CountFPS();

		Mino tmpMino = mino;//�ꎞ�I�ɕۑ����Ă����p�̃~�m

		//����
		//if���ɓ����8�����Ă�̂́C
		//������͂�1�t���[���ڂŃ~�m���������C
		//�ȍ~��8�t���[�����������Ȃ��Ɠ����Ȃ��悤�ɂ��邽��
		if (keyInputFrames[KEY_INPUT_A] >= 1 && !isAnim ) {
			keyInputFrames[KEY_INPUT_A] -= 8;
			if (CanMove(&mino, Dir::Left)) {
				//���ɓ������C�t�B�[���h�X�V
				MoveMino(&mino, Dir::Left);
				UpdateFieldOnMove(&mino, &tmpMino);
			}						
		}
		if (keyInputFrames[KEY_INPUT_D] >= 1 && !isAnim) {
			keyInputFrames[KEY_INPUT_D] -= 8;
			if (CanMove(&mino, Dir::Right)) {
				//�E�ɓ������C�t�B�[���h�X�V
				MoveMino(&mino, Dir::Right);
				UpdateFieldOnMove(&mino, &tmpMino);
			}
		}
		if (keyInputFrames[KEY_INPUT_S] >= 1 && !isAnim) {
			keyInputFrames[KEY_INPUT_S] -= 8;
			if (CanMove(&mino, Dir::Down)) {
				//���ɓ������C�t�B�[���h�X�V
				MoveMino(&mino, Dir::Down);	
				UpdateFieldOnMove(&mino, &tmpMino);

				//�������ɓ��������ꍇ�͎��R�����̎��Ԃ����Z�b�g
				mino.fallCountTime = 0.0f;
			}
			else {
				//�������ɓ��������Ƃ��Ă������Ȃ��Ƃ������Ƃ͐ڒn����
				GroundMino(&mino, &isAnim);
			}
		}

		//�~�m�̎��R�������s���i���͂̌�ɂ��邱�ƂŁC�������̓��͂�����������͎��R�������Ȃ��悤�ɂȂ�j
		Gravitate(&mino, &tmpMino,&isAnim);

		//�`��
		DrawField(handle);		

		//�A�j���[�V������isAnim�t���O���C��莞�Ԍo������|��
		if (isAnim) {
			animTimeSoFar += Time::DeltaTime();

			if (animTimeSoFar >= animTime) {
				isAnim = false;

				for (int i = 0; i < X_SIZE; i++) {
					for (int j = 0; j < Y_SIZE; j++) {
						field[i][j] = tmpField[i][j];
					}
				}

				animTimeSoFar = 0.0f;

				mino.InitMino();//�~�m�̏�����
			}
		}
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}