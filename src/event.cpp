#include "event.h"
#include "sprite.h"
#include "console.h"
#include <stdlib.h>
#include "entity.h"
int hitten = 0;

#define NonState 0
struct StateNode
{
	int type;
	int subtype;
	void *ref;
};

static StateNode State[HEIGHT][WIDTH];

void InitState()
{
	memset(&State[0][0], 0, sizeof(State));
}

void WriteState(Entity& obj, int state)
{
	int x, y, w, h;
	int k = 0;
	const char *s = obj.getImage();
	obj.getPos(x, y);
	obj.getSize(w, h);
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			if (s[k++] != JMP_CHAR) {
				State[j][i].type = state;
				State[j][i].ref = &obj;
			}
		}
	}
}
void RefreshEnemyState()
{
	deque<Entity>::iterator itr = enemies.begin();
	while (itr != enemies.end()) {
		WriteState(*itr, ENEMY_JUDGE);
		itr++;
	}
}
void DetectCollision()
{
	deque<Entity>::iterator itr = enemies.begin();
	void *aim;
	while (itr != enemies.end()) {
		if (aim = isHitten(*itr, PLAYER_BULLET))
		{
			itr->die();
		}
		itr++;
	}
}

void *isHitten(const Entity& obj, int label)
{
	int x, y, w, h;
	obj.getPos(x, y);
	obj.getSize(w, h);
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			if (State[j][i].type == label) {
				return State[j][i].ref;
			}
		}
	}
	return NULL;
}

int IsKeyPressed(KEYCODE keycode)
{
	short state = GetAsyncKeyState(keycode);
	if ((state & 0x8000) == 0x8000) {
		return 1;
	}
	else {
		return 0;
	}
}
void FireBullet(KEYCODE keycode)
{
	short state = GetAsyncKeyState(keycode);
	if ((state & 0x8000) == 0x8000 || 1) {
		int x, y, w, h;
		player.getPos(x, y);
		player.getSize(w, h);
		bulletSample.setPos(x + (w - 1) / 2, y);
		bullets.push_back(bulletSample);
	}
}
#include "fps.h"
#include "draw.h"
#include <stdio.h>
#include <math.h>
extern CFPS Fps;
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

void CreateEnemy() {
	int a = rand() % 10;
	if (enemies.size() > 5)
		return;
	if (a == 5) {
		int x = rand() % (SCREEN_WIDTH - 3);
		int y = 0;
		enemySample.setPos(x, y);
		enemies.push_back(enemySample);
	}
}
void MoveBullets() {
	deque<Entity>::iterator itr = bullets.begin();
	while (itr != bullets.end()) {
		if (itr->move(U)) {
			WriteState(*itr, PLAYER_BULLET);
			itr++;
		}
		else {
			itr = bullets.erase(itr);
		}
	}
	itr = enemyBullets.begin();
	while (itr != enemyBullets.end())
	{
		if (itr->move(D))
		{
			WriteState(*itr, ENEMY_BULLET);
			itr++;
		}
		else
		{
			itr = enemyBullets.erase(itr);
		}
	}
}
void EnemyAutoMove()
{
	deque<Entity>::iterator itr = enemies.begin();
	int x, y, w, h;
	while (itr != enemies.end()) {
		UINT32 sw = rand() % 100;
		if (sw < 5)
		{
			//itr->getPos(x, y);
			//itr->getSize(w, h);
			//bulletSample.setPos(x + (w - 1) / 2, y);
			//enemyBullets.push_back(bulletSample);
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
int EraseDeadEnemies()
{
	deque<Entity>::iterator itr = enemies.begin();
	int cnt = 0;
	while (itr != enemies.end()) {
		if (itr->isAlive()) {
			itr++;
		}
		else {
			cnt++;
			itr = enemies.erase(itr);
		}
	}
	return cnt;
}
void CommonEvents() {
	void *aim;
	if (aim = isHitten(player, ENEMY_JUDGE))  // 判断自机是否碰撞到敌机
	{
		player.hurt(*(Entity *)aim);
	}
	else if (aim = isHitten(player, ENEMY_BULLET))
	{
		player.hurt(*(Entity *)aim);
	}
	InitState();
	WriteState(player, PLAYER_JUDGE);
	MoveBullets();
	RefreshEnemyState();
	DetectCollision();
	EraseDeadEnemies();
}
