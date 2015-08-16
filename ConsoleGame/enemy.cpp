#include "enemy.h"
#include "fps.h"
float F = 2.0f;
extern int lv;

int Enemies::decision(Entity& me, Entity& he)
{
	int dir = STOP;
	if (me.scr_x + me.width < he.scr_x)
		dir |= R;
	else if (me.scr_x > he.scr_x + he.width)
		dir |= L;
	if (me.scr_y + me.height < he.scr_y)
		dir |= D;
	else if (me.scr_y > he.scr_y + he.height && lv >= 2)
		dir |= U;
	return dir;
}
#include "draw.h"
void Enemies::fire(Bullets& blt, Entity& obj)
{
	srand(timeGetTime());
	int r;
	int size = getSize();
	PEntity p;
	for (int i = 0; i < LEN; i++) {
		if (FreqLock(t[i], F, entries[i] != NULL)) {
			p = entries[i];
			r = rand() % 1000;
			if (r < 200) {
				blt.fire(p->mid(), p->down() + 1, decision(*p, obj), true);
			}
			else if (r < 500) {
				blt.fire(p->mid(), p->down() + 1, D);
			}
		}
	}
}

extern Entity enemySample;
void Enemies::add(void)
{
	if (!FreqLock(t1, freq, true))
		return;

	enemySample.scr_x = rand() % (SCREEN_WIDTH - 3);
	enemySample.scr_y = 1;
	enemySample.dir = D;

	addNewEntity(enemySample);
}

Enemies enemies;

#include "sprite.h"
char bossImg[] =
" #  [|]  # "
"-||--|--||-"
" |-|||||-| "
" |  |||  | "
" $   V   $ ";

int bossAttr[] =
{
	FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED,
	FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED,
	FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED,
	FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED,
	FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED, FRED,
};
// 常备一个样本对象，加入容器时似乎避免不了拷贝构造，这样似乎可以把参数的构造析构节省掉？
Entity boss(
	(SCREEN_WIDTH - 11 - 1) / 2, 0,
	11, 5,
	0,
	bossImg, bossAttr);
Bullets bossbullets(100, 10.0f, enemyBulletSample);
Beam bossbeam(BGREEN | BRED, 100, 10000000.0f);
bool haveBoss = false;
bool beatBoss = false;
bool beamEN = false;
int bossLife = 1000;

extern Bullets bullets;
extern Beam beam;

void BossCollide(void)
{
	int hit = bullets.collide(boss);
	int beamHit = boss.collide(beam.getJudge());
	bossLife -= hit + beamHit;
	if (bossLife < 0) {
		haveBoss = false;
		beatBoss = true;
	}
}

void BossAttack(void) {
	boss.vel = 5;
	if (boss.dir != L && boss.dir != R)
		boss.dir = R;

	static float t = 0.0f;
	static float mv_time = 0.0f;
	static int s = 0;
	t += F * GetPast();
	mv_time += GetPast();

	if (!boss.move()) {
		switch (boss.dir) {
		case R: boss.dir = L; break;
		case L: boss.dir = R; break;
		}
	}
	if (t < 10.0f) {
		if (mv_time > 1.0f) {
			bossbullets.fire(boss.mid(), boss.down() + 1, D, true);
			bossbullets.fire(boss.left() + 1, boss.down() + 1, DR, true);
			bossbullets.fire(boss.right() - 1, boss.down() + 1, DL, true);
			mv_time = 0.0f;
		}
		s = rand() % 90;
	}
	else if (t < 15.0f) {
		beamEN = true;
		
		if (s < 30)
			bossbeam.fire(boss.mid(), boss.down() + 1, D, beamEN);
		else if (s < 60)
			bossbeam.fire(boss.left() + 1, boss.down() + 1, D, beamEN);
		else if (s < 90)
			bossbeam.fire(boss.right() - 1, boss.down() + 1, D, beamEN);
	}
	else {
		beamEN = false;
		t = 0.0f;
	}
	bossbullets.update();
}