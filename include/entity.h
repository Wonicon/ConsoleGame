#pragma once

#include <windows.h>
#include <assert.h>
#include <string.h>
#include "console.h"
#include "event.h"

#define STOP 0
#define CONS (1 << 4)
#define U 8
#define D 4
#define L 2
#define R 1
#define UL (U | L)
#define UR (U | R)
#define DL (D | L)
#define DR (D | R)

class Entity {
private:
	float real_x, real_y;
	int scr_x, scr_y;
	int width, height;
	int life;
	int max_life;
	int atk;
#define BUFFER_MAX (128)
	char image[BUFFER_MAX];
	int attr[BUFFER_MAX];
public:
	int vel;
	int dir;
	Entity(int x, int y, int w, int h, int v, int hp, int attack, char img[], int attribute[]);
	// 根据自身状态移动，返回是否超出屏幕边界
	bool move(int new_dir = CONS);
	void setPos(int x, int y)
	{
		real_x = (float)(scr_x = x);
		real_y = (float)(scr_y = y);
	}
	void die()
	{
		life = 0;
	}
	bool rangeLimit();
	// 给定窗口的坐标和大小，判断对象是否在窗口内
	bool isInWindow(int x0, int y0, int w, int h);
	bool isHitWindow(int x0, int y0, int w, int h);
	bool isAlive()
	{
		return life > 0;
	}
	void getPos(int &x, int &y) const
	{
		x = scr_x;
		y = scr_y;
	}
	void getSize(int &w, int &h) const
	{
		w = width;
		h = height;
	}
	int getLife(void) const
	{
		return life;
	}
	void hurt(void) { life--; }
	void hurt(int atk)
	{
		life -= atk;
	}
	void hurt(Entity &enemy)
	{
		life -= enemy.atk;
	}
	void heal(int recover)
	{
		life = (life + recover) % max_life;
	}
	const char *getImage(void)
	{
		return image;
	}
	char getChar(int x, int y) const
	{
		return image[x + y * width];
	}
	bool isInImage(int x, int y) const
	{
		bool a1 = scr_x <= x;
		bool a2 = x < scr_x + width;
		bool a3 = scr_y <= y;
		bool a4 = y < scr_y + height;
		return a1 && a2 && a3 && a4 && getChar(x, y) != JMP_CHAR;
	}
	friend void DrawObject(Entity& obj);
	friend bool Collide(Entity &, Entity &);
};

