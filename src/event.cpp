﻿#include "event.h"
#include "sprite.h"
#include "console.h"
#include <stdlib.h>
#include "entity.h"
#include "game.h"

int hitten = 0;
static float MaxPow = 100.0f;
float beampower = MaxPow;
static int state[HEIGHT * WIDTH];

void InitState()
{
	memset(&state[0], 0, sizeof(state));
}

void WriteState(Entity& obj, int label)
{
	int x, y, w, h;
	int k = 0;
	const char *s = obj.getImage();
	obj.getPos(x, y);
	obj.getSize(w, h);
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			if (s[k++] != JMP_CHAR) {
				state[i + j * WIDTH] = label;
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
	while (itr != enemies.end()) {
		if (isHitten(*itr, PLAYER_JUDGE | PLAYER_BULLET | PLAYER_BEAM))
		{
			itr->die();
			hitten++;
			beampower += 1.0f;
		}
		itr++;
	}
}

bool isHitten(const Entity& obj, int label)
{
	int x, y, w, h;
	obj.getPos(x, y);
	obj.getSize(w, h);
	for (int j = y; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			if (state[i + j * WIDTH] & label) {
				return true;
			}
		}
	}
	return false;
}

void MoveBullets() {
	deque<Entity>::iterator itr = bullets.begin();
	while (itr != bullets.end()) {
		if (itr->move()) {
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
		if (isHitten(*itr, PLAYER_BEAM))
		{
			itr = enemyBullets.erase(itr);
		}
		else if (itr->move())
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
void FireBullet()
{
	static float N = 8.0f;
	static float n = 0.0f;
	n += N * Fps.GetPast();
	
	if (n > 1.0f) {
		if (IsKeyPressed(0x5a)) {
			int x, y, w, h;
			player.getPos(x, y);
			player.getSize(w, h);
			bulletSample.setPos(x + (w - 1) / 2, y);
			bulletSample.dir = U;
			bullets.push_back(bossSample);
			n = 0.0f;
		}
		else if (IsKeyPressed(0x58)) {
			int x, y, w, h;
			player.getPos(x, y);
			player.getSize(w, h);
			bulletSample.setPos(x + (w - 1) / 2, y);
			bulletSample.dir = UR;
			bullets.push_back(bulletSample);
			bulletSample.dir = UL;
			bullets.push_back(bulletSample);
			n = 0.0f;
		}
	}
}
void Beam()
{
	if (IsKeyPressed(VK_SPACE) && beampower > 1.0f) {
		if (beampower > 2.0f) {
			setConsoleColor(BWHITE);
			int x, y, w, h;
			player.getPos(x, y);
			player.getSize(w, h);
			RepDrawColumn(x + w / 2, 0, y, ' ');

			for (int i = 0; i <= y - 1; i++)
			{
				state[i * WIDTH + x + w / 2] = PLAYER_BEAM;
			}

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
		UINT32 sw = rand() % 100;
		if (sw < 5)
		{
			if (n > 1.0f) {
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

				enemyBullets.push_back(enemyBulletSample);
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
		int y = 0;
		enemySample.setPos(x, y);
		enemies.push_back(enemySample);
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
void CommonEvents()
{
	InitState();
	WriteState(player, PLAYER_JUDGE);
	MoveBullets();
	DetectCollision();
	EraseDeadEnemies();
	RefreshEnemyState();
}
void Movement()
{
	WriteState(player, PLAYER_JUDGE);
	MoveBullets();
	EnemyMove();
	DetectCollision();
	RefreshEnemyState();
	if (isHitten(player, ENEMY_BULLET | ENEMY_JUDGE))
	{
		PlayerState = DEAD;
	}
	EraseDeadEnemies();
	PlayerMovement();
}