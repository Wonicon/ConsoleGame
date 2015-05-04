#include "entity.h"
#include "sprite.h"
#include <deque>
using std::deque;
// �Ի�
char playerImg[] = "<=#=>";
int playerAttr[] = { FWHITE, FWHITE, FWHITE, FWHITE, FWHITE };
Entity player(
	40, 40,
	5, 1,
	40,
	1, 100, 
	playerImg, playerAttr);

// �л�
char enemyImg[] = "'_'";
int enemyAttr[] = { FWHITE, FWHITE, FWHITE };
// ����һ���������󣬼�������ʱ�ƺ����ⲻ�˿������죬�����ƺ����԰Ѳ����Ĺ���������ʡ����
Entity enemySample(
	0, 0,
	3, 1,
	30,
	1, 10, 
	enemyImg, enemyAttr);

// �л�Boss
char bossImg[] =
"\
 &  #|#  & \
-||--|--||-\
 |-|-|-|-| \
 |  |||  | \
 $   V   $ \
";
int bossAttr[] =
{
	FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE,
	FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE,
	FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE,
	FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE,
	FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE, FWHITE,
};
// ����һ���������󣬼�������ʱ�ƺ����ⲻ�˿������죬�����ƺ����԰Ѳ����Ĺ���������ʡ����
Entity bossSample(
	(SCREEN_WIDTH - 11) / 2, 0,
	11, 5,
	0,
	100, 10,
	bossImg, bossAttr);

// �ӵ�
char bulletImg[] = "0";
int bulletAttr[] = { FWHITE };
// ͬ�л�������������Ϊ�ӵ��͵л�����Ҫ�����ظ����ɵ�
Entity bulletSample(
	0, 0,
	1, 1,
	70,
	10, 100,
	bulletImg, bulletAttr);

// �ӵ�
char enemyBulletImg[] = "*";
int enemyBulletAttr[] = { FWHITE };
Entity enemyBulletSample(
	0, 0,
	1, 1,
	10,
	30, 100,
	enemyBulletImg, enemyBulletAttr);

deque<Entity> enemies;
deque<Entity> bullets;
deque<Entity> enemyBullets;
deque<Entity> beam;