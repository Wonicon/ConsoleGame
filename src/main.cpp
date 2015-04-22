#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "spirit.h"
#include "event.h"

volatile int start;
volatile int count = 0;

int main(void)
{
	InitConsole();
	int slp = 10;
	while (1) {
		count++;

		ClearConsoleBuffer();
		if (isHitten(player, 8)) {
			break;
		}

		if (IsWindowActive()) {
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
	RedrawConsole();
	printf("You are dead!\n");
	system("pause");
	return 0;
}