#include "heart.h"
#include "config.h"
Heart::Heart() {
	h_heart.load(HEART_PATH);
	h_x = 0;
	h_y = 0;
	h_Free = true;
	h_Speed = HEART_SPEED;
	h_Rect.setWidth(h_heart.width());
	h_Rect.setHeight(h_heart.height());
	h_Rect.moveTo(h_x, h_y);

};
void Heart::updatePosition()
{
    //���а���״̬ ����������
    if (h_Free)
    {
        return;
    }

    h_x -= h_Speed;
    h_Rect.moveTo(h_x, h_y);

    //���������Ļ ���ÿ���״̬
    if (h_x <= -50)
    {
        h_Free = true;
    }
}