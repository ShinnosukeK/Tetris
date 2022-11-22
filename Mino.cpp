#include "Mino.hpp"
#include "DxLib.h"

void Mino::InitMino() {

	//�����o�̏�����
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

	//�~�m�̎�ށi7��ށj������
	int randomNumber = rand() % 7 + 1;//������1~7����I��
	this->minoType = BlockType(randomNumber);//�����Ɋ�Â��ă~�m�̎�ށiBlockType�j������

	//�~�m�̈ʒu������
	UpdateLocalBlockPosition();
	UpdateWorldBlockPosition();
}

void Mino::UpdateLocalBlockPosition() {

	int k = 0;
	
	//�~�m�̎��(1~7)���擾�B
	//1�������̂́Cshape�s���1�����ڂ�0~6�Ŏw�肷�邽��
	int type = int(minoType) - 1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			//�~�m�̏�Ԃ�\���s��ishape[*][*][4][4]�j�̐����̂����C
			//None�ł͂Ȃ��ꍇ�́i���~�m�̃u���b�N���������炠��ꍇ�́j
			if (this->shape[type][this->rotState][i][j] != int(BlockType::None)) {
				
				//�~�m�̃u���b�N���L�q����Ă��镔�������[�J�����W�Ƃ��ĕۑ�
				this->localPos[k].x = i;
				this->localPos[k].y = j;

				//1�~�m�ɂ�4�u���b�N���邩��Ck=3�܂ő����ł����痣�E
				if (k == 3)break;
				k++;
			}

		}
	}
}

void Mino::UpdateWorldBlockPosition() {	
	for (int i = 0; i < 4; i++) {

		//���[���h���W�́C�~�m�̒��S��\�������̍��W�Ƀ��[�J�����W�������ē���
		this->worldPos[i].x = this->centerPos.x + this->localPos[i].x;
		this->worldPos[i].y = this->centerPos.y + this->localPos[i].y;
	}	
}

//�R���X�g���N�^
Mino::Mino() {

	//�~�m�̔z�u��\�����̂Ƃ��āC
	//�G�I�ɐ�����������s��reversedShape[*][*][4][4]
	//�͂��̂܂�reversedShape[*][*][x][y]�̂悤�ȃC���[�W�ŕ`�悷���
	//�s�Ɨ񂪔��]���Ă��܂��̂ŁC�����œ]�u����shape[*][*][4][4]�ɑ��
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