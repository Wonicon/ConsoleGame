#include "object.h"

#pragma warning(disable : 4996)
Object::Object(COORD &position, COORD &scale, char s[], int v, int _life)
{
	x = position.X;
	y = position.Y;
	width = scale.X;
	height = scale.Y;
	speed = v;
	life = _life;
	strcpy(image, s);
}

#pragma warning(disable : 4996)
Object::Object(const Object& obj)
{
	x = obj.x;
	y = obj.y;
	width = obj.width;
	height = obj.height;
	speed = obj.speed;
	life = obj.life;
	strcpy(image, obj.image);
}
bool Object::RangeLimit(void)
{
	bool flag = true;
	if (x < 0) {
		x = 0;
		flag = false;
	}
	else if (x > SCREEN_WIDTH - width) {
		x = SCREEN_WIDTH - width;
		flag = false;
	}
	if (y < 0) {
		y = 0;
		flag = false;
	}
	else if (y > HEIGHT - height) {
		y = HEIGHT - height;
		flag = false;
	}
	return flag;
}
bool Object::isInWindow(COORD pos, COORD window)
{
	int left = x - pos.X;
	int right = pos.X + window.X - x - width;
	int up = y - pos.Y;
	int down = pos.Y + window.Y - y - height;
	return left >= 0 && right >= 0 && up >= 0 && down >= 0;
}