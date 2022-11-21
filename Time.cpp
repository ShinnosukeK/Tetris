#include "Time.hpp"

//static�ϐ��̏�����
LONGLONG Time::nowTime = 0;
LONGLONG Time::time = 0;
LONGLONG Time::fpsCheckTime = 0;
float Time::deltaTime = 0.0f;
int Time::fps = 0;
int Time::fpsCount = 0;


void Time::CountFPS() {

	//�������ۑ�
	Time::nowTime = GetNowHiPerformanceCount();
	
	//�o�ߎ��Ԍv��
	Time::deltaTime = (Time::nowTime - Time::time) / 1000000.0f;

	//���̃t���[���Ŏg��������Ƃ��ĕۑ�	
	Time::time = Time::nowTime;

	Time::fpsCount++;

	//������-�v���J�n������1s�𒴂�����
	if (Time::nowTime - Time::fpsCheckTime > 1000000) {

		//FPS������
		Time::fps = Time::fpsCount;		

		//FPS�v���ϐ������Z�b�g
		Time::fpsCount = 0;

		//�����FPS�v���̍ۂ̊����
		Time::fpsCheckTime = Time::nowTime;
	}
}

int Time::FPS() {
	return Time::fps;
}

float Time::DeltaTime() {
	return Time::deltaTime;
}