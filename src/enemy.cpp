#include "enemy.h"
#include "fps.h"

int Enemies::decision(Entity& me, Entity& he)
{
	int dir = STOP;
	if (me.scr_x + me.width < he.scr_x)
		dir |= R;
	else if (me.scr_x > he.scr_x + he.width)
		dir |= L;
	if (me.scr_y + me.height < he.scr_y)
		dir |= D;
	else if (me.scr_y < he.scr_y + he.height)
		dir |= U;
	return dir;
}
#include "draw.h"
void Enemies::fire(Bullets& blt, Entity& obj)
{
	srand(timeGetTime());
	int r;
	int size = getSize();
	PEntity p;
	for (int i = 0; i < LEN; i++) {
		if (FreqLock(t[i], 1.0f, entries[i] != NULL)) {
			p = entries[i];
			r = rand() % 1000;
			if (r < 200) {
				blt.fire(p->mid(), p->down() + 1, decision(*p, obj), true);
			}
			else if (r < 500) {
				blt.fire(p->mid(), p->down() + 1, D);
			}
		}
	}
}

extern Entity enemySample;
void Enemies::add(void)
{
	if (!FreqLock(t1, freq, true))
		return;

	enemySample.scr_x = rand() % (SCREEN_WIDTH - 3);
	enemySample.scr_y = 1;
	enemySample.dir = D;

	addNewEntity(enemySample);
}