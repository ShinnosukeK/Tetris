#pragma once
#include "Mino.hpp"
#include "DxLib.h"
#define X_SIZE 12//x�����̃t�B�[���h�T�C�Y
#define Y_SIZE 21//y�����̃t�B�[���h�T�C�Y
#define LEFT_CORNER_POS 50//�`��̍��[
#define UP_CORNER_POS 50//�`��̏�[
#define MINO_SIZE 18//�u���b�N1�ӂ̒���
#define MINO_SIZE_ORIG 12//�u���b�N1�ӂ̌��̒���
extern int field[X_SIZE][Y_SIZE];//�t�B�[���h
extern int tmpField[X_SIZE][Y_SIZE];//���u���p�̃t�B�[���h
extern double extRate;//�~�m�̊g�嗦

/// <summary>
/// �t�B�[���h������
/// </summary>
/// <param name="handle"></param>
/// <param name=""></param>
void InitField();

/// <summary>
/// �~�m�̈ʒu����t�B�[���h�X�V
/// </summary>
void UpdateField(const Mino& mino, BlockType type);

/// <summary>
/// �ړ��ɍۂ��Ẵt�B�[���h�X�V���s��
/// </summary>
void UpdateFieldOnMove(const Mino& mino, const Mino& tmpMino);

/// <summary>
/// ��������t���O����t�B�[���h�X�V
/// </summary>
/// <param name="deleteFlag"></param>
void UpdateFieldOnDelete(bool* deleteFlag);

/// <summary>
/// �t�B�[���h�`��
/// </summary>
/// <param name="handle"></param>
void DrawField(int* handle);

/// <summary>
/// ���C���������邩�ǂ����̃t���O
/// </summary>
bool CanDeleteLine();

/// <summary>
/// ���C��������
/// </summary>
void DeleteLine();