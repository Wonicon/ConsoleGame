#include "entity.h"
#include <deque>
using std::deque;
#define FRED FOREGROUND_RED
#define FGREEN FOREGROUND_GREEN
#define FBLUE FOREGROUND_BLUE
// �Ի�
char playerImg[] = "<=#=>";
int playerAttr[] = { FGREEN, FGREEN, FGREEN, FGREEN, FGREEN };
Entity player(
	40, 40,
	5, 1,
	40,
	1000, 100, 
	playerImg, playerAttr);

// �л�
char enemyImg[] = ">_<";
int enemyAttr[] = { FRED, FRED, FRED };
// ����һ���������󣬼�������ʱ�ƺ����ⲻ�˿������죬�����ƺ����԰Ѳ����Ĺ���������ʡ����
Entity enemySample(
	0, 0,
	3, 1,
	30,
	100, 10, 
	enemyImg, enemyAttr);

// �ӵ�
char bulletImg[] = "|";
int bulletAttr[] = { FBLUE|FRED };
// ͬ�л�������������Ϊ�ӵ��͵л�����Ҫ�����ظ����ɵ�
Entity bulletSample(
	0, 0,
	1, 1,
	60,
	10, 100,
	bulletImg, bulletAttr);

deque<Entity> enemies;
deque<Entity> bullets;
deque<Entity> enemyBullets;

