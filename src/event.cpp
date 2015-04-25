#include "event.h"
#include "sprite.h"
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
		if (isHitten(*itr, PLAYER_BULLET | PLAYER_JUDGE)) {
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
#include "fps.h"
#include "draw.h"
#include "stdio.h"
#include <math.h>
extern CFPS Fps;
#pragma warning(disable : 4996)
void PlayerMovement()
{
	static float x = player.getPos().X;
	static float y = player.getPos().Y;
	static int preFlags = 0;
	int speed = 80;
	int flags = 0; // 上下左右
	float distance = Fps.GetPast() * speed;

#define U 8
#define D 4
#define L 2
#define R 1
#define UL (U | L)
#define UR (U | R)
#define DL (D | L)
#define DR (D | R)

	if (IsKeyPressed(VK_UP)) {
		flags |= U;
	}
	else if (IsKeyPressed(VK_DOWN)) {
		flags |= D;
	}
	if (IsKeyPressed(VK_LEFT)) {
		flags |= L;
	}
	else if (IsKeyPressed(VK_RIGHT)) {
		flags |= R;
	}

	if (preFlags != flags)
	{
		x = floor(x);
		y = floor(y);
	}

	switch (flags) {
	case U: y -= distance / 2; break;
	case D: y += distance / 2; break;
	case L: x -= distance; break;
	case R: x += distance; break;
	case UL: x -= distance; y -= distance; break;
	case UR: x += distance; y -= distance; break;
	case DL: x -= distance; y += distance; break;
	case DR: x += distance; y += distance; break;
	default: x = floor(x); y = floor(y);
	}
	
	preFlags = flags;

	if (flags != 0) {
		if (y > HEIGHT - player.getSize().Y)
			y = (float)(HEIGHT - player.getSize().Y);
		else if (y < 0)
			y = 0;
		if (x > SCREEN_WIDTH - player.getSize().X)
			x = (float)(SCREEN_WIDTH - player.getSize().X);
		else if (x < 0)
			x = 0;
	}
	player.SetPos((int)x, (int)y);

	static char temp[1024];
	sprintf(temp, "float x %.4f", x);
	DrawString(SCREEN_WIDTH + 1, 10, temp);
	sprintf(temp, "float y %.4f", y);
	DrawString(SCREEN_WIDTH + 1, 11, temp);
	sprintf(temp, "int x %d", (int)x);
	DrawString(SCREEN_WIDTH + 1, 12, temp);
	sprintf(temp, "int y %d", (int)y);
	DrawString(SCREEN_WIDTH + 1, 13, temp);
	sprintf(temp, "Flag:cur %d pre %d", preFlags, flags);
	DrawString(SCREEN_WIDTH + 1, 14, temp);
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
	itr = enemyBullets.begin();
	while (itr != enemyBullets.end())
	{
		itr->Move(0, 1);
		if (itr->RangeLimit())
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
	while (itr != enemies.end()) {
		if (itr->RangeLimit()) {
			UINT32 sw = rand() % 100;
			if (sw < 70)
			{
				if (sw < 50)
				{
					bulletSample.SetPos(itr->getPos().X + (itr->getSize().X - 1) / 2, itr->getPos().Y);
					enemyBullets.push_back(bulletSample);
				}
			}
			else
			{
				itr->Move(0, 1);
			}
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

