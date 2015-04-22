#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <Windows.h>

#define INPUT_CHAR AsciiChar
#define JMP_CHAR ' '
#define WIDTH 80
#define SCREEN_WIDTH 60
#define HEIGHT 40
#define TITLE "Console Invader"
#define BOUNDARY_CHECK(x, y)\
	(0 <= x && x < WIDTH && 0 <= y && y < HEIGHT)

/* 涉及系统功能 */
void InitConsole(void);
bool IsWindowActive(void);
void RedrawConsole(void);
/* 只在缓冲区上操作的函数 */
// 清空缓冲区，清空行为不会立即反应在屏幕上，只是为后面完全重绘做准备
void ClearConsoleBuffer(void);
// 下面的写入缓冲区函数与 draw*函数 在功能上大体相当，但是参数更多
// 多样的形式在 draw*函数里设定
void WriteChar(COORD pos, CHAR_INFO ch);
void WriteString(int x, int y, const char *str, int len, int attr);
void WriteColumn(int x, int y, const char *str, int len, int attr);
void WriteBlock(COORD pos, COORD size, CHAR_INFO str[]);
void ModifyAttribute(COORD pos, int attr);


#endif