#include "Field.hpp"

int field[X_SIZE][Y_SIZE];//�t�B�[���h
int tmpField[X_SIZE][Y_SIZE];//���u���p�̃t�B�[���h
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

void UpdateFieldOnDelete(bool* deleteFlag) {

	//�t���O�������Ă���s�������ׂĔw�i�ɂ���
	for (int _y = 0; _y <= 18; _y++) {
		if (deleteFlag[_y] == true) {
			//y=1~19���Ֆ�
			int y = _y + 1;

			//x=1~10���Ֆ�
			for (int x = 1; x <= 10; x++) {
				field[x][y] = int(BlockType::Background);
			}
		}
	}

	//�A�j���[�V�����Ƃ��ċ@�\�����邽�߁Cfield����U�͒��ڂ����炸�CtmpField�ɕۑ����Ă���
	for (int i = 0; i < X_SIZE; i++) {
		for (int j = 0; j < Y_SIZE; j++) {
			tmpField[i][j] = field[i][j];
		}
	}

	//���������C�S�̂����ɃV�t�g������
	for (int y = 18; y >= 1; y--) {

		int count = 0;

		//y�s�ڂ������̍s�ŉ��s�����������J�E���g
		for (int _y = y; _y <= 18 ; _y++) {
			if (deleteFlag[_y]) {
				count++;
			}			
		}

		//�J�E���g�����݂���΃V�t�g������
		if (count != 0) {
			for (int x = 1; x <= 10; x++) {

				//y�s�ڂ�count���������ɂ��炷
				tmpField[x][y + count] = tmpField[x][y];

				//�ړ����Ă��܂���y�s�ڂ͈�U�w�i�ɂ���
				tmpField[x][y] = int(BlockType::Background);
			}
		}
	}
	
	
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

bool CanDeleteLine() {

	//�������C�������݂��邩�ǂ����̃t���O
	bool canDelete = false;

	//�������C����ۑ����邽�߂̃t���O
	bool deleteFlag[19] = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,
	};

	int y = 0;

	//�����郉�C������
	//deleteFlag��_y=0~18������
	for (int _y = 0; _y <= 18; _y++) {

		//�����Ώۂ�y=1~19�̍s
		y = _y + 1;

		//�����Ώۂ�x=1~10�̗�
		for (int x = 1; x <= 10; x++) {
			//��s���ׂĂ������ň��ł��w�i������ꍇ�͏����ł��Ȃ����ƂɂȂ�
			if (field[x][y] == int(BlockType::Background))
			{
				deleteFlag[_y] = false;
			}
		}

		//1�s�ł��������C��������΁C������t���O������
		canDelete = canDelete || deleteFlag[_y];
	}

	return canDelete;
}

void DeleteLine() {

	//�������C����ۑ����邽�߂̃t���O
	bool deleteFlag[19] = {
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,1,
		1,1,1,1,
	};

	int y = 0;

	//�����郉�C������
	//deleteFlag��_y=0~18������
	for (int _y = 0; _y <= 18; _y++) {

		//�����Ώۂ�y=1~19�̍s
		y = _y + 1;

		//�����Ώۂ�x=1~10�̗�
		for (int x = 1; x <= 10; x++) {
			//��s���ׂĂ������ň��ł��w�i������ꍇ�͏����ł��Ȃ����ƂɂȂ�
			if (field[x][y] == int(BlockType::Background))
			{
				deleteFlag[_y] = false;
			}
		}
	}

	//���C�����������Ƃɂ��t�B�[���h�̍X�V
	UpdateFieldOnDelete(deleteFlag);
}