#include "entity.h"
#include <deque>
using std::deque;

// �Ի�
COORD playerPos = { 40, 40 };
COORD playerSize = { 5, 1 };
char playerImg[] = "<=#=>";

Entity player(playerPos, playerSize, playerImg, 1, 1000);

// �л�
COORD enemyPos = { 0, 0 };
COORD enemySize = { 3, 1 };
char enemyImg[] = ">_<";
// ����һ���������󣬼�������ʱ�ƺ����ⲻ�˿������죬�����ƺ����԰Ѳ����Ĺ���������ʡ����
Entity enemySample(enemyPos, enemySize, enemyImg, 1, 50);

// �ӵ�
COORD bulletPos = { 1, 1 };
COORD bulletSize = { 1, 1 };
char bulletImg[] = "|";
// ͬ�л�������������Ϊ�ӵ��͵л�����Ҫ�����ظ����ɵ�
Entity bulletSample(bulletPos, bulletSize, bulletImg, 3, 1);

deque<Entity> enemies;
deque<Entity> bullets;
deque<Entity> enemyBullets;

