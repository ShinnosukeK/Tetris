#include "Field.hpp"

int field[X_SIZE][Y_SIZE];//フィールド
int tmpField[X_SIZE][Y_SIZE];//仮置き用のフィールド
double extRate = double(MINO_SIZE) / MINO_SIZE_ORIG;//ミノの拡大率

void InitField() {

	//初期状態にフィールド更新
	for (int i = 0; i < Y_SIZE; i++) {
		for (int j = 0; j < X_SIZE; j++) {
			//最左列or最右列なら壁
			if (j == 0 || j == X_SIZE - 1) {
				field[j][i] = int(BlockType::Wall);
			}
			//それ以外の列なら背景
			else {
				field[j][i] = int(BlockType::Background);
			}
			//最上行は空白にしたいので上書き
			if (i == 0) {
				field[j][i] = int(BlockType::Black);
			}
			//最下行なら壁なので上書き
			if (i == Y_SIZE - 1) {
				field[j][i] = int(BlockType::Wall);
			}
		}
	}
}


void UpdateField(Mino* mino, BlockType type) {
	for (int i = 0; i < 4; i++) {
		//受け取ったミノのワールド座標の位置のフィールドを，受け取った色にする
		field[mino->worldPos[i].x][mino->worldPos[i].y] = int(type);
	}
};

void UpdateFieldOnMove(Mino* mino, Mino* tmpMino) {

	//先に移動前のミノに当たるフィールドを背景に更新
	UpdateField(tmpMino, BlockType::Background);

	//後に移動後のミノに当たるフィールドをそのミノの色に更新。
	//これは逆にするとミノ部分が背景に塗られるので注意。
	UpdateField(mino, mino->minoType);
}

void UpdateFieldOnDelete(bool* deleteFlag) {

	//フラグが立っている行だけすべて背景にする
	for (int _y = 0; _y <= 18; _y++) {
		if (deleteFlag[_y] == true) {
			//y=1~19が盤面
			int y = _y + 1;

			//x=1~10が盤面
			for (int x = 1; x <= 10; x++) {
				field[x][y] = int(BlockType::Background);
			}
		}
	}

	//アニメーションとして機能させるため，fieldを一旦は直接いじらず，tmpFieldに保存しておく
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			tmpField[i][j] = field[i][j];
		}
	}

	//消えた分，全体を下にシフトさせる
	for (int y = 18; y >= 1; y--) {

		int count = 0;

		//y行目よりも下の行で何行消えたかをカウント
		for (int _y = y; _y <= 18 ; _y++) {
			if (deleteFlag[_y]) {
				count++;
			}			
		}

		//カウントが存在すればシフトさせる
		if (count != 0) {
			for (int x = 1; x <= 10; x++) {

				//y行目はcount分だけ下にずらす
				tmpField[x][y + count] = tmpField[x][y];

				//移動してしまったy行目は一旦背景にする
				tmpField[x][y] = int(BlockType::Background);
			}
		}
	}
	
	
}


void DrawField(int* handle) {
	for (int j = 0; j < Y_SIZE; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			//スタートの描画場所を決め，そこからミノサイズ分だけずらしながら描画する
			DrawRotaGraph(
				LEFT_CORNER_POS + MINO_SIZE * i,
				UP_CORNER_POS + MINO_SIZE * j,
				extRate, 0.0f, handle[field[i][j] - 1], TRUE);
		}
	}
}

bool CanDeleteLine() {

	//消すラインが存在するかどうかのフラグ
	bool canDelete = false;

	//消すラインを保存するためのフラグ
	bool deleteFlag[19] = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,
	};

	int y = 0;

	//消せるライン判定
	//deleteFlagは_y=0~18を見る
	for (int _y = 0; _y <= 18; _y++) {

		//消す対象はy=1~19の行
		y = _y + 1;

		//消す対象はx=1~10の列
		for (int x = 1; x <= 10; x++) {
			//一行調べていく中で一回でも背景がある場合は消去できないことになる
			if (field[x][y] == int(BlockType::Background))
			{
				deleteFlag[_y] = false;
			}
		}

		//1行でも消すラインがあれば，消せるフラグが立つ
		canDelete = canDelete || deleteFlag[_y];
	}

	return canDelete;
}

void DeleteLine() {

	//消すラインを保存するためのフラグ
	bool deleteFlag[19] = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,
	};

	int y = 0;

	//消せるライン判定
	//deleteFlagは_y=0~18を見る
	for (int _y = 0; _y <= 18; _y++) {

		//消す対象はy=1~19の行
		y = _y + 1;

		//消す対象はx=1~10の列
		for (int x = 1; x <= 10; x++) {
			//一行調べていく中で一回でも背景がある場合は消去できないことになる
			if (field[x][y] == int(BlockType::Background))
			{
				deleteFlag[_y] = false;
			}
		}
	}

	//ラインを消すことによるフィールドの更新
	UpdateFieldOnDelete(deleteFlag);
}