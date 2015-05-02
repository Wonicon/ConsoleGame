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

int GameMainLoop()
{
	count = 0;
	hitten = 0;
	InitState();
	player.setPos(SCREEN_WIDTH / 2, HEIGHT / 2);
	enemies.clear();
	bullets.clear();
	float n = 5.0f;
	float N = 0.0f;
	while (1) {
		ClearConsoleBuffer();  // 清空缓冲区
		if (1 || IsWindowActive()) {  // 在窗口激活时进行以下动态时间
			CreateEnemy();
			if (count % 4 == 0) {
				EnemyAutoMove();
			}
			PlayerMovement();
			N += n * Fps.GetPast();
			DrawString(10, 10, "past %f", Fps.GetPast());
			DrawString(10, 11, "N %f", N);
			if (N > 1.0f)
			{
				FireBullet(0x5a);
				N = 0.0f;
			}
		}
		CommonEvents();
		DrawScreen();

		RedrawConsole();
	}
	return 0;
}

