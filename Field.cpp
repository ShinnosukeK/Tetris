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


void UpdateField(Mino* mino, BlockType type) {
	for (int i = 0; i < 4; i++) {
		//�󂯎�����~�m�̃��[���h���W�̈ʒu�̃t�B�[���h���C�󂯎�����F�ɂ���
		field[mino->worldPos[i].x][mino->worldPos[i].y] = int(type);
	}
};

void UpdateFieldOnMove(Mino* mino, Mino* tmpMino) {

	//��Ɉړ��O�̃~�m�ɓ�����t�B�[���h��w�i�ɍX�V
	UpdateField(tmpMino, BlockType::Background);

	//��Ɉړ���̃~�m�ɓ�����t�B�[���h�����̃~�m�̐F�ɍX�V�B
	//����͋t�ɂ���ƃ~�m�������w�i�ɓh����̂Œ��ӁB
	UpdateField(mino, mino->minoType);
}


void DrawField(int* handle) {
	for (int j = 0; j < Y_SIZE; j++) {
		for (int i = 0; i < X_SIZE; i++) {
			//�X�^�[�g�̕`��ꏊ�����߁C��������~�m�T�C�Y���������炵�Ȃ���`�悷��
			DrawRotaGraph(
				LEFT_CORNER_POS + MINO_SIZE * i,
				UP_CORNER_POS + MINO_SIZE * j,
				extRate, 0.0f, handle[field[i][j] - 1], TRUE);
		}
	}
}