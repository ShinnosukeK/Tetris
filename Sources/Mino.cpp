#include "Mino.hpp"

void Mino::InitMino() {

	//メンバの初期化
	this->rotState = 0;
	this->fallCountTime = 0.0f;	
	this->centerPos = {
		4,1,
	};
	for (int i = 0; i < 4; i++) {
		this->worldPos[i] = {0,0};
	}
	for (int i = 0; i < 4; i++) {
		this->localPos[i] = { 0,0 };
	}

	//ミノの種類（7種類）を決定
	int randomNumber = rand() % 7 + 1;//乱数を1~7から選ぶ
	this->minoType = BlockType(randomNumber);//乱数に基づいてミノの種類（BlockType）を決定

	//ミノの位置を決定
	UpdateLocalBlockPosition();
	UpdateWorldBlockPosition();
}

void Mino::UpdateLocalBlockPosition() {

	int k = 0;
	
	//ミノの種類(1~7)を取得。
	//1を引くのは，shape行列の1成分目は0~6で指定するため
	int type = int(minoType) - 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			//ミノの状態を表す行列（shape[*][*][4][4]）の成分のうち，
			//Noneではない場合は（＝ミノのブロックが何かしらある場合は）
			if (this->shape[type][this->rotState][i][j] != int(BlockType::None)) {
				
				//ミノのブロックが記述されている部分をローカル座標として保存
				this->localPos[k].x = i;
				this->localPos[k].y = j;

				//1ミノにつき4ブロックあるから，k=3まで走査できたら離脱
				if (k == 3)break;
				k++;
			}

		}
	}
}

void Mino::UpdateWorldBlockPosition() {	
	for (int i = 0; i < 4; i++) {

		//ワールド座標は，ミノの中心を表す部分の座標にローカル座標を加えて得る
		this->worldPos[i].x = this->centerPos.x + this->localPos[i].x;
		this->worldPos[i].y = this->centerPos.y + this->localPos[i].y;
	}	
}

//コンストラクタ
Mino::Mino() {

	//ミノの配置を表すものとして，
	//絵的に正しく見える行列reversedShape[*][*][4][4]
	//はそのままreversedShape[*][*][x][y]のようなイメージで描画すると
	//行と列が反転してしまうので，ここで転置してshape[*][*][4][4]に代入
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 4; l++) {
					shape[i][j][k][l] = reversedShape[i][j][l][k];
				}
			}
		}
	}
	InitMino();
}