#include "Timer.hpp"

void Timer::InitTimer() {
	time = GetNowHiPerformanceCount();//�Q�[�����[�v�ɓ���O�̎����ۑ�
	fpsCheckTime = GetNowHiPerformanceCount();//�����FPS�v���̍ۂ̊����
	fps = 0;
	fpsCount = 0;
	deltaTime = 0.000001f;//���̒l
}

void Timer::CountFPS() {

	//�������ۑ�
	nowTime = GetNowHiPerformanceCount();
	
	//�o�ߎ��Ԍv��
	deltaTime = (nowTime - time) / 1000000.0f;

	//���̃t���[���Ŏg��������Ƃ��ĕۑ�	
	time = nowTime;

	fpsCount++;

	//������-�v���J�n������1s�𒴂�����
	if (nowTime - fpsCheckTime > 1000000) {

		//FPS������
		fps = fpsCount;		

		//FPS�v���ϐ������Z�b�g
		fpsCount = 0;

		//�����FPS�v���̍ۂ̊����
		fpsCheckTime = nowTime;
	}
}

int Timer::GetFPS() {
	return this->fps;
}

float Timer::GetDeltaTime() {
	return this->deltaTime;
}