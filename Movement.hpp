#pragma once
#define FALL_TIME 1.0f//自由落下の時間間隔
#include "Mino.hpp"
#include "Field.hpp"
#include "Timer.hpp"



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
/// ミノを重力落下させる
/// </summary>
void Gravitate(Mino* mino, Timer* timer);