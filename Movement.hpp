#pragma once
#include "Mino.hpp"
#include "Field.hpp"


/// <summary>
/// ��������
/// </summary>
enum class Dir {
	Left,
	Down,
	Right,
};


/// <summary>
/// �~�m���������邩�ǂ����̃`�F�b�N
/// </summary>
/// <returns></returns>
bool CanMove(Mino* p, Dir d);

/// <summary>
/// �~�m�𓮂���
/// </summary>
void MoveMino(Mino* p, Dir d);

/// <summary>
/// �~�m�̏ꏊ���O����ς�������ǂ����̃`�F�b�N
/// </summary>
bool IsMinoPosChanged(Mino* mino, Mino* tmpMino);