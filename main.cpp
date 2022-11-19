#include "../DxLib/DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"
#include "Timer.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (Initialize() != 0) return -1;//DXLib������
	SRand(123456);//����������
	InitField();//�t�B�[���h������
	
	int handle[18];//�~�m�摜�phandle
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);//�~�m�摜�ǂݍ���
	for (int i = 11; i < 18; i++) {
		//Grounded_Z�~�m(handle[11])����Grounded_T�~�m(handle[17])�܂ł́C
		//Z�~�m(handle[0])����T�~�m(handle[6])�̓����摜�𓖂Ă�
		handle[i] = handle[i - 11];
	}

	Mino mino = Mino();//player�����삷��~�m

	Timer timer;//FPS�v���p�̃C���X�^���X

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS�v���Əo��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS:%d", timer.GetFPS());
		timer.CountFPS();

		Mino tmpMino = mino;//�ꎞ�I�ɕۑ����Ă����p�̃~�m

		//����
		//if���ɓ����8�����Ă�̂́C
		//������͂�1�t���[���ڂŃ~�m���������C
		//�ȍ~��8�t���[�����������Ȃ��Ɠ����Ȃ��悤�ɂ��邽��
		if (keyInputFrames[KEY_INPUT_A] >= 1) {
			//keyInputFrames[KEY_INPUT_A] -= 8;
			if (CanMove(&mino, Dir::Left)) {
				//���ɓ������C�t�B�[���h�X�V
				MoveMino(&mino, Dir::Left);
				UpdateFieldOnMove(&mino, &tmpMino);
			}						
		}
		if (keyInputFrames[KEY_INPUT_D] >= 1) {
			//keyInputFrames[KEY_INPUT_D] -= 8;
			if (CanMove(&mino, Dir::Right)) {
				//�E�ɓ������C�t�B�[���h�X�V
				MoveMino(&mino, Dir::Right);
				UpdateFieldOnMove(&mino, &tmpMino);
			}
		}
		if (keyInputFrames[KEY_INPUT_S] >= 1) {
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
				GroundMino(&mino);				
			}
		}

		//�~�m�̎��R�������s���i���͂̌�ɂ��邱�ƂŁC�������̓��͂�����������͎��R�������Ȃ��悤�ɂȂ�j
		//Gravitate(&mino, &tmpMino, &timer);

		//�`��
		DrawField(handle);
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}