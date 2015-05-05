﻿#include <assert.h>
#include <stdio.h>
#include "draw.h"
#include "entity.h"
#include "console.h"
#include "weapon.h"
#include "game-state.h"
#include "component.h"

extern Bullets bullets;
extern Bullets enemyBullets;

void DrawEnemy(void);

// 绘制字符串
char _drawstring_buffer[1024];
// 竖向绘制字符串
void DrawColumn(int x, int y, char str[])
{
	WriteColumn(x, y, str);
}
// 竖向输出重复字符
void RepDrawColumn(int x, int y, int n, char ch)
{
	char *p = new char[n + 1];
	memset(p, ch, n);
	p[n] = '\0';
	WriteColumn(x, y, p);
	free(p);
}
// 绘制单个对象
void DrawObject(Entity& obj)
{
	WriteBlock(obj.scr_x, obj.scr_y, obj.height, obj.width, obj.image, obj.attr);
}

#include <stdio.h>
#include <Windows.h>
#include "sprite.h"
#include "weapon.h"
#include "fps.h"

#pragma warning(disable : 4996)
// 集中管理除字符串以外的所有绘图
void DrawScreen(void) {
	RepDrawColumn(SCREEN_WIDTH, 0, HEIGHT, '|');

	// 输出文字信息
	
	// Fps
	DrawString(0, 0, "Fps %f", GetFps());
	int line = 0;
	// Enemies
	DrawString(SCREEN_WIDTH + 1, line++, "Enemies %d", enemies.size());
	// Bullets
	DrawString(SCREEN_WIDTH + 1, line++, "Hits %d", state.hitCount);
	DrawString(SCREEN_WIDTH + 1, line++, "P %.0f", beam.getPower());
	DrawString(SCREEN_WIDTH + 1, line++, "B %d", bullets.getCount());
	// 绘制自机
	player.draw();
	// 绘制子弹
	bullets.draw();
	enemyBullets.draw();
	// 绘制敌人
	DrawEnemy();

	beam.draw(state.beam);
}

