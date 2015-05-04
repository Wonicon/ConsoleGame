#include <assert.h>
#include <deque>
#include "draw.h"
#include "entity.h"
#include "console.h"
#include <stdio.h>
#include "weapon.h"
extern Bullets bullets;
extern Bullets enemyBullets;
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
	// Hitten
	DrawString(SCREEN_WIDTH + 1, line++, "Hits %d", hitten);
	DrawString(SCREEN_WIDTH + 1, line++, "P %.0f", beampower);

	// 绘制自机
	player.draw();

	// 绘制子弹
	bullets.draw();
	enemyBullets.draw();
	
	// 绘制敌人
	for (deque<Entity>::iterator itr = enemies.begin(); itr != enemies.end(); itr++) {
		itr->draw();
	}
}

