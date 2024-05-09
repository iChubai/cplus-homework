#include "Dinosaur.h"
#include <qpainter.h>
#include <qrect>
#include "config.h"
#include <QIcon>
#include<QPushButton>
#include<QKeyEvent>
#include <QTime>
#include <QDebug>
#include <qtimer>
#include <Qtglobal>
#include "enemy.h"
#include <random>
Dinosaur::Dinosaur(QWidget *parent)
    : QMainWindow(parent),y(645.0),v(0.0),g(0.08),a(1),ground(645),is_jumping(false),is_releasing(false),is_flying(false),dis_flying(),last_v(0.0)
{
    ui.setupUi(this);
    this->setGeometry(100, 50, 1500,900 );
    
    Dinosaur1.load(GAME_Dinopic1);
    Dinosaur2.load(GAME_Dinopic2);
    Dinosaur3.load(GAME_Dinopic3);
    Dinosaur4.load(GAME_Dinopic4);
    Dinosaur_max1.load(GAME_Dinomaxpic1);
    Dinosaur_max2.load(GAME_Dinomaxpic2);
    Dinosaur_max3.load(GAME_Dinomaxpic3);
    Dinosaur_max4.load(GAME_Dinomaxpic4);
    Dinosaur_max5.load(GAME_Dinomaxpic5);
    Dinosaur_max6.load(GAME_Dinomaxpic6);
    Dinosaur_max7.load(GAME_Dinomaxpic7);
    Dinosaur_max8.load(GAME_Dinomaxpic8);
    lsz.load(GAME_lsz);
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);
    m_map1_posX = 700;
    m_map2_posX = 0;
    m_scroll_speed = MAP_SCROLL_SPEED;
   
    d_x = 40;
    d_y = 700;
    d_rect.setWidth(90);
    d_rect.setHeight(90);
    d_rect.moveTo(d_x, d_y);
   // time->start(50);
   // connect(time, SIGNAL(timeout()), this, SLOT(dinoo()));
    
    
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_Icon));
    
    m_restartBtn = new QPushButton(this);
    m_restartBtn->setIcon(QIcon(RESTART));
    m_restartBtn->setFixedSize(100, 100);
    m_restartBtn->move(700, 400);
    m_restartBtn->setVisible(false);
    connect(m_restartBtn, &QPushButton::clicked, this, &Dinosaur::restartGame);
    
    gamestart();
}
void Dinosaur::dinoo() {
    update();
}
Dinosaur::~Dinosaur()
{}
void Dinosaur::setposition(int x, int y) {
    d_x = x;
    d_y = y;
    d_rect.moveTo(d_x, d_y);
}
void Dinosaur::paintEvent(QPaintEvent* event)
{
    QPainter paint(this);
    //paint.drawPixmap(40,650,150,150,Dinosaur1);
    paint.drawPixmap(m_map1_posX,790,3500,40,m_map1);
    paint.drawPixmap(m_map2_posX,790,3500,40, m_map2);
    if (dino_flag) {
        if (d_y == ground) {
            static int frame = 0;
            frame++;
            if (frame >= 20) {
                frame = 0;
            }
            if (frame < 10) {
                paint.drawPixmap(d_x, d_y, 150, 150, Dinosaur2);
            }
            else {
                paint.drawPixmap(d_x, d_y, 150, 150, Dinosaur3);
            }
        }
        else {
            paint.drawPixmap(d_x, d_y, 150, 150, Dinosaur4);
        }
    }
    else {
          if(dino_change==1)  paint.drawPixmap(d_x-40, d_y-50, 200, 200, Dinosaur_max1);
          if(dino_change==2)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max2);
          if(dino_change==3)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max3);
          if(dino_change==4)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max4);
          if (dino_change == 5)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max5);
          if (dino_change == 6)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max6);
          if (dino_change == 7)  paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, Dinosaur_max7);
          if (dino_change == 8)  paint.drawPixmap(d_x-40 , d_y -50, 200, 200, Dinosaur_max8);
          if (dino_change == 9)    paint.drawPixmap(d_x - 40, d_y - 50, 200, 200, lsz);
    }
    for (int i = 0;i < ENERMY_NUM; i++)
    {
        if (m_enermys[i].m_Free == false)
        {
            paint.drawPixmap(m_enermys[i].m_x, m_enermys[i].m_y,150,150, m_enermys[i].m_enermy);
        }
    }
}
void Dinosaur::mapPosition()
{
    //第一张滚动
    m_map1_posX -= m_scroll_speed;     //向左
    if (m_map1_posX <= 0)
    {
        m_map1_posX = 2400;
    }

    //第二张
    m_map2_posX -= m_scroll_speed;
    if (m_map2_posX <= -2400)
    {
        m_map2_posX = 0;
    }
}
 
void Dinosaur::onTimer(){
    if(is_flying&&!dis_flying){ 
        y -=a;
    }
    else if (is_flying && dis_flying) {
    
    }
    else if (!is_flying && dis_flying) {
        y += a;
        if (y >= ground) {
            y = ground;
            v = 0.0;
        }
    }
    else {
        if (is_jumping) {
            y += v;
            v += g;
            if (y >= ground) {
                y = ground;
                v = -v;
                is_jumping = false;
            }
        }
        else {
            if (y < ground) {
                if (is_releasing && v < 0 && y < last_h) {
                    y += v;
                    v += g;
                }
                else {
                    y += v;
                    v += g;
                    if (y >= ground) {
                        y = ground;
                        v = 0.0;
                    }
                }
            }
        }
    }
     setposition(40, y);
     last_h = y;
}
void Dinosaur::gamestart()
{
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, [=]() {

        //dinoo();
        enermyToScene();

        //birdToScene();

       // cloudToScene();

       // heartToScene();

       // updatePosition();

       // updateMark();
       mapPosition();
    
      
       update();//重新绘制窗口中所有信息
       enemy_updatePosition();

        /*if (checkCollision())
        {
            m_gameover++;
            //QSound::play(REACH);
        }
        if (collisiondDetection() || checkbirdCollision()) { // 检查碰撞
            m_gameover--;
            //QSound::play(HIT);
            if (m_gameover == 0)
                m_Timer.stop();
            // 标记游戏结束
        }*/
        });
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimer()));
}
void Dinosaur::restartGame()
{
    mark = 0;
    m_gameover = 1; // 重置游戏结束标志
    y = ground; // 重置角色位置
    v = 0.0; // 重置速度
    is_jumping = false; // 重置跳跃状态
    is_jumping = false;
    is_releasing = false;

    m_restartBtn->setVisible(false);
    // 重新初始化游戏

    m_timer.start();
    //仙人掌出场
    //绘制到屏幕中
    update();//重新绘制窗口中所有信息

   /* if (checkCollision())
    {
        m_gameover++;
    }
    if (collisiondDetection()) { // 检查碰撞
        m_gameover--;
        if (m_gameover == 0)
            m_Timer.stop();
        // 标记游戏结束*/
    }
void Dinosaur::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space && !is_jumping && y == ground) {

        is_jumping = true;
        v = -6.5;
        is_jumping = true;
        is_releasing = false;
    }
    if (event->key() == Qt::Key_Z)
    {
        dino_flag = false;
        dino_change = 1;
    }
    if (event->key() == Qt::Key_M)
    {
        dino_flag = false;
        dino_change = 2;
    }
    if (event->key() == Qt::Key_X)
    {
        dino_flag = false;
        dino_change = 3;
    }
    if (event->key() == Qt::Key_C)
    {
        dino_flag = false;
        dino_change = 4;
    }
    if (event->key() == Qt::Key_V)
    {
        dino_flag = false;
        dino_change = 5;
    }
    if (event->key() == Qt::Key_B)
    {
        dino_flag = false;
        dino_change = 6;
    }
    if (event->key() == Qt::Key_N)
    {
        dino_flag = false;
        dino_change = 7;
    }
    if (event->key() == Qt::Key_L)
    {
        dino_flag = false;
        dino_change = 8;
    }
    if (event->key() == Qt::Key_P)
    {
        dino_flag = false;
        dino_change = 9;
    }
    if (event->key() == Qt::Key_Shift) {
        dino_flag = true;
    }
    if (event->key() == Qt::Key_R)
    {
        is_flying = true;
    }
    if (event->key() == Qt::Key_T)
    {
        dis_flying = true;
    }
}
void Dinosaur::keyReleaseEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_Space && is_jumping) {

        is_jumping = false;
        is_releasing = true;
        last_v = v;
    }
    if (event->key() == Qt::Key_R ) {
        is_flying = false;
    }
    if (event->key() == Qt::Key_T) {
        dis_flying = false;
    }
} 
void Dinosaur::enermyToScene()
{
    m_recorder++;
    if (m_recorder < ENERMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;
    for (int i = 0;i < ENERMY_NUM; i++)
    {
        if (m_enermys[i].m_Free)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1, 6);
            int randomNumber = dis(gen);
            int type = randomNumber;
            QPixmap pixmap;
            if (type == 1) {
                pixmap.load(ENERMY_PATH1);
                m_enermys[i].m_Collision.setWidth(15);
                m_enermys[i].m_Collision.setHeight(25);
            }
            else if (type == 2) {
                pixmap.load(ENERMY_PATH2);
                m_enermys[i].m_Collision.setWidth(15);
                m_enermys[i].m_Collision.setHeight(25);
            }
            else if (type == 3) {
                pixmap.load(ENERMY_PATH3);
                m_enermys[i].m_Collision.setWidth(15);
                m_enermys[i].m_Collision.setHeight(25);
            }
            else if (type == 4) {
                pixmap.load(ENERMY_PATH4);
                m_enermys[i].m_Collision.setWidth(15);
                m_enermys[i].m_Collision.setHeight(25);
            }
            else if (type == 5) {
                pixmap.load(ENERMY_PATH5);
                m_enermys[i].m_Collision.setWidth(15);
                m_enermys[i].m_Collision.setHeight(25);
            }
            else if (type == 6) {
                pixmap.load(ENERMY_PATH6);
                m_enermys[i].m_Collision.setWidth(40);
                m_enermys[i].m_Collision.setHeight(25);
            }

            m_enermys[i].m_enermy = pixmap;
            m_enermys[i].m_Free = false;
            m_enermys[i].m_x = 1100 + m_enermys[i].m_enermy.width();
            m_enermys[i].m_y = 750 - m_enermys[i].m_enermy.height();
            break;
        }
    }
}
void Dinosaur::enemy_updatePosition()
{
    //空闲仙人掌状态 不计算坐标
    for (int i = 0;i < ENERMY_NUM; i++) {
        if (m_enermys[i].m_Free)
        {
            return;
        }

       m_enermys[i].m_x -= 3;
       m_enermys[i].m_Rect.moveTo(m_enermys[i].m_x,m_enermys[i]. m_y);

        //如果超出屏幕 重置空闲状态
        if (m_enermys[i].m_x <= -m_enermys[i].m_Rect.width())
        {
            m_enermys[i].m_Free = true;
        }
    }
}
