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

	if (Initialize() != 0) return -1;//DXLib初期化
	SRand(12345);//乱数初期化
	InitField();//フィールド初期化
	
	int handle[18];//ミノ画像用handle
	LoadMino(handle);//ミノ画像読み込み
	
	//初期化
	Player p;
	p.Player_Initialize();

	while (ProcessMessage()==0 && ScreenFlip()==0 && ClearDrawScreen()==0 && UpdateKeyInputFrames()==0) {		

		//FPS表示
		Time::DisplayFPS();

		//更新
		p.Player_Update();		

		//描画
		p.Player_Draw(handle);		
	}

	if(Finalize()!=0) return -1;
	
	return 0;
}