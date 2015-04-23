#include <stdio.h>
#include <time.h>
#include "spirit.h"
#include "event.h"
#include "game.h"

extern int hitten;
extern int start;
int count;

int GameMainLoop()
{
	start = timeGetTime();
	count = 0;
	hitten = 0;
	InitState();
	player.SetPos(SCREEN_WIDTH / 2, HEIGHT / 2);
	enemies.clear();
	bullets.clear();
	while (1) {
		int s = timeGetTime();
		count++;
		ClearConsoleBuffer();  // 清空缓冲区
		if (isHitten(player, 8))  // 判断自机是否碰撞到敌机
			break;

		if (IsWindowActive()) {  // 在窗口激活时进行以下动态时间
			if (count % 4 == 0) {
				EnemyAutoMove();
			}
			if (count % 2 == 0) {
				CreateEnemy();
				FireBullet(0x5A);
			}
			PlayerMovement();
		}
		CommonEvents();
		DrawScreen();

		RedrawConsole();

		Sleep(10);
	}
	return 0;
}