#pragma once
#include "Mino.hpp"
#include "Field.hpp"
#include "Time.hpp"
#define FALL_TIME 1.0f//���R�����̎��ԊԊu

/// <summary>
/// ��������
/// </summary>
enum class Dir {
	Left,
	Down,
	Right,
};

/// <summary>
/// ��]����
/// </summary>
enum class RotaDir {
	Clockwise,
	CounterClockwise,
};

/// <summary>
/// �~�m���������邩�ǂ����̃`�F�b�N
/// </summary>
/// <returns></returns>
bool CanMove(const Mino& p, Dir d);

/// <summary>
/// �~�m�𓮂���
/// </summary>
void MoveMino(Mino* p, Dir d);

/// <summary>
/// �~�m�̏ꏊ���O����ς�������ǂ����̃`�F�b�N
/// </summary>
bool IsMinoPosChanged(const Mino& mino, const Mino& tmpMino);

/// <summary>
/// �~�m���d�͗���������i�t�B�[���h�̍X�V�������ɂ���Ă����j
/// </summary>
void Gravitate(Mino* mino, bool* isAnim);

/// <summary>
/// �~�m��ڒn����
/// </summary>
void GroundMino(Mino* mino, bool* isDeleted);

/// <summary>
/// �~�m����]�ł��邩�ǂ���
/// </summary>
bool CanRota(const Mino& mino, RotaDir d);

/// <summary>
/// �~�m����]����
/// </summary>
void RotaMino(Mino* mino, RotaDir d);