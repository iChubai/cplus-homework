#pragma once


#include<QPixmap>
#include<QRect>
#include "config.h"
class Enermy
{
public:
    Enermy();

   // void updatePosition();
public:

    QPixmap m_enermy;
    QPixmap m_enermy1;
    QPixmap m_enermy2;
    QPixmap m_enermy3;
    QPixmap m_enermy4;
    QPixmap m_enermy5;
    QPixmap m_enermy6;
    QRectF m_Collision; // ��� m_Collision ��Ա����
    //λ��
    int m_x;
    int m_y;


    QRect m_Rect;
    QRect m_Rect1;
    QRect m_Rect2;
    QRect m_Rect3;
    QRect m_Rect4;
    QRect m_Rect5;
    QRect m_Rect6;
    //״̬
    bool m_Free;
    //�ٶ�
    int m_Speed=ENERMY_SPEED;
};

