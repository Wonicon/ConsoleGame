#pragma once

#include <deque>
#include "entity.h"
using std::deque;

extern Entity player;
extern Entity bulletSample;
extern Entity enemySample;
extern deque<Entity> enemies;
extern deque<Entity> bullets;
extern deque<Entity> enemyBullets;

