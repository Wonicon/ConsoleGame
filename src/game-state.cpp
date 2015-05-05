#include <Windows.h>
#include <Winuser.h>
#include "game-state.h"

GameState state;

enum KEYCODE {
	K_A = 0x41,
	K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M,
	K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y,
	K_Z
};

void InitGameState(void)
{
	state.playerState = ALIVE;
	state.level = EASY;
	state.twoWayShot = false;
	state.hShot = false;
	state.vShot = false;
	state.beam = false;
	state.up = false;
	state.down = false;
	state.left = false;
	state.right = false;
	state.hitCount = 0;
}

void UpdateState(void)
{
	state.hShot = IsKeyPressed(K_Z);
	state.vShot = IsKeyPressed(K_X);
	state.twoWayShot = IsKeyPressed(K_C);
	state.beam = IsKeyPressed(VK_SPACE);
	state.up = IsKeyPressed(VK_UP);
	state.down = IsKeyPressed(VK_DOWN);
	state.left = IsKeyPressed(VK_LEFT);
	state.right = IsKeyPressed(VK_RIGHT);
}

bool GameOver(void)
{
	return state.playerState == DEAD;
}