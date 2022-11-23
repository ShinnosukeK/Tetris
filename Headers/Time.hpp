#pragma once
#include "DxLib.h"

class Time {
private:
	static LONGLONG nowTime;//���t���[���̎���
	static LONGLONG time;//1�t���[���O�̎���
	static LONGLONG fpsCheckTime;//FPS�v���p�̃X�^�[�g����
	static float deltaTime;//�t���[���Ԃ̎���
	static int fps;
	static int fpsCount;//�o�߃t���[���𐔂��Ă������߂̕ϐ�
public:
	/// <summary>
	/// FPS���v���i���t���[���Ăяo�������邱�Ɓj
	/// </summary>
	static void CountFPS();

	/// <summary>
	/// FPS�̕\��
	/// </summary>
	static void DisplayFPS();

	static int FPS();
	static float DeltaTime();
};