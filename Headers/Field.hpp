#pragma once
#include "Mino.hpp"
#include "DxLib.h"
#define X_SIZE 12//x方向のフィールドサイズ
#define Y_SIZE 21//y方向のフィールドサイズ
#define LEFT_CORNER_POS 50//描画の左端
#define UP_CORNER_POS 50//描画の上端
#define MINO_SIZE 18//ブロック1辺の長さ
#define MINO_SIZE_ORIG 12//ブロック1辺の元の長さ
extern int field[X_SIZE][Y_SIZE];//フィールド
extern int tmpField[X_SIZE][Y_SIZE];//仮置き用のフィールド
extern double extRate;//ミノの拡大率

/// <summary>
/// フィールド初期化
/// </summary>
/// <param name="handle"></param>
/// <param name=""></param>
void InitField();

/// <summary>
/// ミノの位置からフィールド更新
/// </summary>
void UpdateField(const Mino& mino, BlockType type);

/// <summary>
/// 移動に際してのフィールド更新を行う
/// </summary>
void UpdateFieldOnMove(const Mino& mino, const Mino& tmpMino);

/// <summary>
/// 消去するフラグからフィールド更新
/// </summary>
/// <param name="deleteFlag"></param>
void UpdateFieldOnDelete(bool* deleteFlag);

/// <summary>
/// フィールド描画
/// </summary>
/// <param name="handle"></param>
void DrawField(int* handle);

/// <summary>
/// ラインを消せるかどうかのフラグ
/// </summary>
bool CanDeleteLine();

/// <summary>
/// ラインを消す
/// </summary>
void DeleteLine();