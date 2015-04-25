#include <stdio.h>
#include <time.h>
#include "sprite.h"
#include "event.h"
#include "game.h"
#include "fps.h"

int count;
extern int hitten;
extern CFPS Fps;

int GameMainLoop()
{
	count = 0;
	hitten = 0;
	InitState();
	player.SetPos(SCREEN_WIDTH / 2, HEIGHT / 2);
	enemies.clear();
	bullets.clear();
	while (1) {
		int frameStart = timeGetTime();
		count++;
		ClearConsoleBuffer();  // 清空缓冲区
		if (isHitten(player, ENEMY_JUDGE | ENEMY_BULLET))  // 判断自机是否碰撞到敌机
		{
			player.hurt();
		}

		if (1 || IsWindowActive()) {  // 在窗口激活时进行以下动态时间
			CreateEnemy();
			if (count % 4 == 0) {
				EnemyAutoMove();
			}
			if (count % 2 == 0) {
				//CreateEnemy();
				FireBullet(0x5A);
			}
			PlayerMovement();
		}
		CommonEvents();
		DrawScreen();

		RedrawConsole();
	}
	return 0;
}