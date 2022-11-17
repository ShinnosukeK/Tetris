#pragma once
#include "Mino.hpp"
#include "DxLib.h"
#include "Movement.hpp"
#define X_SIZE 12//x�����̃t�B�[���h�T�C�Y
#define Y_SIZE 21//y�����̃t�B�[���h�T�C�Y
#define LEFT_CORNER_POS 50//�`��̍��[
#define UP_CORNER_POS 50//�`��̏�[
#define MINO_SIZE 18//�u���b�N1�ӂ̒���
#define MINO_SIZE_ORIG 12//�u���b�N1�ӂ̌��̒���
extern int field[X_SIZE][Y_SIZE];//�t�B�[���h
extern double extRate;//�~�m�̊g�嗦

/// <summary>
/// �t�B�[���h������
/// </summary>
/// <param name="handle"></param>
/// <param name=""></param>
void InitField();

/// <summary>
/// �~�m�̈ʒu����field�̒l���X�V
/// </summary>
/// <param name="mino"></param>
/// <param name="tmpMino"></param>
void UpdateField(Mino mino, Mino tmpMino);

/// <summary>
/// �t�B�[���h�`��
/// </summary>
/// <param name="handle"></param>
void DrawField(int* handle);