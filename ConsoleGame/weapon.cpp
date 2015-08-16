#include "sprite.h"
#include "weapon.h"
#include "game-state.h"
#include "fps.h"

Bullets bullets(100, 10.0f, bulletSample);
Bullets enemyBullets(100, 1.0f, enemyBulletSample);
Beam beam(BWHITE, 100, 1000.0f);

// 激光射线的位置受到所属对象（这个所属只是逻辑上的）的位置影响
// 所以不太需要在构造函数里指定。而激光的图像是在游戏设计时不太需要动态指定的，
// 甚至写死在全局数组里也不是不可。
// 不过暂时没有实现 1 宽度以外的激光，感觉判定点有点麻烦，可以用多个激光组合起来实现
Beam::Beam(int attr, int attack, float power)
	:ent(0, 0, 1, SCREEN_HEIGHT, 0, BeamCharBuffer, BeamAttrBuffer),
	attribute(attr), attack(attack), power(power),
	maxPower(power)
{
	// 填充一个实体字符
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		BeamCharBuffer[i] = '|';
		BeamAttrBuffer[i] = attr;
	}
}

// fire 是用来生成判定点的，不过碰撞检测函数需要检查透明字符 JMP_CHAR
// 所以 entry 一开始就要设置成可预期的最大尺寸
void Beam::fire(int x, int y, int dir, bool en)
{
	if (en && power > 5.0f) {
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

		power -= 10.0f * GetPast();
	}
}

void Beam::draw(bool en)
{
	if (en) ent.draw();
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


// Shooter 是玩家 Bullets 发射行为控制
// 主要是为了处理多个方向的子弹发射问题
// 如果在独立的函数里进行，则会分别消耗计时，导致子弹如果想同时发射
// 动画效果会受影响
void Shooter(Bullets& blt, Entity& obj, int dir)
{
	bool en = state.hShot | state.vShot | state.twoWayShot;
	if (blt.enable(en)) {
		if (state.hShot) {
			blt.fire(obj.left() - 1, obj.up(), L);
			blt.fire(obj.right() + 1, obj.up(), R);
		}
		if (state.vShot) {
			blt.fire(obj.mid(), obj.up() - 1, dir);
		}
		if (state.twoWayShot) {
			blt.fire(obj.mid(), obj.up(), dir | L);
			blt.fire(obj.mid(), obj.up(), dir | R);
		}
	}
}
