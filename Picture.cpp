#include "Picture.hpp"

void LoadMino(int* handle) {

	//�~�m�摜�ǂݍ���
	LoadDivGraph("Pictures/minos.png", 11, 11, 1, 12, 12, handle);

	for (int i = 11; i < 18; i++) {
		//Grounded_Z�~�m(handle[11])����Grounded_T�~�m(handle[17])�܂ł́C
		//Z�~�m(handle[0])����T�~�m(handle[6])�̓����摜�𓖂Ă�
		handle[i] = handle[i - 11];
	}
}