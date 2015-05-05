#pragma once

#include "entity.h"
#include "fps.h"

// ��Щ���������Ϊ��ҪƵ�ʿ��ƣ�ԭ���Ĵ��뵽���ɼ����������ظ���Ƶ�ʿ��ƽṹ
// n += Freq * Fps.getPast();
// if (n > 1.0f) {
//     ...
//     n = 0.0f;
// }
// �Ҿ������ֹ��� һ����������һ���ж���������FPS��Ϳ�����
class Beam
{
private:
	Entity ent;     // Entity���е���ͼ����ֻ��һ���ж������
	float power;
	float maxPower;
	int attack;
	int attribute;
	char BeamCharBuffer[SCREEN_HEIGHT];
	int BeamAttrBuffer[SCREEN_HEIGHT];
public:
	Beam(int attr, int attack, float power);
	void fire(int x, int y, int dir, bool en = true); // �γ������ж���ͬʱ��������
	void draw(bool en = true);                        // �����ߣ������fire֮�����
	void charge(float n);             // ����
	float getPower() const;           // �������
	int getAtk() const;               // ��ù�����
	Entity &getJudge(void);

};

class Bullets;

void Shooter(Bullets& blt, Entity& obj, int dir);
extern Bullets bullets;
extern Bullets enemyBullets;
extern Beam beam;