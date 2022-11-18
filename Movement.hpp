#pragma once
#define FALL_TIME 1.0f//���R�����̎��ԊԊu
#include "Mino.hpp"
#include "Field.hpp"
#include "Timer.hpp"



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

/// <summary>
/// �~�m���d�͗���������
/// </summary>
void Gravitate(Mino* mino, Timer* timer);