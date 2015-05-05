#pragma once

#include "entity.h"
#include <deque>
using std::deque;

class Beam
{
private:
	Entity ent;     // Entity不承担画图任务，只是一个判定点组件
	float power;
	float maxPower;
	int attack;
	int attribute;
	char BeamCharBuffer[SCREEN_HEIGHT];
	int BeamAttrBuffer[SCREEN_HEIGHT];
public:
	Beam(int attr, int attack, int power, int width);
	void fire(int x, int y, int dir);         // 形成射线判定，同时消耗能量
	void draw();                     // 画射线，最好在fire之后调用
	void charge(float n);            // 充能
	/**********************/
	float getPower() const;          // 获得能量
	int getAtk() const;              // 获得攻击力
	Entity &getJudge(void);

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
		if (enableKey == 0) {
			sample.setPos(x, y);
			sample.dir = dir;
			entries.push_back(sample);
		}
		else if (IsKeyPressed(enableKey)) {
			sample.setPos(x, y);
			sample.dir = dir;
			entries.push_back(sample);
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

void VShooter(int, int);