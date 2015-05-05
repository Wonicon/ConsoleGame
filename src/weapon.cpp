#include "sprite.h"
#include "weapon.h"

Bullets bullets(100, 10.0f, bulletSample);
Bullets enemyBullets(100, 1.0f, enemyBulletSample);

Beam::Beam(int attr, int attack, int power, int width)
	:ent(0, 0, 1, SCREEN_HEIGHT, 0, (char *)BeamCharBuffer, (int *)BeamAttrBuffer),
	attribute(attr), attack(attack), power(power),
	maxPower(power)
{
	// 填充一个实体字符
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		BeamCharBuffer[i] = '|';
		BeamAttrBuffer[i] = attr;
	}
}
void Beam::fire(int x, int y, int dir)
{
	// x, y 是射线的起点
	// 暂时只实现上下两个方向
	ent.scr_x = x;
	if (dir == U) {
		ent.scr_y = 0;
		ent.height = y + 1;
	}
	else if (dir == D) {
		ent.scr_y = y;
		ent.height = SCREEN_HEIGHT - y;
	}
	//power -= 1.0f;
}

void Beam::draw()
{
	ent.draw();
}

void Beam::charge(float n)
{
	power += n;
	if (power > maxPower) {
		power = maxPower;
	}
}

float Beam::getPower() const
{
	return power;
}

int Beam::getAtk() const
{
	return attack;
}

Entity &Beam::getJudge(void)
{
	return ent;
}

void VShooter(int x, int y)
{
	static float N = 10.0f;
	static float n = 0.0f;
	n += N * Fps.GetPast();
	if (n > 1.0f) {
		if (IsKeyPressed(VK_SHIFT)) {
			bullets.fire(x, y, UL);
			bullets.fire(x, y, UR);
		}
		n = 0.0f;
	}
}