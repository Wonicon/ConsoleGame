#include <stdlib.h>
#include <windows.h>
#include "entity.h"
#include "sprite.h"
#include "game-state.h"

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


// 一些实体的集合对象，如 Bullet 自带了erase方法
// 这个函数是用来清理一些暴露在外面的实体集合的死亡实体的
//int EraseDeadEntity(deque<Entity> &ent)
//{
//	deque<Entity>::iterator itr = ent.begin();
//	int cnt = 0;
//	while (itr != ent.end()) {
//		if (!itr->isDel()) {
//			itr++;
//		}
//		else {
//			cnt++;
//			itr = ent.erase(itr);
//		}
//	}
//	return cnt;
//}

//// isCollide 检查 实体x 是否与一组实体碰撞。
//// 并根据参数判断是否删除组内实体
//int Collide(Entity &x, deque<Entity> &group, bool kill)
//{
//	auto itr = group.begin();
//	int count = 0;
//	while (itr != group.end()) {
//		if (x.collide(*itr)) {
//			if (kill) {
//				count++;
//				itr->del();
//			}
//		}
//		itr++;
//	}
//	return count;
//}
//
//// isCollide 检查一组实体是否与另一组实体碰撞。
//// 并根据参数判断是否删除组内实体
//int Collide(deque<Entity> &objs, deque<Entity> &hitters, bool kill)
//{
//	auto itr = objs.begin();
//	int count = 0;
//	while (itr != objs.end()) {
//		if (Collide(*itr, hitters, kill) > 0) {
//			if (kill) itr->del();
//			count++;
//		}
//		itr++;
//	}
//	return count;
//}
//
//// CollisionDetectionn 全局碰撞检测
//// 所有碰撞检测行为都在这里处理
//#include "weapon.h"
//void CollisionDetection()
//{
//	state.hitCount += Collide(enemies, bullets.getEntry(), true);
//	state.hitCount += Collide(beam.getJudge(), enemies, true);
//	if (Collide(player, enemies, true) > 0)
//		state.playerState = DEAD;
//	if (Collide(player, enemyBullets.getEntry(), true) > 0)
//		state.playerState = DEAD;
//}

