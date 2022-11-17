#include "Field.hpp"

int field[X_SIZE][Y_SIZE];//�t�B�[���h
double extRate = double(MINO_SIZE) / MINO_SIZE_ORIG;//�~�m�̊g�嗦

void InitField() {

	//������ԂɃt�B�[���h�X�V
	for (int i = 0; i < Y_SIZE; i++) {
		for (int j = 0; j < X_SIZE; j++) {
			//�ō���or�ŉE��Ȃ��
			if (j == 0 || j == X_SIZE - 1) {
				field[j][i] = int(BlockType::Wall);
			}
			//����ȊO�̗�Ȃ�w�i
			else {
				field[j][i] = int(BlockType::Background);
			}
			//�ŏ�s�͋󔒂ɂ������̂ŏ㏑��
			if (i == 0) {
				field[j][i] = int(BlockType::Black);
			}
			//�ŉ��s�Ȃ�ǂȂ̂ŏ㏑��
			if (i == Y_SIZE - 1) {
				field[j][i] = int(BlockType::Wall);
			}			
		}

	}
}


void UpdateField(Mino mino, Mino tmpMino) {
	for (int i = 0; i < 4; i++) {

		//�O�̃~�m�̈ʒu���ω����Ă����ꍇ
		if (IsMinoPosChanged(&mino, &tmpMino)) {
			//���̃~�m�������ꏊ�͔w�i�ɂ���
			field[tmpMino.worldPos[i].x][tmpMino.worldPos[i].y] = int(BlockType::Background);
		}

		//�ŐV�̃~�m�̈ʒu���X�V����
		field[mino.worldPos[i].x][mino.worldPos[i].y] = int(mino.minoType);
	}
};


void DrawField(int* handle) {
	for (int j = 0; j < Y_SIZE; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			//�X�^�[�g�̕`��ꏊ�����߁C��������~�m�T�C�Y���������炵�Ȃ���`�悷��
			DrawRotaGraph(
				LEFT_CORNER_POS + MINO_SIZE * i,
				UP_CORNER_POS + MINO_SIZE * j,
				extRate, 0.0f, handle[int(field[i][j]) - 1], TRUE);
		}
	}
}