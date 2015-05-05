#include <stdlib.h>
#include <windows.h>
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "weapon.h"
#include "game-state.h"    // state
#include "fps.h"           // GetPast()
#include "enemy.h"

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

// CollisionDetectionn 全局碰撞检测
// 所有碰撞检测行为都在这里处理
#include "enemy.h"
Enemies enemies;

void CollisionDetection()
{
	state.hitCount += bullets.collide(enemies);
	state.hitCount += enemies.collide(beam.getJudge());
	if (enemies.collide(player) > 0)
		state.playerState = DEAD;
	if (enemyBullets.collide(player))
		state.playerState = DEAD;
}

void Events()
{
	// 敌人的回合
	enemies.move();
	enemies.fire(enemyBullets, player);
	enemyBullets.update();
	CollisionDetection();
	enemies.erase();

	// 玩家的回合
	PlayerMovement();
	Shooter(bullets, player, U);
	bullets.update();
	beam.fire(player.mid(), player.up(), U, state.beam);
	CollisionDetection();
	enemies.erase();
}