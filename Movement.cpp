#include "Movement.hpp"

bool CanMove(Mino* p, Dir d) {

	//�����̃~�m�𕡐�
	Mino futureMino = *p;

	//���������~�m�����z�I�ɓ������Ă݂�
	MoveMino(&futureMino, d);

	//��{�͓�������Ƃ��ăt���O��ݒ�
	bool flag = true;
	
	for (int i = 0; i < 4; i++) {

		int x = futureMino.worldPos[i].x;//���z�I�Ɉړ������~�m��1�u���b�N�̃��[���hx���W
		int y = futureMino.worldPos[i].y;//���z�I�Ɉړ������~�m��1�u���b�N�̃��[���hy���W

		//�ړ���̃~�m�̃��[���h���W(x,y)���C1�ł��ǂ�ڒn�~�m�ɂȂ�Γ������Ȃ�(false)
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

	//Dir�̕����ɉ����āC1�~�m���\������4�u���b�N�̃��[���h���W�ƁC1�~�m�̒��S���W��ω�������
	switch (d) {
	case Dir::Left:
		for (int i = 0; i < 4; i++) {
			//���͂����Ȃ�Cx���W������
			p->worldPos[i].x -= 1;
		}

		//�~�m�̒��S�����炷
		p->centerPos.x -= 1;

		break;

	case Dir::Down:
		for (int i = 0; i < 4; i++) {
			//���͂����Ȃ�Cy���W�𑝉�
			p->worldPos[i].y += 1;			
		}

		//�~�m�̒��S�����炷
		p->centerPos.y += 1;

		break;

	case Dir::Right:
		for (int i = 0; i < 4; i++) {
			//���͂��E�Ȃ�Cx���W�𑝉�
			p->worldPos[i].x += 1;		
		}

		//�~�m�̒��S�����炷
		p->centerPos.x += 1;

		break;
	}
};

bool IsMinoPosChanged(Mino* mino, Mino* tmpMino) {
	for (int i = 0; i < 4; i++) {
		//�����L�[�ɂ��ړ��͕��s�ړ�������C�Ή�����4�u���b�N��x,y���W���r����1�ł��Ⴆ�Έʒu���ω�(true�j
		if (mino->worldPos[i].x != tmpMino->worldPos[i].x)  return true;
		if (mino->worldPos[i].y != tmpMino->worldPos[i].y)	return true;
	}
	return false;
}

void Gravitate(Mino* mino,Mino* tmpMino, Timer* timer){
	mino->fallCountTime += timer->GetDeltaTime();
	if (mino->fallCountTime > FALL_TIME) {
		mino->fallCountTime = 0.0f;

		//������Ȃ玩�R���������āC�t�B�[���h�X�V
		if (CanMove(mino, Dir::Down)) {
			MoveMino(mino, Dir::Down);
			UpdateField(tmpMino, BlockType::Background);
			UpdateField(mino, mino->minoType);			
		}
		//�����Ȃ��Ƃ������Ƃ͐ڒn����
		else {
			GroundMino(mino);
		}
	}
}

void GroundMino(Mino* mino) {

	//�~�m�̐F�B11�𑫂����R�F�Ⴆ��Z�~�m��BlockType��1�ɑΉ����邪�C
	//�u�ڒn���ꂽZ�~�m�v��12�ɑΉ�����悤�ɂ��ċ�ʂ���������
	int number = int(mino->minoType) + 11;

	//��ŋ��߂�������BlockType�^�ɒ���
	BlockType minoType = BlockType(number);

	//�ڒn�p�̃~�m�̔ԍ��Ńt�B�[���h���X�V
	UpdateField(mino, minoType);

	//�ڒn�����~�m�͏�����
	mino->InitMino();	
}