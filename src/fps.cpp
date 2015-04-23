#include <Windows.h>
#include "fps.h"

CFPS::CFPS(void)
{
	nFrames = 0;
	lastFrames = 0;
	lastTime = 0;
	startTime = timeGetTime();
}

void CFPS::UpdateFPS(void)
{
	nFrames++;
	int currentTime = timeGetTime();
	static int prevTime = currentTime;
	past = (currentTime - prevTime) / 1000.0f;
	prevTime = currentTime;

	if (currentTime - lastTime > 1000)
	{
		float slot = (currentTime - lastTime) / 1000.0f;
		fps = float(nFrames - lastFrames) / slot;
		lastTime = currentTime;
		lastFrames = nFrames;

	}
}