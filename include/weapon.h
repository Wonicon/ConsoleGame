#pragma once

#include "entity.h"
#include "fps.h"
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
	Beam(int attr, int attack, float power);
	void fire(int x, int y, int dir, bool en = true); // �γ������ж���ͬʱ��������
	void draw(bool en = true);                      // �����ߣ������fire֮�����
	void charge(float n);             // ����
	float getPower() const;           // �������
	int getAtk() const;               // ��ù�����
	Entity &getJudge(void);

};

class Bullets
{
private:
#define LEN 128
	//deque<Entity> entries;
	PEntity entries[LEN];
	int size;
	int  atk;
	Entity &sample;
	float freq;
	float acc;
	int count;
public:
	Bullets(int attack, float frequence, Entity &sample)
		:atk(attack), sample(sample), freq(frequence), acc(0.0f), count(10000)
	{
		for (int i = 0; i < LEN; i++) {
			entries[i] = NULL;
		}
		size = 0;
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
	void deleteEntity(int i)
	{
		delete entries[i];
		entries[i] = NULL;
		size--;
	}
	void fire(int x, int y, int dir, bool en = false)
	{
		// en ��Ϊ��������������ӵ���
		if (en || count > 0) {
			sample.setPos(x, y);
			sample.dir = dir;
			addNewEntity(sample);
			if (!en) count--;
		}
	}
	void move()
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && !entries[i]->move()) {
				deleteEntity(i);
			}
		}
	}
	void erase()
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && entries[i]->isDel()) {
				deleteEntity(i);
			}
		}
	}
	void draw()
	{
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL) {
				entries[i]->draw();
			}
		}
	}
	void update() {
		erase();
		move();
	}
	bool enable(bool clear)
	{
		return FreqLock(acc, freq, clear);
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
	int getCount(void) const
	{
		return count;
	}
	int add(int n)
	{
		count += n;
	}
	int collide(Entity& obj)
	{
		int hitCount = 0;
		for (int i = 0; i < LEN; i++) {
			if (entries[i] != NULL && obj.collide(*entries[i])) {
				obj.del();
				hitCount++;
			}
		}
		return hitCount;
	}
};

void Shooter(Bullets& blt, Entity& obj, int dir);


extern Bullets bullets;
extern Bullets enemyBullets;
extern Beam beam;