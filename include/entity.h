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

#define BUFFER_MAX (128)

class Entity {
private:
	int scr_x, scr_y;
	int life;
	int max_life;
	float offset;
	char image[BUFFER_MAX];
	int attr[BUFFER_MAX];
public:
	int vel;
	int dir;
	int width, height;
	Entity(int x, int y, int w, int h, int v, int hp, int attack, char img[], int attribute[]);

	/*******************************************
	  实体相关
	 *******************************************/
	void draw();
	bool collide(Entity &obj);
	void setPos(int x, int y)
	{
		scr_x = x;
		scr_y = y;
	}
	// 根据自身状态移动，返回是否超出屏幕边界
	bool move(int new_dir = CONS);
	// 给定窗口的坐标和大小，判断对象是否在窗口内
	bool isInWindow(int x0, int y0, int w, int h);
	// 给定窗口的坐标和大小，判断实体是否与窗口相交
	bool isHitWindow(int x0, int y0, int w, int h);
	bool isInImage(int x, int y) const
	{

		bool a1 = scr_x <= x;
		bool a2 = x < scr_x + width;
		bool a3 = scr_y <= y;
		bool a4 = y < scr_y + height;
		return a1 && a2 && a3 && a4 && getChar(x, y) != JMP_CHAR;
	}

	/**********************************************
	  RPG 内容
	 **********************************************/
	// 判断实体是否存活
	int  getLife(void) const
	{
		return life;
	}
	bool isAlive()
	{
		return life > 0;
	}
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
	void die()
	{
		life = 0;
	}

	// 读取函数
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
	char getChar(int x, int y) const
	{
		return image[x + y * width];
	}
	bool rangeLimit();
	const char *getImage(void) const
	{
		return image;
	}

	friend void DrawObject(Entity& obj);
	friend bool Collide(Entity &, Entity &);
};

