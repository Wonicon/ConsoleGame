#include "entity.h"
#include <deque>
using std::deque;

// 自机
COORD playerPos = { 40, 40 };
COORD playerSize = { 5, 1 };
char playerImg[] = "<=#=>";

Entity player(playerPos, playerSize, playerImg, 1, 1000);

// 敌机
COORD enemyPos = { 0, 0 };
COORD enemySize = { 3, 1 };
char enemyImg[] = ">_<";
// 常备一个样本对象，加入容器时似乎避免不了拷贝构造，这样似乎可以把参数的构造析构节省掉？
Entity enemySample(enemyPos, enemySize, enemyImg, 1, 50);

// 子弹
COORD bulletPos = { 1, 1 };
COORD bulletSize = { 1, 1 };
char bulletImg[] = "|";
// 同敌机的样本对象，因为子弹和敌机都是要大量重复生成的
Entity bulletSample(bulletPos, bulletSize, bulletImg, 3, 1);

deque<Entity> enemies;
deque<Entity> bullets;
deque<Entity> enemyBullets;

