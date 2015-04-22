﻿#ifndef __OBJ_H__
#define __OBJ_H__
#include <windows.h>
#include <assert.h>
#include <string.h>
#include "console.h"
#include "event.h"

class Object {
private:
	int x;
	int y;
	int width;
	int height;
	int speed;
	int life;
#define BUFFER_MAX (1008)
	char image[BUFFER_MAX];
public:
	Object(COORD &position, COORD &scale, char s[], int v, int life);
	Object(const Object& obj);
	void Move(int xx, int yy)
	{
		x += xx;
		y += yy;
	}
	void SetPos(int xx, int yy)
	{
		x = xx;
		y = yy;
	}
	void Die()
	{
		life = 0;
	}
	bool RangeLimit();
	// 给定窗口的坐标和大小，判断对象是否在窗口内
	bool isInWindow(COORD pos, COORD windows);
	bool isAlive()
	{
		return life > 0;
	}
	COORD getPos() const  {
		COORD pos = { x, y };
		return pos;
	}
	COORD getSize() const { 
		COORD ret = { width, height };
		return ret;
	}
	friend void DrawObject(Object& obj);
};
#endif