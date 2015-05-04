#pragma once

#include <deque>
#include "entity.h"
using std::deque;

#define FRED FOREGROUND_RED
#define FGREEN FOREGROUND_GREEN
#define FBLUE FOREGROUND_BLUE
#define FWHITE (FBLUE | FRED | FGREEN)

#define BRED BACKGROUND_RED
#define BGREEN BACKGROUND_GREEN
#define BBLUE BACKGROUND_BLUE
#define BWHITE (BBLUE | BRED | BGREEN)

extern Entity player;
extern Entity bulletSample;
extern Entity enemySample;
extern Entity enemyBulletSample;
extern Entity bossSample;
extern deque<Entity> enemies;
extern deque<Entity> bullets;
extern deque<Entity> enemyBullets;