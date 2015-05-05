#pragma once

#include <windows.h>
#include "draw.h"
#include "fps.h"

typedef int KEYCODE;

// 判断某键是否按下
int IsKeyPressed(KEYCODE keycode);
// 根据指定的键位状态判断是否生成子弹
void FireBullet();
// 随机产生一个敌机，在游戏区域内
void CreateEnemy();
void Movement();
void BeamUpdate();
