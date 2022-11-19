#include "Movement.hpp"

bool CanMove(Mino* p, Dir d) {

	//引数のミノを複製
	Mino futureMino = *p;

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

bool IsMinoPosChanged(Mino* mino, Mino* tmpMino) {
	for (int i = 0; i < 4; i++) {
		//方向キーによる移動は平行移動だから，対応する4ブロックのx,y座標を比較して1つでも違えば位置が変化(true）
		if (mino->worldPos[i].x != tmpMino->worldPos[i].x)  return true;
		if (mino->worldPos[i].y != tmpMino->worldPos[i].y)	return true;
	}
	return false;
}

void Gravitate(Mino* mino,Mino* tmpMino, Timer* timer){
	mino->fallCountTime += timer->GetDeltaTime();
	if (mino->fallCountTime > FALL_TIME) {
		mino->fallCountTime = 0.0f;

		//動けるなら自由落下させて，フィールド更新
		if (CanMove(mino, Dir::Down)) {
			MoveMino(mino, Dir::Down);
			UpdateField(tmpMino, BlockType::Background);
			UpdateField(mino, mino->minoType);			
		}
		//動けないということは接地する
		else {
			GroundMino(mino);
		}
	}
}

void GroundMino(Mino* mino) {

	//ミノの色。11を足す理由：例えばZミノはBlockTypeで1に対応するが，
	//「接地されたZミノ」は12に対応するようにして区別したいから
	int number = int(mino->minoType) + 11;

	//上で求めた整数をBlockType型に直す
	BlockType minoType = BlockType(number);

	//接地用のミノの番号でフィールドを更新
	UpdateField(mino, minoType);

	//接地したミノは初期化
	mino->InitMino();	
}