#pragma once
#include <QPixmap>
#include <QRect>
class Heart
{
public:
	Heart();
	void updatePosition();
	QPixmap h_heart;
	QRectF h_Collision;
	int h_x;
	int h_y;
	QRect h_Rect;
	bool h_Free;
	int h_Speed;
};
