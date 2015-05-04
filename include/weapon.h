#pragma once

#include "entity.h"
#include <deque>
using std::deque;

class Beam
{
private:
	Entity ent;     // �洢ͼ�������
	char repImage;
	int color;
	int power;
	int atk;
	int width, height;
	Entity *owner;  // ������Ҫ���������ߵ�λ�����ƶ���ͬʱҲҪ�ݴ��ж�����Ȩ
public:
	Beam(char ch, int attr, int atk, int pow, Entity *obj);
	void update();
	void draw();
	void charge();
	int getPower() const;
	int attack(deque<Entity> &enemy);
};