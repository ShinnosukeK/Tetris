#include "Movement.hpp"

bool CanMove(const Mino& mino, Dir d) {

	//引数のミノを複製
	Mino futureMino = mino;

	//複製したミノを仮想的に動かしてみる
	MoveMino(&futureMino, d);

	//基本は動かせるとしてフラグを設定
	bool flag = true;
	
	for (int i = 0; i < 4; i++) {

		int x = futureMino.worldPos[i].x;//仮想的に移動したミノの1ブロックのワールドx座標
		int y = futureMino.worldPos[i].y;//仮想的に移動したミノの1ブロックのワールドy座標

		//移動後のミノのワールド座標(x,y)が，1つでも壁や接地ミノになれば動かせない(false)
		if (
			field[x][y] == int(BlockType::Wall) ||
			field[x][y] == int(BlockType::Grounded_Z) ||
			field[x][y] == int(BlockType::Grounded_L) ||
			field[x][y] == int(BlockType::Grounded_O) ||
			field[x][y] == int(BlockType::Grounded_S) ||
			field[x][y] == int(BlockType::Grounded_I) ||
			field[x][y] == int(BlockType::Grounded_J) ||
			field[x][y] == int(BlockType::Grounded_T)
			) 
		{
			flag = false;
		}
	}
	
	return flag;

}

void MoveMino(Mino* p, Dir d) {

	//Dirの方向に応じて，1ミノを構成する4ブロックのワールド座標と，1ミノの中心座標を変化させる
	switch (d) {
	case Dir::Left:
		for (int i = 0; i < 4; i++) {
			//入力が左なら，x座標を減少
			p->worldPos[i].x -= 1;
		}

		//ミノの中心もずらす
		p->centerPos.x -= 1;

		break;

	case Dir::Down:
		for (int i = 0; i < 4; i++) {
			//入力が下なら，y座標を増加
			p->worldPos[i].y += 1;			
		}

		//ミノの中心もずらす
		p->centerPos.y += 1;

		break;

	case Dir::Right:
		for (int i = 0; i < 4; i++) {
			//入力が右なら，x座標を増加
			p->worldPos[i].x += 1;		
		}

		//ミノの中心もずらす
		p->centerPos.x += 1;

		break;
	}
};

bool IsMinoPosChanged(const Mino& mino, const Mino& tmpMino) {
	for (int i = 0; i < 4; i++) {
		//方向キーによる移動は平行移動だから，対応する4ブロックのx,y座標を比較して1つでも違えば位置が変化(true）
		if (mino.worldPos[i].x != tmpMino.worldPos[i].x)  return true;
		if (mino.worldPos[i].y != tmpMino.worldPos[i].y)	return true;
	}
	return false;
}

void Gravitate(Mino* mino, bool* isGrounded){

	//時間計測
	mino->fallCountTime += Time::DeltaTime();

	//一定時間経ったら
	if (mino->fallCountTime > FALL_TIME) {

		//時間計測リセット
		mino->fallCountTime = 0.0f;

		//動けるなら自由落下させる
		if (CanMove(*mino, Dir::Down)) {
			MoveMino(mino, Dir::Down);			
		}
		//動けないということは接地フラグを立てる
		else {
			*isGrounded = true;
		}
	}
}

void GroundMino(Mino* mino, bool* isDeleted) {

	//ミノの色。11を足す理由：例えばZミノはBlockTypeで1に対応するが，
	//「接地されたZミノ」は12に対応するようにして区別したいから
	int number = int(mino->minoType) + 11;

	//上で求めた整数をBlockType型に直す
	BlockType t = BlockType(number);

	//ミノの状態を更新
	mino->minoType = t;

	//消すラインが存在するなら
	if (CanDeleteLine()) {
		//ラインを消すフラグを立てる
		*isDeleted = true;
	}
}

bool CanRota(const Mino& mino, RotaDir d) {
	//引数のミノを複製
	Mino futureMino = mino;

	//複製したミノを仮想的に回転してみる
	RotaMino(&futureMino, d);

	//基本は動かせるとしてフラグを設定
	bool flag = true;

	for (int i = 0; i < 4; i++) {

		int x = futureMino.worldPos[i].x;//仮想的に移動したミノの1ブロックのワールドx座標
		int y = futureMino.worldPos[i].y;//仮想的に移動したミノの1ブロックのワールドy座標

		//移動後のミノのワールド座標(x,y)が，1つでも壁や接地ミノになれば動かせない(false)
		if (
			field[x][y] == int(BlockType::Wall) ||
			field[x][y] == int(BlockType::Grounded_Z) ||
			field[x][y] == int(BlockType::Grounded_L) ||
			field[x][y] == int(BlockType::Grounded_O) ||
			field[x][y] == int(BlockType::Grounded_S) ||
			field[x][y] == int(BlockType::Grounded_I) ||
			field[x][y] == int(BlockType::Grounded_J) ||
			field[x][y] == int(BlockType::Grounded_T)
			)
		{
			flag = false;
		}
	}

	return flag;
}

void RotaMino(Mino* mino, RotaDir d) {

	//回転方向により，minoが持つ回転状態を変更
	switch (d) {
	case RotaDir::CounterClockwise:
		mino->rotState = (mino->rotState + 1) % 4;
		break;
	case RotaDir::Clockwise:
		mino->rotState = (mino->rotState + 3) % 4;//+3ではなくて-1としてしまうとバグる。多分負のmodが例外になるから。
		break;
	}	

	//ミノのローカル座標を更新
	mino->UpdateLocalBlockPosition();

	//ミノのワールド座標を更新
	mino->UpdateWorldBlockPosition();
}