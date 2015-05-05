#pragma once

enum State
{
	ALIVE, DEAD, WIN,
	/********/
	EASY, NORMAL, HARD
};
void InitGameState(void);
void UpdateGameState(void);

struct GameState
{
	State playerState;
	State level;
	int hitCount;
	bool hShot;
	bool vShot;
	bool twoWayShot;
	bool beam;
	bool left;
	bool right;
	bool up;
	bool down;
};

extern GameState state;

void InitGameState(void);
void UpdateState(void);
bool GameOver(void);

inline bool IsKeyPressed(int keycode)
{
	short state = GetAsyncKeyState(keycode);
	if ((state & 0x8000) == 0x8000) {
		return true;
	}
	else {
		return false;
	}
}