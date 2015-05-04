#pragma once

#include "entity.h"
#include <deque>
using std::deque;

class Beam
{
private:
	Entity ent;     // 存储图像等内容
	char repImage;
	int color;
	int power;
	int atk;
	int width, height;
	Entity *owner;  // 激光需要根据所有者的位置来移动，同时也要据此判断所有权
public:
	Beam(char ch, int attr, int atk, int pow, Entity *obj);
	void update();
	void draw();
	void charge();
	int getPower() const;
	int attack(deque<Entity> &enemy);
};