#pragma once

#include "entity.h"
#include "weapon.h"

class Enemies : public EntitySet
{
private:
	float freq;
	float t0, t1;
	int decision(Entity& me, Entity& he);
	float t[LEN];
public:
	Enemies(void) :freq(2.0f), t0(0.0f), t1(0.0f)
	{
		for (int i = 0; i < LEN; i++) {
			t[i] = 0.0f;
		}
	}
	void fire(Bullets& blt, Entity& obj);
	void add(void);
};