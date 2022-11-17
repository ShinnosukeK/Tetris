#include "../DxLib/DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (Initialize() != 0) return -1;//DXLib������
	SRand(123456);//����������
	InitField();//�t�B�[���h������
	
	int handle[11];//�~�m�摜�phandle
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);//�~�m�摜�ǂݍ���

	Mino mino = Mino();//player�����삷��~�m

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		Mino tmpMino = mino;//�ꎞ�I�ɕۑ����Ă����p�̃~�m
		
		//���͔���
		if (keyInputFrames[KEY_INPUT_A] >= 1) {
			if (CanMove(&mino, Dir::Left)) {
				MoveMino(&mino, Dir::Left);
			}			
		}
		if (keyInputFrames[KEY_INPUT_S] >= 1) {
			if (CanMove(&mino, Dir::Down)) {
				MoveMino(&mino, Dir::Down);
			}
		}
		if (keyInputFrames[KEY_INPUT_D] >= 1) {
			if (CanMove(&mino, Dir::Right)) {
				MoveMino(&mino, Dir::Right);
			}
		}

		if (keyInputFrames[KEY_INPUT_R] == 1) {
			mino.InitMino();
		}
		
		//�X�V
		UpdateField(mino,tmpMino);
		DrawField(handle);
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}