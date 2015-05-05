#pragma once
#include <stdio.h>
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

class Entity
{
private:
	float offset;
	const char *image;
	const int *attr;
	bool toDel;
public:
	int scr_x, scr_y;
	int width, height;
	int vel;
	int dir;
	Entity(int x, int y, int w, int h, int v, char *img, int *attribute)
		:offset(0.0f), width(w), height(h), vel(v), image(img), attr(attribute), dir(STOP), toDel(false){}
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
		bool l = scr_x <= x;
		bool r = x < scr_x + width;
		bool u = scr_y <= y;
		bool d = y < scr_y + height;
		return l && r && u && d;
	}
	bool isInScreen();
	void del(void);

	// 读取函数
	int mid(void) const
	{
		return scr_x + width / 2;
	}
	int down(void) const
	{
		return scr_y + height - 1;
	}
	int up(void) const
	{
		return scr_y;
	}
	int left(void) const
	{
		return scr_x;
	}
	int right(void) const
	{
		return scr_x + width - 1;
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
	char getChar(int x, int y) const
	{
		return image[x - scr_x + (y - scr_y) * width];
	}
	bool isDel(void) const;
	const char *getImage(void) const
	{
		return image;
	}

	friend void DrawObject(Entity& obj);
	friend bool Collide(Entity &, Entity &);
	friend class Beam;
};

typedef Entity *PEntity;

class EntitySet
{
protected:
#define LEN 128
	PEntity entries[LEN];
	int size;
private:
	int index;
	int prev;
	int prev_index;
	bool deleteEntity(int i)
	{
		if (entries[i] == NULL)
			return false;
		delete entries[i];
		entries[i] = NULL;
		size--;
		return true;
	}
public:
	EntitySet(void) : size(0), index(0), prev(0), prev_index(0)
	{
		for (int i = 0; i < LEN; i++) {
			entries[i] = NULL;
		}
	}
	bool addNewEntity(Entity& x)
	{
		if (size == LEN)
			return false;

		for (int i = 0; i < LEN; i++) {
			if (entries[i] == NULL) {
				entries[i] = new Entity(x);
				size++;
				return true;
			}
		}

		return false;
	}
	void draw(void) const
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL) {
				entries[i]->draw();
			}
		}
	}
	void erase(void)
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && entries[i]->isDel()) {
				deleteEntity(i);
			}
		}
	}
	void move(void)
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && !entries[i]->move()) {
				deleteEntity(i);
			}
		}
	}
	void clear(void)
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL) {
				deleteEntity(i);
			}
		}
		size = 0;
	}
	int collide(Entity& obj)
	{
		int hitCount = 0;
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && obj.collide(*entries[i])) {
				obj.del();
				entries[i]->del();
				hitCount++;
			}
		}
		return hitCount;
	}
	int collide(EntitySet& s)
	{
		int count = 0;
		for (int i = 0; i < LEN; i++) {
			if (s.entries[i] != NULL) {
				count += collide(*(s.entries[i]));
			}
		}
		return count;
	}
	int getSize(void) const
	{
		return size;
	}
	PEntity getEntity(int i)
	{
		if (i >= size) 
			return NULL;
		if (prev == i)
			return entries[prev_index];
		else if (prev > i) {
			prev = i;
			prev_index = 0;
		}
		for (int j = prev_index; j < LEN; j++) {
			if (entries[j] != NULL) {
				i--;
				if (i < 0) {
					prev_index = j;
					return entries[prev_index];
				}
			}
		}
		return NULL;
	}
};