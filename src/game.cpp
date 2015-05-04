#include <stdio.h>
#include <time.h>
#include "sprite.h"
#include "event.h"
#include "game.h"
#include "fps.h"
#include "draw.h"

int count;
extern int hitten;
extern CFPS Fps;
int PlayerState = ALIVE;

int GameMainLoop()
{
	count = 0;
	hitten = 0;
	player.setPos(SCREEN_WIDTH / 2, HEIGHT / 2);
	enemies.clear();
	bullets.clear();
	enemyBullets.clear();
	PlayerState = ALIVE;
	while (PlayerState == ALIVE) {
		if (1 || IsWindowActive()) {  // 在窗口激活时进行以下动态时间
			ClearConsoleBuffer();  // 清空缓冲区
			CreateEnemy();
			FireBullet();
			Beam();
			Movement();
			DrawScreen();
			RedrawConsole();
		}
	}
	return 0;
}

