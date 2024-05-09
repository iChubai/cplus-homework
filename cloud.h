#pragma once
#include <QPixmap>
#include <QRect>
class Cloud
{
public:
	Cloud();
public:
	void updatePosition();
	QPixmap c_cloud;
	int c_x;
	int c_y;
	bool c_Free;
	int c_Speed;

};