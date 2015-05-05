#pragma once

#include "entity.h"
#include <deque>
using std::deque;

// ��Щ���������Ϊ��ҪƵ�ʿ��ƣ�ԭ���Ĵ��뵽���ɼ����������ظ���Ƶ�ʿ��ƽṹ
// n += Freq * Fps.getPast();
// if (n > 1.0f) {
//     ...
//     n = 0.0f;
// }
// �Ҿ������ֹ��� һ����������һ���ж���������FPS��Ϳ�����
class Beam
{
private:
	Entity ent;     // Entity���е���ͼ����ֻ��һ���ж������
	float power;
	float maxPower;
	int attack;
	int attribute;
	char BeamCharBuffer[SCREEN_HEIGHT];
	int BeamAttrBuffer[SCREEN_HEIGHT];
public:
	Beam(int attr, int attack, int power);
	void fire(int x, int y, int dir); // �γ������ж���ͬʱ��������
	void draw();                      // �����ߣ������fire֮�����
	void charge(float n);             // ����
	float getPower() const;           // �������
	int getAtk() const;               // ��ù�����
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

void VShooter(Bullets& blt, int x, int y, int dir);


extern Bullets bullets;
extern Bullets enemyBullets;
extern Beam beam;