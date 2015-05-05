#pragma once
// 绘图相关函数
#include <Windows.h>
#include <stdio.h>
class Entity;
void DrawString(int x, int y, CHAR str[]);
void DrawColumn(int x, int y, CHAR str[]);
void RepDrawColumn(int x, int y, int n, CHAR ch);
void DrawObject(Entity& obj);
void DrawScreen();

extern char _drawstring_buffer[];

#pragma warning(disable : 4996)
#define DrawString(x, y, ...) do {\
	sprintf(_drawstring_buffer, __VA_ARGS__);\
	WriteString(x, y, _drawstring_buffer);\
}while (0)

