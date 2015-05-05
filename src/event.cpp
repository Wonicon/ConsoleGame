#include <stdlib.h>
#include <windows.h>
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "weapon.h"
#include "game-state.h"    // state
#include "fps.h"           // GetPast()

// PlayerMovement 玩家移动事件
//  1. move方法自带时间控制
//  2. UL, UR, DL, DR可以由U, D, L, R按位或得到
void PlayerMovement()
{
	int dir = STOP;
	if (state.up)         dir |= U;
	else if (state.down)  dir |= D;
	if (state.left)       dir |= L;
	else if (state.right) dir |= R;
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
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
		state.hitCount += bullets.collide(*itr);
	state.hitCount += Collide(beam.getJudge(), enemies, true);
}

void Movement()
{
	CollisionDetection();
	EraseDeadEntity(enemies);
	Shooter(bullets, player, U);
	bullets.update();
	beam.fire(player.mid(), player.up(), U, state.beam);
	CollisionDetection();
	EraseDeadEntity(enemies);
	PlayerMovement();
	if (Collide(player, enemies, true) > 0)
		state.playerState = DEAD;
	if (enemyBullets.collide(player))
		state.playerState = DEAD;
	enemyBullets.update();
}