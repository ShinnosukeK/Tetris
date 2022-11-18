#pragma once
#include "DxLib.h"

class Timer {
private:
	LONGLONG nowTime;//���t���[���̎���
	LONGLONG time;//1�t���[���O�̎���
	LONGLONG fpsCheckTime;//FPS�v���p�̃X�^�[�g����
	float deltaTime;//�t���[���Ԃ̎���
	int fps;
	int fpsCount;//�o�߃t���[���𐔂��Ă������߂̕ϐ�

public:
	/// <summary>
	/// �^�C�}�[�̏�����
	/// </summary>
	void InitTimer();

	/// <summary>
	/// FPS���v���i���t���[���Ăяo�������邱�Ɓj
	/// </summary>
	void CountFPS();

	int GetFPS();
	float GetDeltaTime();
};

