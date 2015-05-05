#include <stdlib.h>
#include "event.h"
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "game.h"
#include "weapon.h"
#include "draw.h"

int hitten = 0;

// BeamUpdate 描述玩家的激光具体行为
void BeamUpdate()
{
	if (IsKeyPressed(VK_SPACE) && beam.getPower() > 1.0f) {
		if (beam.getPower() > 2.0f) {
			beam.fire(player.mid(), player.up(), U);
			beam.draw();
		}
	}
	else {
		beam.charge(1.0f * GetPast());
	}
}

// PlayerMovement 玩家移动事件
//  1. move方法自带时间控制
//  2. UL, UR, DL, DR可以由U, D, L, R按位或得到
void PlayerMovement()
{
	int dir = STOP;
	if (IsKeyPressed(VK_UP))         dir |= U;
	else if (IsKeyPressed(VK_DOWN))  dir |= D;
	if (IsKeyPressed(VK_LEFT))       dir |= L;
	else if (IsKeyPressed(VK_RIGHT)) dir |= R;
	player.move(dir);
}

void CreateEnemy() {
	int a = rand() % 10;
	if (enemies.size() > 10)
		return;
	if (a == 5) {
		int x = rand() % (SCREEN_WIDTH - 3);
		int y = 0;
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

// isCollide 检查 实体x 是否与一组实体碰撞。
// 并根据参数判断是否删除组内实体
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

// isCollide 检查一组实体是否与另一组实体碰撞。
// 并根据参数判断是否删除组内实体
int Collide(deque<Entity> &objs, deque<Entity> &hitters, bool kill)
{
	auto itr = objs.begin();
	int count = 0;
	while (itr != objs.end()) {
		if (Collide(*itr, hitters, kill) > 0) {
			if (kill) itr->del();
			count++;
		}
		itr++;
	}
	return count;
}

// CollisionDetectionn 全局碰撞检测
// 所有碰撞检测行为都在这里处理
void CollisionDetection()
{
	hitten += Collide(enemies, bullets.getEntry(), true);
	hitten += Collide(beam.getJudge(), enemies, true);
}


void Movement()
{
	CollisionDetection();
	EraseDeadEntity(enemies);

	bullets.fire(player.mid(), player.up(), U, 0x5a);
	bullets.update();
	BeamUpdate();
	VShooter(bullets, player.mid(), player.up(), U);
	CollisionDetection();
	EraseDeadEntity(enemies);
	PlayerMovement();
	if (Collide(player, enemies, true) > 0)
		PlayerState = DEAD;
	if (Collide(player, enemyBullets.getEntry(), true) > 0)
		PlayerState = DEAD;
	enemyBullets.update();
}