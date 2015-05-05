#include <stdio.h>
#include <time.h>
#include "sprite.h"
#include "event.h"
#include "game.h"
#include "fps.h"
#include "draw.h"
#include "weapon.h"
#include "game-state.h"

void Welcome(void)
{
	InitFps();
	char title[] = "Console Game: Ascii Shooter";
	char   bar[] = "+------------+";
	char item_1[] = "    Play    ";
	char   col[] = "|            |";
	char item_2[] = "    Quit    ";
	char illus[] = "Press Enter to continue";

	int len_title = strlen(title);
	int len_item_1 = strlen(item_1);
	int len_item_2 = strlen(item_2);
	int len_bar = strlen(bar);
	int len_col = strlen(col);
	int len_illus = strlen(illus);

	int select = 1;
	float n = 0.0f;
	while (1) {
		ClearConsoleBuffer();
		setConsoleColor(FGREEN | FRED | FOREGROUND_INTENSITY);
		DrawString((WIDTH - len_title - 1) / 2, 10, title);
		resetConsoleColor();

		DrawString((WIDTH - len_bar - 1) / 2, 14, bar);
		DrawString((WIDTH - len_col - 1) / 2, 15, col);
		DrawString((WIDTH - len_bar - 1) / 2, 16, bar);
		DrawString((WIDTH - len_bar - 1) / 2, 18, bar);
		DrawString((WIDTH - len_col - 1) / 2, 19, col);
		DrawString((WIDTH - len_bar - 1) / 2, 20, bar);

		if (select == 1) {
			setConsoleColor(BBLUE | BRED | FWHITE | FOREGROUND_INTENSITY);
			DrawString((WIDTH - len_item_1 - 1) / 2, 15, item_1);
			resetConsoleColor();
			DrawString((WIDTH - len_item_2 - 1) / 2, 19, item_2);
		}
		else {
			DrawString((WIDTH - len_item_1 - 1) / 2, 15, item_1);
			setConsoleColor(BBLUE | BRED | FWHITE | FOREGROUND_INTENSITY);
			DrawString((WIDTH - len_item_2 - 1) / 2, 19, item_2);
			resetConsoleColor();
		}

		n += 10.0f * GetPast();
		if (n > 15.0f) {
			n = 0.0f;
		}
		else if (n > 8.0f) {
			DrawString((WIDTH - len_illus - 1) / 2, 25, illus);
		}

		if (IsKeyPressed(VK_UP))
			select = 1;
		else if (IsKeyPressed(VK_DOWN))
			select = 2;
		else if (IsKeyPressed(VK_RETURN)) {
			if (select == 1)
				return;
			else
				exit(0);
		}

		UpdateFps();
		RedrawConsole();
		Sleep(1);
	}
}

int GameMainLoop()
{
	InitGameState();
	player.setPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 2);
	enemies.clear();
	bullets.clear();
	enemyBullets.clear();
	while (!GameOver()) {
		// 在窗口激活时进行以下动态时间, 调试期间论外
		if (1 || IsWindowActive()) {
			// 清空缓冲区和重绘缓冲区一定要有，期间所以字符都重画
			// TODO Movement里包含了太多的功能
			ClearConsoleBuffer();
			UpdateState();
			CreateEnemy();
			Movement();
			DrawScreen();
			RedrawConsole();
		}
	}
	return 0;
}

