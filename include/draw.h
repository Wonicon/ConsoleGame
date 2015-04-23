#pragma once
// 绘图相关函数
#include <Windows.h>

class Entity;
void DrawString(int x, int y, CHAR str[]);
void DrawColumn(int x, int y, CHAR str[]);
void RepDrawColumn(int x, int y, int n, CHAR ch);
void DrawObject(Entity& obj);
void DrawScreen();