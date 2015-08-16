#include <stdlib.h>
#include <windows.h>
#include "sprite.h"
#include "console.h"
#include "entity.h"
#include "weapon.h"
#include "game-state.h"    // state
#include "fps.h"           // GetPast()
#include "enemy.h"
#include "enemy.h"
extern Enemies enemies;
extern 
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
extern bool haveBoss;
extern Bullets bossbullets;
extern Beam bossbeam;
void BossCollide(void);
void BossAttack(void);
void CollisionDetection()
{
	state.hitCount += bullets.collide(enemies);
	state.hitCount += enemies.collide(beam.getJudge());
	state.hp -= enemies.collide(player) + enemyBullets.collide(player);

	if (haveBoss) {
		BossCollide();
		state.hp -= bossbullets.collide(player) + player.collide(bossbeam.getJudge());
	}

	if (state.hp < 0)
		state.playerState = DEAD;
}

void Events()
{
	// Boss的回合
	if (haveBoss) {
		BossAttack();
	}
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

	if (state.hitCount > 20)
		haveBoss = true;
}