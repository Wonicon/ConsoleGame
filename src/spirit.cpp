#include "object.h"
#include <deque>
using std::deque;

// �Ի�
COORD playerPos = { 40, 40 };
COORD playerSize = { 5, 1 };
char playerImg[] = "<=#=>";

Object player(playerPos, playerSize, playerImg, 1, 100);

// �л�
COORD enemyPos = { 0, 0 };
COORD enemySize = { 3, 1 };
char enemyImg[] = ">_<";
// ����һ���������󣬼�������ʱ�ƺ����ⲻ�˿������죬�����ƺ����԰Ѳ����Ĺ���������ʡ����
Object enemySample(enemyPos, enemySize, enemyImg, 1, 50);

// �ӵ�
COORD bulletPos = { 1, 1 };
COORD bulletSize = { 1, 2 };
char bulletImg[] = "^|";
// ͬ�л�������������Ϊ�ӵ��͵л�����Ҫ�����ظ����ɵ�
Object bulletSample(bulletPos, bulletSize, bulletImg, 3, 1);

deque<Object> enemies;
deque<Object> bullets;