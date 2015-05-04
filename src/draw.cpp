#include <assert.h>
#include <deque>
#include "draw.h"
#include "entity.h"
#include "console.h"
#include <stdio.h>
// 绘制字符串
char _drawstring_buffer[1024];
// 竖向绘制字符串
void DrawColumn(int x, int y, CHAR str[])
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
#include "fps.h"

extern int hitten; // 消灭敌人数量
CFPS Fps;
extern float beampower;
#pragma warning(disable : 4996)
// 集中管理除字符串以外的所有绘图
void DrawScreen(void) {
	DrawString(0, 0, "hello, world");
	RepDrawColumn(SCREEN_WIDTH, 0, HEIGHT, '|');

	///* 输出文字信息 */
	int line = 0;
	// Fps
	Fps.UpdateFPS();
	DrawString(SCREEN_WIDTH + 1, line++, "Fps %.1f", Fps.GetFps());
	DrawString(SCREEN_WIDTH + 1, line++, "Past time %.1f", Fps.GetPast());
	// Enemies
	DrawString(SCREEN_WIDTH + 1, line++, "Enemies %d", enemies.size());
	// Bullets
	DrawString(SCREEN_WIDTH + 1, line++, "Bullets %d", bullets.size());
	// Hitten
	DrawString(SCREEN_WIDTH + 1, line++, "Hits %d", hitten);
	DrawString(SCREEN_WIDTH + 1, line++, "P %.0f", beampower);
	/* 移动物体 */

	// 绘制自机
	DrawObject(player);

	// 绘制子弹
	for (deque<Entity>::iterator itr = bullets.begin(); itr != bullets.end(); itr++) {
		itr->draw();
	}
	for (deque<Entity>::iterator itr = enemyBullets.begin(); itr != enemyBullets.end(); itr++) {
		itr->draw();
	}
	
	// 绘制敌人
	for (deque<Entity>::iterator itr = enemies.begin(); itr != enemies.end(); itr++) {
		itr->draw();
	}
}

