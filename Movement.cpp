#include "Movement.hpp"

bool CanMove(Mino* p, Dir d) {

	//�����̃~�m�𕡐�
	Mino futureMino = *p;

	//���������~�m�����z�I�ɓ������Ă݂�
	MoveMino(&futureMino, d);
	
	//���z�I�ɓ��������~�m���\������4�u���b�N�̂����C�ŏ���x���W�����u���b�N�̃��[���h���W���擾
	Pos minXPos = futureMino.GetMinXBlockPosition();

	//���z�I�ɓ��������~�m���\������4�u���b�N�̂����C�ő��x���W�����u���b�N�̃��[���h���W���擾
	Pos maxXPos = futureMino.GetMaxXBlockPosition();

	//���z�I�ɓ��������~�m���\������4�u���b�N�̂����C�ő��y���W�����u���b�N�̃��[���h���W���擾
	Pos maxYPos = futureMino.GetMaxYBlockPosition();

	//��{�͓�������Ƃ��ăt���O�𗧂ĂĂ���
	bool flag = true;

	//�ړ��ł��邩
	switch (d) {
	case Dir::Left:
		//�u�ŏ���x���W�����u���b�N�v�̈ʒu���w�i�ȊO�̂��̂��ƁC�u���ɂ́v�������Ȃ����ƂɂȂ�
		if (field[minXPos.x][minXPos.y] != (int)BlockType::Background) {
			flag = false;			
		}
		break;
	case Dir::Down:
		//�u�ő��y���W�����u���b�N�v�̈ʒu���w�i�ȊO�̂��̂��ƁC�u���ɂ́v�������Ȃ����ƂɂȂ�
		if (field[maxYPos.x][maxYPos.y] != (int)BlockType::Background) {
			flag = false;
		}
		break;
	case Dir::Right:
		//�u�ő��x���W�����u���b�N�v�̈ʒu���w�i�ȊO�̂��̂��ƁC�u�E�ɂ́v�������Ȃ����ƂɂȂ�
		if (field[maxXPos.x][maxXPos.y] != (int)BlockType::Background) {
			flag = false;			
		}
		break;
	}
	
	return flag;

}

void MoveMino(Mino* p, Dir d) {

	//Dir�̕����ɉ����āC1�~�m���\������4�u���b�N�̃��[���h���W�����ׂĕω�������
	switch (d) {
	case Dir::Left:
		for (int i = 0; i < 4; i++) {
			//���͂����Ȃ�Cx���W������
			p->worldPos[i].x -= 1;
		}
		break;

	case Dir::Down:
		for (int i = 0; i < 4; i++) {
			//���͂����Ȃ�Cy���W�𑝉�
			p->worldPos[i].y += 1;
		}
		break;

	case Dir::Right:
		for (int i = 0; i < 4; i++) {
			//���͂��E�Ȃ�Cx���W�𑝉�
			p->worldPos[i].x += 1;
		}
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