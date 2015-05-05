#include <stdlib.h>
#include "event.h"
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "game.h"
#include "weapon.h"
#include "draw.h"
extern Bullets bullets;
extern Bullets enemyBullets;

int hitten = 0;
static float MaxPow = 100.0f;
float beampower = MaxPow;

static Beam beam(BWHITE, 100, 1000.0f, 1);
void BeamUpdate()
{
	if (IsKeyPressed(VK_SPACE) && beam.getPower() > 1.0f) {
		if (beam.getPower() > 2.0f) {
			beam.fire(player.mid(), player.up(), U);
			beam.draw();
		}
	}
	else {
		beam.charge(10.0f * Fps.GetPast());
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
		UINT32 sw = rand() % 10000;
		itr++;
	}
}
void CreateEnemy() {
	int a = rand() % 10;
	if (enemies.size() > 0)
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
int Collide(Entity &x, deque<Entity> &group, bool kill)
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
	hitten += Collide(beam.getJudge(), enemies, true);
}

void Movement()
{
	EnemyMove();
	CollisionDetection();
	EraseDeadEntity(enemies);

	bullets.fire(player.mid(), player.up(), U, 0x5a);
	CollisionDetection();
	EraseDeadEntity(enemies);
	PlayerMovement();
	if (Collide(player, enemies, true) > 0)
		PlayerState = DEAD;
	if (Collide(player, enemyBullets.getEntry(), true))
		PlayerState = DEAD;
	enemyBullets.update();
}