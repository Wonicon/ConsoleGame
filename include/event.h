#ifndef __KEY_EVENT_H__
#define __KEY_EVENT_H__

#include <windows.h>
#include "draw.h"

class Object;
class Bullet;

extern HWND	hWin;
typedef int KEYCODE;

#define PLAYER_BULLET 1
#define PLAYER_JUDGE 2
#define ENEMY_BULLET 4
#define ENEMY_JUDGE 8

// 判断某键是否按下
int IsKeyPressed(KEYCODE keycode);
// 根据指定的键位状态判断是否生成子弹
void FireBullet(KEYCODE keycode);
// 玩家移动，通过键盘控制
void PlayerMovement();
// 随机产生一个敌机，在游戏区域内
void CreateEnemy();
// 敌机自动向下移动
void EnemyAutoMove();
// 碰撞判断等常规事件处理
void CommonEvents();
// 判断指定的对象是否与被 label 标识的对象产生碰撞
bool isHitten(const Object& obj, int label);
// 初始化点阵状态
void InitState();
#endif