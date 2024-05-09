#include "bird.h"
#include "config.h"
Bird::Bird()
{
	b_bird.load(BIRD_PATH);
	b_bird1.load(BIRD_PATH1);
	b_bird2.load(BIRD_PATH2);
	b_x = 1550;
	b_y = 100;
	b_free = true;
	b_speed = BIRD_SPEED;
	b_Rect.setWidth(20);
	b_Rect.setHeight(10);
	b_Rect.moveTo(b_x, b_y);
}
void Bird::updateposition() {
	if (b_free)
	{
		return;
	}
	b_x -= b_speed;
	b_Rect.moveTo(b_x, b_y);
	if (b_x <= -100)
	{
		b_free = true;
	}
}