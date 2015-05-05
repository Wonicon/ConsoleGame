#include <stdio.h>
#include <time.h>
#include "sprite.h"
#include "event.h"
#include "game.h"
#include "fps.h"
#include "draw.h"
#include "weapon.h"
#include "weapon.h"
extern Bullets bullets;
int count;
extern int hitten;
int PlayerState = ALIVE;

int GameMainLoop()
{
	count = 0;
	hitten = 0;
	player.setPos(SCREEN_WIDTH / 2, HEIGHT / 2);
	enemies.clear();
	PlayerState = ALIVE;
	while (PlayerState == ALIVE) {
		if (1 || IsWindowActive()) {  // 在窗口激活时进行以下动态时间, 调试期间论外
			// 清空缓冲区和重绘缓冲区一定要有，期间所以字符都重画
			// 除了键盘API外，只有输出缓冲区这一个系统调用
			// TODO Movement里包含了太多的功能
			ClearConsoleBuffer();
			CreateEnemy();
			Movement();
			DrawScreen();
			RedrawConsole();
		}
	}
	return 0;
}

