#include "Input.hpp"

char key[256];//key押下状態（1ならON，0ならOFF）
char keyPushedState[256];//keyが押され「続けている」かどうかのflag
int keyInputFrames[256];//key押下フレーム数

bool GetPushedKeyStateAll(int keyCode) {

	//押し始めの1F目は0，2F目以降は該当キーが1になる
	for (int i = 0; i < 256; i++) {
		if (key[i] == 1) {
			keyPushedState[i] = 1;
		}
		else {
			keyPushedState[i] = 0;
		}
	}

	//全キー状態取得
	GetHitKeyStateAll(key);

	//あるキーが押されていて，かつ，そのキーがまだ押し続けられているわけではないのであれば
	if (key[keyCode] && !keyPushedState[keyCode]) {
		return true;
	}

	return false;
}

int UpdateKeyInputFrames() {

	//全キー状態取得
	GetHitKeyStateAll(key);

	//キー毎に何F押され続けているかをカウント。離されたら即0にする。
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
