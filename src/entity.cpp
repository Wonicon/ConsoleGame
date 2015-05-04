#include "entity.h"
#include "fps.h"

bool Entity::isInScreen(void)
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
	else if (scr_y > SCREEN_HEIGHT - height) {
		scr_y = SCREEN_HEIGHT - height;
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

#include <math.h>
bool Entity::move(int newDir)
{
	if (newDir == CONS)
		newDir = dir;
	else if (newDir == STOP)
		return true;

	offset += Fps.GetPast() * vel;
	if (offset > 1.0f) {
		float floorOffset = floor(offset);
		switch (newDir) {
		case U:  scr_y -= floorOffset; break;
		case D:  scr_y += floorOffset; break;
		case L:  scr_x -= floorOffset; break;
		case R:  scr_x += floorOffset; break;
		case UL: scr_x -= floorOffset; scr_y -= floorOffset; break;
		case UR: scr_x += floorOffset; scr_y -= floorOffset; break;
		case DL: scr_x -= floorOffset; scr_y += floorOffset; break;
		case DR: scr_x += floorOffset; scr_y += floorOffset; break;
		}
		offset = 0.0f;
	}

	dir = newDir;

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

void Entity::draw()
{
	WriteBlock(scr_x, scr_y, height, width, image, attr);
}

/*******************************************
   isCollide 检查 obj 是否碰撞到 hitter
*******************************************/
bool Entity::collide(Entity &hitter)
{
	for (int i = scr_x; i < scr_x + width; i++) {
		for (int j = scr_y; j < scr_y + height; j++) {
			if (image[i + j * width] == JMP_CHAR) {
				continue;
			}
			if (hitter.isInImage(i, j)) {
				return true;
			}
		}
	}
	return false;
}

void Entity::del(void)
{
	toDel = true;
}
bool Entity::isDel(void) const
{
	return toDel;
}