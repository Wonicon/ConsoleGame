#include "sprite.h"
#include "weapon.h"
#include "fps.h"

Bullets bullets(100, 10.0f, bulletSample);
Bullets enemyBullets(100, 1.0f, enemyBulletSample);
Beam beam(BWHITE, 100, 1000.0f);

// �������ߵ�λ���ܵ����������������ֻ���߼��ϵģ���λ��Ӱ��
// ���Բ�̫��Ҫ�ڹ��캯����ָ�����������ͼ��������Ϸ���ʱ��̫��Ҫ��ָ̬���ģ�
// ����д����ȫ��������Ҳ���ǲ��ɡ�
// ������ʱû��ʵ�� 1 �������ļ��⣬�о��ж����е��鷳�������ö�������������ʵ��
Beam::Beam(int attr, int attack, int power)
	:ent(0, 0, 1, SCREEN_HEIGHT, 0, BeamCharBuffer, BeamAttrBuffer),
	attribute(attr), attack(attack), power(power),
	maxPower(power)
{
	// ���һ��ʵ���ַ�
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		BeamCharBuffer[i] = '|';
		BeamAttrBuffer[i] = attr;
	}
}

// fire �����������ж���ģ�������ײ��⺯����Ҫ���͸���ַ� JMP_CHAR
// ���� entry һ��ʼ��Ҫ���óɿ�Ԥ�ڵ����ߴ�
void Beam::fire(int x, int y, int dir)
{
	// x, y �����ߵ����
	// ��ʱֻʵ��������������
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

void VShooter(Bullets& blt, int x, int y, int dir)
{
	static float n = 0.0f;
	if (FreqLock(n, 10.0f)) {
		if (IsKeyPressed(VK_SHIFT)) {
			bullets.fire(x, y, UL);
			bullets.fire(x, y, UR);
		}
	}
}