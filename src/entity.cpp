#include "entity.h"
#include "fps.h"

#pragma warning(disable : 4996)
Entity::Entity(int x, int y, int w, int h, int v, int hp, int attack, char img[], int attribute[])
{
	real_x = (float)(scr_x = x);
	real_y = (float)(scr_y = y);
	width = w;
	height = h;
	vel = v;
	life = hp;
	atk = attack;
	strcpy(image, img);
	memcpy(attr, attribute, w * h * sizeof(int));
	dir = STOP;
}
bool Entity::rangeLimit(void)
{
	bool flag = true;
	if (scr_x < 0) {
		scr_x = 0;
		flag = false;
	}
	else if (scr_x > SCREEN_WIDTH - width) {
		scr_x = SCREEN_WIDTH - width;
		flag = false;
	}
	if (scr_y < 0) {
		scr_y = 0;
		flag = false;
	}
	else if (scr_y > HEIGHT - height) {
		scr_y = HEIGHT - height;
		flag = false;
	}
	return flag;
}
bool Entity::isInWindow(int x0, int y0, int w, int h)
{
	int left = scr_x - x0;
	int right = x0 + w - scr_x - width;
	int up = scr_y - y0;
	int down = y0 + h - scr_y - height;
	return left >= 0 && right >= 0 && up >= 0 && down >= 0;
}
bool Entity::isHitWindow(int x0, int y0, int w, int h)
{
	int left = scr_x - x0;
	int right = x0 + w - scr_x - width;
	int up = scr_y - y0;
	int down = y0 + h - scr_y - height;
	return left >= 0 || right >= 0 || up >= 0 || down >= 0;
}
bool Entity::move(int new_dir = CONS)
{
	if (new_dir == CONS)
		new_dir = dir;

	float distance = Fps.GetPast() * vel;

	if (new_dir != dir)  // 转向或停止
	{
		real_x = (float)scr_x;
		real_y = (float)scr_y;
	}

	switch (new_dir)
	{
	case U:  real_y -= distance; break;
	case D:  real_y += distance; break;
	case L:  real_x -= distance; break;
	case R:  real_x += distance; break;
	case UL: real_x -= distance; real_y -= distance; break;
	case UR: real_x += distance; real_y -= distance; break;
	case DL: real_x -= distance; real_y += distance; break;
	case DR: real_x += distance; real_y += distance; break;
	case STOP: real_x = (float)scr_x; real_y = (float)scr_y; break;
	}

	dir = new_dir;
	scr_x = (int)real_x;
	scr_y = (int)real_y;

	bool flag = true;
	if (scr_y > SCREEN_HEIGHT - height)
		scr_y = SCREEN_HEIGHT - height, flag = false;
	else if (scr_y < 0)
		scr_y = 0, flag = false;

	if (scr_x > SCREEN_WIDTH - width)
		scr_x = SCREEN_WIDTH - width, flag = false;
	else if (scr_x < 0)
		scr_x = 0, flag = false;

	return flag;
}

