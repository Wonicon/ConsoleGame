#pragma once
#pragma comment( lib,"winmm.lib" )
class CFPS
{
public:
	CFPS(void);
	void UpdateFPS(void);  // 刷新时间
	float GetFps(void) { return fps; }
private:
	int startTime;   // 起始时间(ms)
	int lastTime;    // 上次更新的时间(ms)
	int nFrames;     // 总帧数
	int lastFrames;  // 上次更新的总帧数
	float fps;
	float past;
};