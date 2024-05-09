#pragma once
#include <QPixmap>
#include <QRect>
class Bird
{
public:
	Bird();
	void updateposition();
	QPixmap b_bird;
	QPixmap b_bird1;
	QPixmap b_bird2;
	QRectF b_Collision;
	int b_x;
	int b_y;
	QRect b_Rect;
	bool b_free;
	int b_speed;

};