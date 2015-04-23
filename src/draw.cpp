#include <assert.h>
#include <deque>
#include "draw.h"
#include "object.h"
#include "console.h"
#include "spirit.h"

// 绘制字符串
void DrawString(int x, int y, const char *str) 
{
	WriteString(x, y, str, strlen(str), DEFAULT_ATTR);
}
// 竖向绘制字符串
void DrawColumn(int x, int y, const char *str)
{
	WriteColumn(x, y, str, strlen(str), DEFAULT_ATTR);
}
// 竖向输出重复字符
void RepDrawColumn(int x, int y, int n, char ch)
{
	char *p = new char[n + 1];
	memset(p, ch, n);
	p[n] = '\0';
	WriteColumn(x, y, p, strlen(p), DEFAULT_ATTR);
}
// 绘制单个对象
void DrawObject(Object& obj) {
	CHAR_INFO buf[WIDTH * HEIGHT];
	COORD pos = { obj.x, obj.y };
	COORD sz = { obj.width, obj.height };
	for (int i = 0; i < obj.width * obj.height; i++) {
		buf[i].Char.AsciiChar = obj.image[i];
		buf[i].Attributes = DEFAULT_ATTR;
	}
	WriteBlock(pos, sz, buf);
}


#include <stdio.h>
#include <Windows.h>
#pragma comment( lib,"winmm.lib" )
int start = 0;
extern int count;  // 主循环次数
extern int hitten; // 消灭敌人数量
#pragma warning(disable : 4996)
// 集中管理除字符串以外的所有绘图
void DrawScreen(void) {
	RepDrawColumn(SCREEN_WIDTH, 0, HEIGHT, '|');

	/* 输出文字信息 */
	static char temp[1024];
	int line = 0;
	// Fps
	sprintf(temp, "Fps %f", count * 1000.0f / (timeGetTime() - start));
	DrawString(SCREEN_WIDTH + 1, line++, temp);
	// Enemies
	sprintf(temp, "Enemies %d", enemies.size());
	DrawString(SCREEN_WIDTH + 1, line++, temp);
	// Bullets
	sprintf(temp, "Bullets %d", bullets.size());
	DrawString(SCREEN_WIDTH + 1, line++, temp);
	// Hitten
	sprintf(temp, "Hits %d", hitten);
	DrawString(SCREEN_WIDTH + 1, line++, temp);
	/* 移动物体 */

	// 绘制自机
	DrawObject(player);

	// 绘制子弹
	for (deque<Object>::iterator itr = bullets.begin();
		itr != bullets.end(); itr++) {
		DrawObject(*itr);
	}
	
	// 绘制敌人
	for (deque<Object>::iterator itr = enemies.begin();
		itr != enemies.end(); itr++) {
		DrawObject(*itr);
	}
}