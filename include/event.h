#pragma once

#include <windows.h>
#include "draw.h"
#include "fps.h"

class Entity;
class Bullet;

extern HWND	hWin;
typedef int KEYCODE;

#define PLAYER_BULLET 1
#define PLAYER_JUDGE 2
#define ENEMY_BULLET 4
#define ENEMY_JUDGE 8
#define PLAYER_BEAM 16

// 判断某键是否按下
int IsKeyPressed(KEYCODE keycode);
// 根据指定的键位状态判断是否生成子弹
void FireBullet();
// 随机产生一个敌机，在游戏区域内
void CreateEnemy();
void Movement();
void Beam();
