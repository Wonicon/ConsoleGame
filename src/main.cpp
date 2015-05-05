#include <windows.h>
#include <stdio.h>
#include "console.h"
#include "draw.h"
#include "event.h"
#include "game.h"
#include "game-state.h"
#include "sprite.h"

int main(void)
{
	InitConsole();
	Welcome();
	while (1) {
		GameMainLoop();
		ClearConsoleBuffer();
		setConsoleColor(FRED);
		DrawString((WIDTH - strlen("You are dead")) / 2, HEIGHT / 2, "You are dead");
		resetConsoleColor();
		RedrawConsole();
		while (!IsKeyPressed(VK_RETURN));
	}
	return 0;
}

