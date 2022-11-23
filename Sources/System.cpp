#include "System.hpp"

int Initialize() {

	//初期化に異常があれば-1とする
	if (ChangeWindowMode(TRUE) != 0) return -1;//ウィンドウモードにする
	if (DxLib_Init() != 0) return -1;//DxLib初期化
	if (SetDrawScreen(DX_SCREEN_BACK) != 0) return -1;//裏画面処理開始
	return 0;
}

int Finalize() {
	if(DxLib_End()!=0) return -1;
	return 0;
}