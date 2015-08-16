#include <Windows.h>
#include "fps.h"
#pragma comment( lib,"winmm.lib" )

static int startTime;   // 起始时间(ms)
static int lastTime;    // 上次更新的时间(ms)
static int nFrames;     // 总帧数
static int lastFrames;  // 上次更新的总帧数
static float past;      // 从上一次 UpdateFps 到这一次 UpdateFps 经过的时间
static float fps;

void InitFps(void)
{
	nFrames = 0;
	lastFrames = 0;
	lastTime = 0;
	startTime = timeGetTime();
	fps = 0.0f;
	past = 0.0f;
}

void UpdateFps(void)
{
	nFrames++;
	int currentTime = timeGetTime();
	static int prevTime = currentTime;
	past = (currentTime - prevTime) / 1000.0f;
	prevTime = currentTime;

	// 一秒钟更新一次 Fps
	if (currentTime - lastTime > 1000)
	{
		float slot = (currentTime - lastTime) / 1000.0f;
		fps = float(nFrames - lastFrames) / slot;
		lastTime = currentTime;
		lastFrames = nFrames;
	}
}

float GetFps(void)
{
	return fps;
}

float GetPast(void)
{
	return past;
}

// 频率锁, 顺便直接使用 past 提高效率
// 但是往往不只是积累够了就能清零，而是要保证允许其它事件触发
// 所以使用clear使能，同时只有在clear使能有效时才是真的有效
bool FreqLock(float &current, float freq, bool clear)
{
	if (current > 1.0f) {
		if (clear) current = 0.0f;
		return clear;
	}
	else {
		current += past * freq;
		return false;
	}
}