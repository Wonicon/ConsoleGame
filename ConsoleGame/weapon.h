#pragma once

#include "entity.h"
#include "fps.h"

// ?些武器?的行?需要?率控制，原来的代?到?可?如下??重?的?率控制??
// n += Freq * Fps.getPast();
// if (n > 1.0f) {
//     ...
//     n = 0.0f;
// }
// 我?得??功能 一个浮点数，一个判定函数，和FPS?就可以了
class Beam
{
private:
	Entity ent;     // Entity不承担画?任?，只是一个判定点?件
	float power;
	float maxPower;
	int attack;
	int attribute;
	char BeamCharBuffer[SCREEN_HEIGHT];
	int BeamAttrBuffer[SCREEN_HEIGHT];
public:
	Beam(int attr, int attack, float power);
	void fire(int x, int y, int dir, bool en = true); // 形成射?判定，同?消耗能量
	void draw(bool en = true);                      // 画射?，最好在fire之后?用
	void charge(float n);             // 充能
	float getPower() const;           // ?得能量
	int getAtk() const;               // ?得攻?力
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
		:atk(attack), sample(sample), freq(frequence), acc(0.0f), count(10000) {}
	void fire(int x, int y, int dir, bool en = false)
	{
		// en 是?了允??人无限子?的
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