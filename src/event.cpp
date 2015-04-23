#include "event.h"
#include "spirit.h"
#include "console.h"
#include <stdlib.h>

int hitten = 0;
static int State[HEIGHT * WIDTH];


void InitState()
{
	memset(State, 0, sizeof(State));
}

void WriteState(const Entity& obj, int state)
{
	COORD pos = obj.getPos();
	COORD size = obj.getSize();
	for (int j = pos.Y; j < pos.Y + size.Y; j++) {
		for (int i = pos.X; i < pos.X + size.X; i++) {
			State[j * WIDTH + i] |= state;

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
	while (itr != enemies.end()) {
		if (isHitten(*itr, PLAYER_BULLET)) {
			itr->Die();
		}
		itr++;
	}
}
bool isHitten(const Entity& obj, int label)
{
	COORD pos = obj.getPos();
	COORD size = obj.getSize();
	for (int j = pos.Y; j < pos.Y + size.Y; j++) {
		for (int i = pos.X; i < pos.X + size.X; i++) {
			if (State[j * WIDTH + i] & label) {
				hitten++;
				return true;
			}
		}
	}
	return false;
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
	if ((state & 0x8000) == 0x8000) {
		COORD playerPos = player.getPos();
		COORD playerSize = player.getSize();
		bulletSample.SetPos(playerPos.X + (playerSize.X - 1) / 2, playerPos.Y);
		bullets.push_back(bulletSample);
	}
}
void PlayerMovement()
{
	int x, y;
	x = y = 0;
	if (IsKeyPressed(VK_DOWN)) {
		y = 1;
	}
	else if (IsKeyPressed(VK_UP)) {
		y = -1;
	}
	if (IsKeyPressed(VK_LEFT)) {
		x = -1;
	}
	else if (IsKeyPressed(VK_RIGHT)) {
		x = 1;
	}
	player.Move(x, y);
	player.RangeLimit();
}


void CreateEnemy() {
	int a = rand() % 10;
	if (a == 5) {
		int x = rand() % (SCREEN_WIDTH - 3);
		int y = 0;
		enemySample.SetPos(x, y);
		enemies.push_back(enemySample);
	}
}
void MoveBullets() {
	deque<Entity>::iterator itr = bullets.begin();
	while (itr != bullets.end()) {
		itr->Move(0, -1);
		if (itr->RangeLimit()) {
			WriteState(*itr, PLAYER_BULLET);
			itr++;
		}
		else {
			itr = bullets.erase(itr);
		}
	}
}
void EnemyAutoMove()
{
	deque<Entity>::iterator itr = enemies.begin();
	while (itr != enemies.end()) {
		if (itr->RangeLimit()) {
			itr->Move(0, 1);
			itr++;
		}
		else {
			itr = enemies.erase(itr);
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
	InitState();
	WriteState(player, PLAYER_JUDGE);
	MoveBullets();
	RefreshEnemyState();
	DetectCollision();
	EraseDeadEnemies();
}