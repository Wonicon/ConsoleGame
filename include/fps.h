#pragma once
#pragma comment( lib,"winmm.lib" )
class CFPS
{
public:
	CFPS(void);
	void UpdateFPS(void);  // ˢ��ʱ��
	float GetFps(void) { return fps; }
private:
	int startTime;   // ��ʼʱ��(ms)
	int lastTime;    // �ϴθ��µ�ʱ��(ms)
	int nFrames;     // ��֡��
	int lastFrames;  // �ϴθ��µ���֡��
	float fps;
	float past;
};