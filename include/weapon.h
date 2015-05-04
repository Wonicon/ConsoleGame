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
	int attack(deque<Entity> enemy);
};

class Bullets
{
private:
	deque<Entity> entries;
	int  atk;
	float frequence;
	float accumulate;
	Entity &sample;
public:
	Bullets(int attack, float frequence, Entity &sample)
		:atk(attack), sample(sample), frequence(frequence), accumulate(0.0f){}
	void fire(int x, int y, int dir, int enableKey = 0)
	{
		accumulate += frequence * Fps.GetPast();
		if (enableKey == 0 && accumulate > 1.0f) {
			sample.setPos(x, y);
			sample.dir = dir;
			entries.push_back(sample);
			accumulate = 0.0f;
		}
		else if (accumulate > 1.0f && IsKeyPressed(enableKey)) {
			sample.setPos(x, y);
			sample.dir = dir;
			entries.push_back(sample);
			accumulate = 0.0f;
		}
	}
	void move()
	{
		deque<Entity>::iterator itr = entries.begin();
		while (itr != entries.end()) {
			if (itr->move()) itr++;
			else itr = entries.erase(itr);
		}
	}
	void erase()
	{
		deque<Entity>::iterator itr = entries.begin();
		while (itr != entries.end()) {
			if (!itr->isDel()) itr++;
			else itr = entries.erase(itr);
		}
	}
	void draw()
	{
		for (deque<Entity>::iterator itr = entries.begin(); itr != entries.end(); itr++) {
			itr->draw();
		}
	}
	void update() {
		erase();
		move();
	}
	deque<Entity>& Bullets::getEntry()
	{
		return entries;
	}
};