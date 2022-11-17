#include "Input.hpp"

char key[256];//key������ԁi1�Ȃ�ON�C0�Ȃ�OFF�j
char keyPushedState[256];//key��������u�����Ă���v���ǂ�����flag
int keyInputFrames[256];//key�����t���[����

bool GetPushedKeyStateAll(int keyCode) {

	//�����n�߂�1F�ڂ�0�C2F�ڈȍ~�͊Y���L�[��1�ɂȂ�
	for (int i = 0; i < 256; i++) {
		if (key[i] == 1) {
			keyPushedState[i] = 1;
		}
		else {
			keyPushedState[i] = 0;
		}
	}

	//�S�L�[��Ԏ擾
	GetHitKeyStateAll(key);

	//����L�[��������Ă��āC���C���̃L�[���܂������������Ă���킯�ł͂Ȃ��̂ł����
	if (key[keyCode] && !keyPushedState[keyCode]) {
		return true;
	}

	return false;
}

int UpdateKeyInputFrames() {

	//�S�L�[��Ԏ擾
	GetHitKeyStateAll(key);

	//�L�[���ɉ�F�����ꑱ���Ă��邩���J�E���g�B�����ꂽ�瑦0�ɂ���B
	for (int i = 0; i < 256; i++) {
		if (key[i] == 1) {
			keyInputFrames[i]++;
		}
		else {
			keyInputFrames[i] = 0;
		}
	}
	return 0;
}
