#ifndef __DRAW_H__
#define __DRAW_H__

// 绘图相关函数
#include <Windows.h>

#define DEFAULT_ATTR \
(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED)

class Object;
void DrawString(int x, int y, const char *str);
void DrawColumn(int x, int y, const char *str);
void RepDrawColumn(int x, int y, int n, char ch);
void DrawObject(Object& obj);
void DrawScreen();
#endif