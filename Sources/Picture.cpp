#include "Picture.hpp"

void LoadMino(int* handle) {

	//ミノ画像読み込み
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);

	for (int i = 11; i < 18; i++) {
		//Grounded_Zミノ(handle[11])からGrounded_Tミノ(handle[17])までは，
		//Zミノ(handle[0])からTミノ(handle[6])の同じ画像を当てる
		handle[i] = handle[i - 11];
	}
}