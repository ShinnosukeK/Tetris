#include "DxLib.h"
#include "System.hpp"
#include "Input.hpp"
#include "Mino.hpp"
#include "Movement.hpp"
#include "Field.hpp"
#include "Time.hpp"
#include "Picture.hpp"
#include "PlayerInput.hpp"
#include "Player.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (Initialize() != 0) return -1;//DXLib������
	SRand(12345);//����������
	InitField();//�t�B�[���h������
	
	int handle[18];//�~�m�摜�phandle
	LoadMino(handle);//�~�m�摜�ǂݍ���
	
	//������
	Player p;
	p.Player_Initialize();

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS�\��
		Time::DisplayFPS();

		//�X�V
		p.Player_Update();		

		//�`��
		p.Player_Draw(handle);		
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}