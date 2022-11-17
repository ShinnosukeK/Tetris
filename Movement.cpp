#include "Movement.hpp"

bool CanMove(Mino* p, Dir d) {

	//引数のミノを複製
	Mino futureMino = *p;

	//複製したミノを仮想的に動かしてみる
	MoveMino(&futureMino, d);
	
	//仮想的に動かしたミノを構成する4ブロックのうち，最小のx座標をもつブロックのワールド座標を取得
	Pos minXPos = futureMino.GetMinXBlockPosition();

	//仮想的に動かしたミノを構成する4ブロックのうち，最大のx座標をもつブロックのワールド座標を取得
	Pos maxXPos = futureMino.GetMaxXBlockPosition();

	//仮想的に動かしたミノを構成する4ブロックのうち，最大のy座標をもつブロックのワールド座標を取得
	Pos maxYPos = futureMino.GetMaxYBlockPosition();

	//基本は動かせるとしてフラグを立てておく
	bool flag = true;

	//移動できるか
	switch (d) {
	case Dir::Left:
		//「最小のx座標を持つブロック」の位置が背景以外のものだと，「左には」動かせないことになる
		if (field[minXPos.x][minXPos.y] != (int)BlockType::Background) {
			flag = false;			
		}
		break;
	case Dir::Down:
		//「最大のy座標を持つブロック」の位置が背景以外のものだと，「下には」動かせないことになる
		if (field[maxYPos.x][maxYPos.y] != (int)BlockType::Background) {
			flag = false;
		}
		break;
	case Dir::Right:
		//「最大のx座標を持つブロック」の位置が背景以外のものだと，「右には」動かせないことになる
		if (field[maxXPos.x][maxXPos.y] != (int)BlockType::Background) {
			flag = false;			
		}
		break;
	}
	
	return flag;

}

void MoveMino(Mino* p, Dir d) {

	//Dirの方向に応じて，1ミノを構成する4ブロックのワールド座標をすべて変化させる
	switch (d) {
	case Dir::Left:
		for (int i = 0; i < 4; i++) {
			//入力が左なら，x座標を減少
			p->worldPos[i].x -= 1;
		}
		break;

	case Dir::Down:
		for (int i = 0; i < 4; i++) {
			//入力が下なら，y座標を増加
			p->worldPos[i].y += 1;
		}
		break;

	case Dir::Right:
		for (int i = 0; i < 4; i++) {
			//入力が右なら，x座標を増加
			p->worldPos[i].x += 1;
		}
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