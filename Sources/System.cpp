#include "System.hpp"

int Initialize() {

	//�������Ɉُ킪�����-1�Ƃ���
	if (ChangeWindowMode(TRUE) != 0) return -1;//�E�B���h�E���[�h�ɂ���
	if (DxLib_Init() != 0) return -1;//DxLib������
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//����ʏ����J�n
	return 0;
}

int Finalize() {
	if(DxLib_End()!=0) return -1;
	return 0;
}