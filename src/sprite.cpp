#include "entity.h"
#include "sprite.h"
#include <deque>
using std::deque;
// 自机
char playerImg[] = "<=#=>";
int playerAttr[] = { FWHITE, FWHITE, FWHITE, FWHITE, FWHITE };
Entity player(
	40, 40,
	5, 1,
	40,
	playerImg, playerAttr);

// 敌机
char enemyImg[] = "'_'";
int enemyAttr[] = { FWHITE, FWHITE, FWHITE };
// 常备一个样本对象，加入容器时似乎避免不了拷贝构造，这样似乎可以把参数的构造析构节省掉？
Entity enemySample(
	0, 0,
	3, 1,
	10,
	enemyImg, enemyAttr);

// 敌机Boss
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
// 常备一个样本对象，加入容器时似乎避免不了拷贝构造，这样似乎可以把参数的构造析构节省掉？
Entity bossSample(
	(SCREEN_WIDTH - 11) / 2, 0,
	11, 5,
	0,
	bossImg, bossAttr);

// 子弹
char bulletImg[] = "0";
int bulletAttr[] = { FWHITE };
// 同敌机的样本对象，因为子弹和敌机都是要大量重复生成的
Entity bulletSample(
	0, 0,
	1, 1,
	70,
	bulletImg, bulletAttr);

// 子弹
char enemyBulletImg[] = "*";
int enemyBulletAttr[] = { FWHITE };
Entity enemyBulletSample(
	0, 0,
	1, 1,
	4,
	enemyBulletImg, enemyBulletAttr);