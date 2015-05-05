#include "entity.h"
#include "fps.h"
#include <deque>
using std::deque;
class Bullets
{
private:
	deque<Entity> entries;
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
		// en 是为了允许敌人无限子弹的
		if (en || count > 0) {
			sample.setPos(x, y);
			sample.dir = dir;
			entries.push_back(sample);
			if (!en) count--;
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
	bool enable(bool clear)
	{
		return FreqLock(acc, freq, clear);
	}
	void clear(void)
	{
		entries.clear();
	}
	int getCount(void) const
	{
		return count;
	}
	int add(int n)
	{
		count += n;
	}
};