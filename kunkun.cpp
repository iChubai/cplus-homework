#include "kunkun.h"
#include "config.h"
#include <QPixmap>
kunkun::kunkun()
{
	ikun.load(KUN_PATH);
	k_x = 1500;
	k_y = 680;
	k_free = true;
	k_Speed = KUN_SPEED;
	k_Rect.setWidth(ikun.width());
	k_Rect.setHeight(ikun.height());
	k_Rect.moveTo(k_x, k_y - 50);
}
void kunkun::updateposition() {
	if (k_free)
	{
		return;
	}
	k_x -= k_Speed;
	k_Rect.moveTo(k_x, k_y);
	if (k_x <= -100)
	{
		k_free = true;
	}
}