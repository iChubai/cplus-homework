#include"enemy.h"
#include"config.h"
#include <QPixmap>
Enermy::Enermy()
{
    //资源的加载
    m_enermy.load(ENERMY_PATH);
    m_enermy1.load(ENERMY_PATH1);
    m_enermy2.load(ENERMY_PATH2);
    m_enermy3.load(ENERMY_PATH3);
    m_enermy4.load(ENERMY_PATH4);
    m_enermy5.load(ENERMY_PATH5);
    m_enermy6.load(ENERMY_PATH6);
    //仙人掌位置
    m_x = 1500;
    m_y = 680;

    //仙人掌状态
    m_Free = true;

    //仙人掌速度
    m_Speed = ENERMY_SPEED;

    //仙人掌边框（碰撞检测）
    m_Rect.setWidth(m_enermy.width());
    m_Rect.setHeight(m_enermy.height());
    m_Rect.moveTo(m_x, m_y - 50);

    m_Rect1.setWidth(30);
    m_Rect1.setHeight(15);
    m_Rect1.moveTo(m_x, m_y - 30);

    m_Rect2.setWidth(30);
    m_Rect2.setHeight(15);
    m_Rect2.moveTo(m_x, m_y - 40);

    m_Rect3.setWidth(30);
    m_Rect3.setHeight(15);
    m_Rect3.moveTo(m_x, m_y - 40);

    m_Rect4.setWidth(30);
    m_Rect4.setHeight(15);
    m_Rect4.moveTo(m_x, m_y - 40);

    m_Rect5.setWidth(30);
    m_Rect5.setHeight(15);
    m_Rect5.moveTo(m_x, m_y - 30);

    m_Rect6.setWidth(80);
    m_Rect6.setHeight(15);
    m_Rect6.moveTo(m_x, m_y - 40);
}
