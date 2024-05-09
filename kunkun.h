#pragma once
#include <QPixmap>
#include"config.h"
#include <QRect>
class kunkun
{
public:
	kunkun();
public:
	QPixmap ikun;
	int k_x;
	int k_y;
	QRect k_Rect;
	bool k_free;
	int k_Speed = KUN_SPEED;
	void updateposition();
};