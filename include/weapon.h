#pragma once

#include "entity.h"
#include "fps.h"

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
	EntitySet E;
	int  atk;
	Entity &sample;
	float freq;
	float acc;
	int count;
public:
	Bullets(int attack, float frequence, Entity &sample)
		:atk(attack), sample(sample), freq(frequence), acc(0.0f), count(10000){}
	void fire(int x, int y, int dir, bool en = false)
	{
		// en ��Ϊ��������������ӵ���
		if (en || count > 0) {
			sample.setPos(x, y);
			sample.dir = dir;
			E.addNewEntity(sample);
			if (!en) count--;
		}
	}
	void draw(void) { E.draw(); }
	void erase(void) { E.erase(); }
	void update() {
		E.erase();
		E.move();
	}
	bool enable(bool clear)
	{
		return FreqLock(acc, freq, clear);
	}
	void clear(void)
	{
		E.clear();
	}
	int getCount(void) const
	{
		return count;
	}
	int add(int n)
	{
		count += n;
	}
	int collide(Entity& obj) { return E.collide(obj); }
	int collide(EntitySet& s) { return E.collide(s); }
	EntitySet& getSet(void) { return E; }
};

void Shooter(Bullets& blt, Entity& obj, int dir);


extern Bullets bullets;
extern Bullets enemyBullets;
extern Beam beam;