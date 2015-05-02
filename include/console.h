#pragma once
#include <Windows.h>

#define COLOR
#define JMP_CHAR ' '
#define WIDTH 80
#define SCREEN_WIDTH 60
#define HEIGHT 35
#define SCREEN_HEIGHT 35
#define TITLE "Ascii Shooter"
#define BOUNDARY_CHECK(x, y) (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)

typedef char CHAR;

/* 涉及系统功能 */
void InitConsole(void);
bool IsWindowActive(void);
void RedrawConsole(void);
/* 只在缓冲区上操作的函数 */
// 清空缓冲区，清空行为不会立即反应在屏幕上，只是为后面完全重绘做准备
void ClearConsoleBuffer(void);
// 各种输出函数
void WriteString(int x, int y, CHAR str[]);
void WriteColumn(int x, int y, CHAR str[]);
#ifndef COLOR
void WriteBlock(int x, int y, int height, int width, CHAR str[]);
#else
void WriteBlock(int x, int y, int height, int width, CHAR str[], int attr[]);
#endif

