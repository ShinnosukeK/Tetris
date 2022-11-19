#include "Field.hpp"

int field[X_SIZE][Y_SIZE];//フィールド
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