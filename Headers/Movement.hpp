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
bool CanMove(const Mino& p, Dir d);

/// <summary>
/// ミノを動かす
/// </summary>
void MoveMino(Mino* p, Dir d);

/// <summary>
/// ミノの場所が前から変わったかどうかのチェック
/// </summary>
bool IsMinoPosChanged(const Mino& mino, const Mino& tmpMino);

/// <summary>
/// ミノを重力落下させる（フィールドの更新も同時にやってくれる）
/// </summary>
void Gravitate(Mino* mino, bool* isAnim);

/// <summary>
/// ミノを接地する
/// </summary>
void GroundMino(Mino* mino, bool* isDeleted);

/// <summary>
/// ミノを回転できるかどうか
/// </summary>
bool CanRota(const Mino& mino, RotaDir d);

/// <summary>
/// ミノを回転する
/// </summary>
void RotaMino(Mino* mino, RotaDir d);