#pragma once

// 重要，是fps相关函数功能正确的关键，刷新时间，确保在每次循环都执行一次
void UpdateFps(void);

// 获得FPS
float GetFps(void);

// 重要，获得上一帧经过的时间，是时间控制的关键
float GetPast(void);

// 重要，频率控制的关键
bool FreqLock(float &current, float freq, bool clear);

void InitFps(void);