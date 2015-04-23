#include <windows.h>
#include <stdio.h>
#include "console.h"
#include "draw.h"
#include "event.h"
#include "game.h"

volatile int start;
volatile int count = 0;

int main(void)
{
	InitConsole();
	while (1) {
		GameMainLoop();

		ClearConsoleBuffer();
		DrawString(0, 0, "You are dead");
		RedrawConsole();
		while (!IsKeyPressed(VK_RETURN));
	}
	return 0;
}