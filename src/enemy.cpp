#include <stdlib.h>
#include "enemy.h"
#include "sprite.h"
#include "fps.h"
//deque<Entity> enemies;

// 增加新敌机
bool AddEnemy(void)
{
	static float n = 0.0f;
	n += 1.0f * GetPast(); // 1s 产生一个敌人
	if (n > 1.0f) {
		if (enemies.size() >= 20) {
			return false;
		}
		int x = rand() % (SCREEN_WIDTH - 3);
		int y = 0;
		enemySample.setPos(x, y);
		enemies.push_back(enemySample);
		n = 0.0f;
		return false;
	}
	return false;
}

// 敌机移动
#include "component.h"
bool EnemyMovement(void)
{
	auto itr = enemies.begin();
	while (itr != enemies.end()) {
		if (!itr->move()) {
			itr = enemies.erase(itr);
		}
		else {
			itr++;
		}
	}
}

//bool EnemyAI(const Entity&e, const Entity& p, Bullets blt)
//{
//	srand(timeGetTime());
//	int s = rand() % 1000;
//	if (s < 300) return false;
//	else if (s < 900) {
//		if (e.scr_y < p.scr_y) {
//			blt.fire(e.mid(), e.down() + 1, D, true);
//		}
//	}
//	else {
//		int dir = D;
//		if (e.scr_x + e.width < p.scr_x) dir |= R;
//		else if (e.scr_x > p.scr_x + p.width) dir |= L;
//		blt.fire(e.mid(), e.down() + 1, dir, true);
//	}
//	return true;
//}

extern Bullets enemyBullets;
void EnemyFire(void)
{
	int count = 0;
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
		if (1) {
			count++;
		}
		if (count > 10) {
			break;
		}
	}
}

void EnemyClear(bool all)
{
	if (all) {
		enemies.clear();
	}
	else {
		auto itr = enemies.begin();
		while (itr != enemies.end()) {
			if (itr->isDel()) {
				itr = enemies.erase(itr);
			}
			else {
				itr++;
			}
		}
	}
}

void DrawEnemy(void)
{
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
		itr->draw();
	}
}

