#pragma once
#include "Mino.hpp"
#include "Field.hpp"
#include "Time.hpp"
#define FALL_TIME 1.0f//自由落下の時間間隔

/// <summary>
/// 動く方向
/// </summary>
enum class Dir {
	Left,
	Down,
	Right,
};

/// <summary>
/// 回転方向
/// </summary>
enum class RotaDir {
	Clockwise,
	CounterClockwise,
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

/// <summary>
/// ミノを重力落下させる（フィールドの更新も同時にやってくれる）
/// </summary>
void Gravitate(Mino* mino, Mino* tmpMino, bool* isAnim);

/// <summary>
/// ミノを接地する
/// </summary>
void GroundMino(Mino* mino, bool* isDeleted);

/// <summary>
/// ミノを回転する
/// </summary>
void RotaMino(Mino* mino, Mino* tmpMino, RotaDir d);