#pragma once
#include "Mino.hpp"
#include "DxLib.h"
#include "Movement.hpp"
#define X_SIZE 12//x方向のフィールドサイズ
#define Y_SIZE 21//y方向のフィールドサイズ
#define LEFT_CORNER_POS 50//描画の左端
#define UP_CORNER_POS 50//描画の上端
#define MINO_SIZE 18//ブロック1辺の長さ
#define MINO_SIZE_ORIG 12//ブロック1辺の元の長さ
extern int field[X_SIZE][Y_SIZE];//フィールド
extern double extRate;//ミノの拡大率

/// <summary>
/// フィールド初期化
/// </summary>
/// <param name="handle"></param>
/// <param name=""></param>
void InitField();

/// <summary>
/// ミノの位置からfieldの値を更新
/// </summary>
/// <param name="mino"></param>
/// <param name="tmpMino"></param>
void UpdateField(Mino mino, Mino tmpMino);

/// <summary>
/// フィールド描画
/// </summary>
/// <param name="handle"></param>
void DrawField(int* handle);