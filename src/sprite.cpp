#include "entity.h"
#include <deque>
using std::deque;
#define FRED FOREGROUND_RED
#define FGREEN FOREGROUND_GREEN
#define FBLUE FOREGROUND_BLUE
// 自机
char playerImg[] = "<=#=>";
int playerAttr[] = { FGREEN, FGREEN, FGREEN, FGREEN, FGREEN };
Entity player(
	40, 40,
	5, 1,
	40,
	1000, 100, 
	playerImg, playerAttr);

// 敌机
char enemyImg[] = ">_<";
int enemyAttr[] = { FRED, FRED, FRED };
// 常备一个样本对象，加入容器时似乎避免不了拷贝构造，这样似乎可以把参数的构造析构节省掉？
Entity enemySample(
	0, 0,
	3, 1,
	30,
	100, 10, 
	enemyImg, enemyAttr);

// 子弹
char bulletImg[] = "|";
int bulletAttr[] = { FBLUE|FRED };
// 同敌机的样本对象，因为子弹和敌机都是要大量重复生成的
Entity bulletSample(
	0, 0,
	1, 1,
	60,
	10, 100,
	bulletImg, bulletAttr);

deque<Entity> enemies;
deque<Entity> bullets;
deque<Entity> enemyBullets;

