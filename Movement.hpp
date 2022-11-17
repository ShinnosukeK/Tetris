#pragma once
#include "Mino.hpp"
#include "Field.hpp"


/// <summary>
/// 動く方向
/// </summary>
enum class Dir {
	Left,
	Down,
	Right,
};


/// <summary>
/// ミノが動かせるかどうかのチェック
/// </summary>
/// <returns></returns>
bool CanMove(Mino* p, Dir d);

/// <summary>
/// ミノを動かす
/// </summary>
void MoveMino(Mino* p, Dir d);

/// <summary>
/// ミノの場所が前から変わったかどうかのチェック
/// </summary>
bool IsMinoPosChanged(Mino* mino, Mino* tmpMino);