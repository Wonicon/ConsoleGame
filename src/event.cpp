#include <stdlib.h>
#include "event.h"
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "game.h"
#include "weapon.h"
extern Bullets bullets;
extern Bullets enemyBullets;

int hitten = 0;
static float MaxPow = 100.0f;
float beampower = MaxPow;

void Beam()
{
	if (IsKeyPressed(VK_SPACE) && beampower > 1.0f) {
		if (beampower > 2.0f) {
			setConsoleColor(BWHITE);
			int x, y, w, h;
			player.getPos(x, y);
			player.getSize(w, h);
			RepDrawColumn(x + w / 2, 0, y, ' ');

			beampower -= MaxPow * Fps.GetPast();
			resetConsoleColor();
		}
	}
	else {
		beampower += Fps.GetPast();
		if (beampower > MaxPow)
			beampower = MaxPow;
	}
}

void PlayerMovement()
{
	int dir = 0;
	if (IsKeyPressed(VK_UP)) {
		dir |= U;
	}
	else if (IsKeyPressed(VK_DOWN)) {
		dir |= D;
	}
	if (IsKeyPressed(VK_LEFT)) {
		dir |= L;
	}
	else if (IsKeyPressed(VK_RIGHT)) {
		dir |= R;
	}
	player.move(dir);
}

void EnemyMove()
{
	static float N = 1.0f;
	static float n = 0.0f;
	deque<Entity>::iterator itr = enemies.begin();
	while (itr != enemies.end()) {
		n += N * Fps.GetPast();
		enemyBullets.fire(itr->mid(), itr->down(), D, 0);
		UINT32 sw = rand() % 100;
		if (sw < 2)
		{
			if (n > 5.0f) {
				int x, y, w, h;
				itr->getPos(x, y);
				itr->getSize(w, h);
				enemyBulletSample.setPos(x + (w - 1) / 2, y);
				if (sw == 1)
				{
					int h = 0, l = D;
					int x0, x1, y0, y1;
					int w0, w1, h0, h1;
					player.getPos(x0, y0);
					(*itr).getPos(x1, y1);
					player.getSize(w0, h0);
					(*itr).getSize(w1, h1);
					if (x0 + w0 < x1)
						h = L;
					else if (x0 > x1 + w1)
						h = R;
					if (y0 + h0 < y1)
						l = U;
					enemyBulletSample.dir = h | l;
				}
				else
					enemyBulletSample.dir = D;

				enemyBullets.fire(itr->mid(), itr->down(), D, 0);
				n = 0.0f;
			}
		}
		else if (sw < 90)
		{
			itr++;
		}
		else
		{
			if (!itr->move(D))
				itr = enemies.erase(itr);
			else
				itr++;
		}

	}
}
void CreateEnemy() {
	int a = rand() % 10;
	if (enemies.size() > 5)
		return;
	if (a == 5) {
		int x = rand() % (SCREEN_WIDTH - 3);
		int y = 2;
		enemySample.setPos(x, y);
		enemies.push_back(enemySample);
	}
}
int EraseDeadEntity(deque<Entity> &ent)
{
	deque<Entity>::iterator itr = ent.begin();
	int cnt = 0;
	while (itr != ent.end()) {
		if (!itr->isDel()) {
			itr++;
		}
		else {
			cnt++;
			itr = ent.erase(itr);
		}
	}
	return cnt;
}

/****************************************
  isCollide 检查 实体x 是否与一组实体碰撞。
  并根据参数判断是否删除组内实体
 ****************************************/
int Collide(Entity x, deque<Entity> &group, bool kill)
{
	auto itr = group.begin();
	int count = 0;
	while (itr != group.end()) {
		if (x.collide(*itr)) {
			if (kill) {
				count++;
				itr->del();
			}
		}
		itr++;
	}
	return count;
}

/****************************************
  isCollide 检查一组实体是否与另一组实体碰撞。
  并根据参数判断是否删除组内实体
****************************************/
int Collide(deque<Entity> &objs, deque<Entity> &hitters, bool kill)
{
	auto itr = objs.begin();
	int count = 0;
	while (itr != objs.end()) {
		if (Collide(*itr, hitters, kill) > 0) {
			if (kill) {
				count++;
				itr->del();
			}
		}
		itr++;
	}
	return count;
}

void CollisionDetection()
{
	hitten += Collide(enemies, bullets.getEntry(), true);
}

void Movement()
{
	CollisionDetection();
	EraseDeadEntity(enemies);
	EnemyMove();
	CollisionDetection();
	EraseDeadEntity(enemies);
	bullets.fire(player.mid(), player.up(), U, 0x5a);
	CollisionDetection();
	EraseDeadEntity(enemies);
	PlayerMovement();
	EraseDeadEntity(enemies);
	enemyBullets.update();
}