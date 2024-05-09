#include "Dinosaur.h"
#include <qpainter.h>
#include <qrect>
#include "config.h"
#include <QIcon>
#include<QPushButton>
#include<QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <qtimer>
#include <Qtglobal>
#include "enemy.h"
#include <random>
#include "cloud.h"
#include <QPainterPath>
#include "kunkun.h"
#include "button.h"
#include <QGraphicsScene>
Dinosaur::Dinosaur(QWidget *parent)
    : QMainWindow(parent),y(645.0),v(0.0),g(0.08),a(1),ground(645),is_jumping(false),is_releasing(false),is_flying(false),dis_flying(),last_v(0.0)
{
    ui.setupUi(this);
    this->setGeometry(100, 50, 1500,900);
    
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
    lsz22.load(lsz22_PATH);
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);
    m_map1_posX = 700;
    m_map2_posX = 0;
    m_scroll_speed = MAP_SCROLL_SPEED_1;
    d_x = 40;
    d_y = 700;
    d_rect.setWidth(90);
    d_rect.setHeight(90);
    d_rect.moveTo(d_x, d_y);
    jump_once = false;
    jump_twice = false;
    sprint_once = false;
    sprint_twice = false;
   // time->start(50);
   // connect(time, SIGNAL(timeout()), this, SLOT(dinoo()));
    
    //Button* button = new Button(m_timer);
    //button->setPos(970, 20);
    //scene->addItem(button);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_Icon));
    m_timer.setInterval(GAME_RATE);
    m_restartBtn = new QPushButton(this);
    m_restartBtn->setIcon(QIcon(RESTART));
    m_restartBtn->setFixedSize(100, 100);
    m_restartBtn->move(700, 400);
    m_restartBtn->setVisible(false);
    m_restartBtn->setFocusPolicy(Qt::NoFocus);
    connect(m_restartBtn, &QPushButton::clicked, this, &Dinosaur::restartGame);
    m_recorder = 0;
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
          if(dino_change==1)  paint.drawPixmap(d_x-40, d_y-50, 250, 250, Dinosaur_max1);
          if(dino_change==2)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max2);
          if(dino_change==3)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max3);
          if(dino_change==4)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max4);
          if (dino_change == 5)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max5);
          if (dino_change == 6)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max6);
          if (dino_change == 7)  paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, Dinosaur_max7);
          if (dino_change == 8)  paint.drawPixmap(d_x-40 , d_y -50, 250, 250, Dinosaur_max8);
          if (dino_change == 9)    paint.drawPixmap(d_x - 40, d_y - 50, 250, 250, lsz);
    }
    for (int i = 0;i < ENERMY_NUM; i++)
    {
        if (m_enermys[i].m_Free == false)
        {
            paint.drawPixmap(m_enermys[i].m_x, m_enermys[i].m_y,150,150, m_enermys[i].m_enermy);
        }
    }

    for (int i = 0;i < CLOUD_NUM; i++)
    {
        if (c_clouds[i].c_Free == false)
        {
            paint.drawPixmap(c_clouds[i].c_x, c_clouds[i].c_y, c_clouds[i].c_cloud);
        }
    }
    for (int i = 0;i < KUN_NUM; i++)
    {
        if (k_kuns[i].k_free == false)
        {
            paint.drawPixmap(k_kuns[i].k_x, k_kuns[i].k_y+470,200,200, k_kuns[i].ikun);
        }
    }

    for (int i = 0;i < BIRD_NUM; i++)
    {
        if (b_birds[i].b_free == false)
        {
            static int frame1 = 0;
            static int frame2 = 0;
            frame1++;
            frame2++;
            if (frame1 >= 40) {
                frame1 = 0;
            }

            if (frame1 < 20) {
                paint.drawPixmap(b_birds[i].b_x, b_birds[i].b_y , b_birds[i].b_bird1);
            }
            else {
                paint.drawPixmap(b_birds[i].b_x, b_birds[i].b_y , b_birds[i].b_bird2);
            }
        }
    }
    for (int i = 0;i < HEART_NUM; i++)
    {
        if (h_hearts[i].h_Free == false)
        {
            paint.drawPixmap(h_hearts[i].h_x, h_hearts[i].h_y, h_hearts[i].h_heart);
        }
    }
    //画左上角爱心
    paint.scale(0.5, 0.5);
    paint.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    paint.setPen(Qt::NoPen);
    paint.setBrush(Qt::red);

    // 绘制爱心左半部分
    QPainterPath path1;
    path1.moveTo(75, 40);
    path1.cubicTo(75, 15, 50, 0, 25, 0);
    path1.cubicTo(0, 0, 0, 30, 0, 30);
    path1.cubicTo(0, 60, 75, 105, 75, 105);
    path1.cubicTo(75, 105, 150, 60, 150, 30);
    path1.cubicTo(150, 30, 150, 0, 125, 0);
    path1.cubicTo(100, 0, 75, 15, 75, 40);
    paint.drawPath(path1);

    // 绘制爱心右半部分
    QPainterPath path2;
    path2.moveTo(75, 40);
    path2.cubicTo(75, 15, 100, 0, 125, 0);
    path2.cubicTo(150, 0, 150, 30, 150, 30);
    path2.cubicTo(150, 60, 75, 105, 75, 105);
    path2.cubicTo(75, 105, 0, 60, 0, 30);
    path2.cubicTo(0, 30, 0, 0, 25, 0);
    path2.cubicTo(50, 0, 75, 15, 75, 40);
    paint.drawPath(path2);

    // 绘制生命
    QFont font("Arial", 30, QFont::Bold);
    paint.setFont(font);
    paint.setPen(Qt::black);
    paint.drawText(55, 75, QString::number(m_gameover));

    // 绘制得分
    QFont font1;
    font.setPointSize(20);
    paint.setFont(font);
    paint.setPen(Qt::red);
    paint.drawText(rect().adjusted(0, 0, -10, 0), Qt::AlignRight | Qt::AlignTop, QString("Your mark : %1").arg(mark / 10));

    if (lsz_flag) {
        paint.drawPixmap(lsz22_x, lsz22_y, lsz22);
    }

    if (m_gameover == 0) { // 游戏结束，显示重新开始按钮
        m_restartBtn->setVisible(true);
    }
    else { // 游戏未结束，隐藏重新开始按钮
        m_restartBtn->setVisible(false);
    }
}
void Dinosaur::mapPosition()
{
    //第一张滚动
    if (this->sprint_Timer.isActive()) {
        m_map1_posX -= MAP_SCROLL_SPEED_2;     //向左
        if (m_map1_posX <= 0)
        {
            m_map1_posX = 2400;
        }

        //第二张
        m_map2_posX -= MAP_SCROLL_SPEED_2;
        if (m_map2_posX <= -2400)
        {
            m_map2_posX = 0;
        }
    }
    else {
        m_map1_posX -= MAP_SCROLL_SPEED_1;     //向左
        if (m_map1_posX <= 0)
        {
            m_map1_posX = 2400;
        }

        //第二张
        m_map2_posX -= MAP_SCROLL_SPEED_1;
        if (m_map2_posX <= -2400)
        {
            m_map2_posX = 0;
        }
    }
}
void Dinosaur::lszPosition()
{  }
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
     setposition(d_x, y);
     last_h = y;
}
void Dinosaur::gamestart()
{
    m_timer.start();
    connect(&m_timer, &QTimer::timeout, [=]() {

        //dinoo();
        enermyToScene();

        birdToScene();

        cloudToScene();

        heartToScene();
        kunkunToScene();

       // updatePosition();

       // updateMark();
       
        mapPosition();
       enemy_updatePosition();
       cloud_updatePosition();
       bird_updatePosition();
       heart_updateposition();
       kun_updatePosition();
       updatePositionY();
       update();
        if (checkCollision())
        {
            m_gameover++;
            //QSound::play(REACH);
        }
        if (collisiondDetection() || checkbirdCollision()||checkkunkunCollision()) { // 检查碰撞
            m_gameover--;
            //QSound::play(HIT);
            if (m_gameover == 0)
                m_timer.stop();
            m_restartBtn->setVisible(true);
            // 标记游戏结束
        }
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
    for (int i = 0; i < ENERMY_NUM; i++) {
        m_enermys[i].m_Free = true;
    }


    for (int i = 0;i < ENERMY_NUM; i++)
    {

        m_enermys[i].m_x = -100;

    }

    for (int i = 0; i < BIRD_NUM; i++) {
        b_birds[i].b_free = true;
    }
    for (int i = 0;i < BIRD_NUM; i++)
    {

        b_birds[i].b_x = -100;

    }

    for (int i = 0; i < HEART_NUM; i++) {
        h_hearts[i].h_Free = true;
    }
    for (int i = 0;i < HEART_NUM; i++)
    {

        h_hearts[i].h_x = -100;

    }

    m_timer.start();
    //仙人掌出场
    //绘制到屏幕中
    //重新绘制窗口中所有信息
    enermyToScene();
    birdToScene();

    cloudToScene();

    heartToScene();
    enemy_updatePosition();
    cloud_updatePosition();
    bird_updatePosition();
    heart_updateposition();
    mapPosition();
    updatePositionY();
    update();
    if (checkCollision())
    {
       // m_gameover++;
    }
    if (collisiondDetection()) { // 检查碰撞
        m_gameover--;
        if (m_gameover == 0)
            m_timer.stop();
      //  m_restartBtn->setVisible(true);
    }
}
void Dinosaur::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space && !is_jumping) {



        //QSound::play(JUMP);
        qDebug()<<m_gameover;
    }
    if (event->key() == Qt::Key_Space && !is_jumping && y == ground) {

        is_jumping = true;
        v = -6.5;
        is_jumping = true;
        is_releasing = false;
        jump();
    }
    if (event->key() == Qt::Key_Shift)
    {
        sprint();
    }
    if (event->key() == Qt::Key_E)
    {
        dino_flag = false;
        if (dino_change < 9)dino_change++;
        else dino_change = 1;
    }
    /*if (event->key() == Qt::Key_M)
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
    }*/
    if (event->key() == Qt::Key_Q) {
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
    //感觉很拉跨 想删掉
   if (event->key() == Qt::Key_A) {
        d_x -= 30;
    }
    if (event->key() == Qt::Key_D) {
        d_x += 30;
    }
}
void Dinosaur::keyReleaseEvent(QKeyEvent* event)
{

    if (event->key() == Qt::Key_Space && is_jumping) {

        is_jumping = false;
        is_releasing = true;
        last_v = v;
    }
    if (event->key() == Qt::Key_Shift) {
      
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
            m_enermys[i].m_y = 725 - m_enermys[i].m_enermy.height();
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
void Dinosaur::cloud_updatePosition()
{
    for (int i = 0;i < CLOUD_NUM;i++)
    {
        if (c_clouds[i].c_Free)
        {
            return;
        }
        c_clouds[i].c_x -= c_clouds[i].c_Speed;
        if (c_clouds[i].c_x <= -100) {
            c_clouds[i].c_Free = true;
        }
    }
}
void Dinosaur::cloudToScene()
{
    c_recorder++;
    if (c_recorder < CLOUD_INTERVAL)
    {
        return;
    }

    c_recorder = 0;
    for (int i = 0;i < CLOUD_NUM; i++)
    {
        if (c_clouds[i].c_Free)
        {

            QPixmap pixmap;
            pixmap.load(CLOUD_PATH);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0, 150);
            int qrand = dis(gen);
            c_clouds[i].c_cloud = pixmap;
            c_clouds[i].c_Free = false;
            c_clouds[i].c_x = 1500;
            c_clouds[i].c_y = qrand;
            break;
        }
    }
}
void Dinosaur::birdToScene() {
    b_recorder++;
    if (b_recorder < BIRD_INTERVAL)
    {
        return;
    }

    b_recorder = 0;
    for (int i = 0;i < BIRD_NUM; i++)
    {
        if (b_birds[i].b_free)
        {

            b_birds[i].b_free = false;
            QPixmap pixmap;
            pixmap.load(BIRD_PATH);


            b_birds[i].b_bird = pixmap;
            b_birds[i].b_free = false;
            b_birds[i].b_x = 1500 + 50;
            b_birds[i].b_y = 120;

            break;
        }
    }
}
void Dinosaur::bird_updatePosition(){
    for (int i = 0;i < BIRD_NUM;i++) {
        if (b_birds[i].b_free)
        {
            return;
        }
        b_birds[i].b_x -= b_birds[i].b_speed;
        b_birds[i].b_Rect.moveTo(b_birds[i].b_x, b_birds[i].b_y);
        if (b_birds[i].b_x <= -100)
        {
            b_birds[i].b_free = true;
        }
    }
}
void Dinosaur::heartToScene() {
    h_recorder++;
    if (h_recorder < HEART_INTERVAL)
    {
        return;
    }

    h_recorder = 0;
    for (int i = 0;i < HEART_NUM; i++)
    {
        if (h_hearts[i].h_Free)
        {


            QPixmap pixmap;
            pixmap.load(HEART_PATH);


            h_hearts[i].h_Collision.setWidth(1);
            h_hearts[i].h_Collision.setHeight(1);


            h_hearts[i].h_heart = pixmap;
            h_hearts[i].h_Free = false;
            h_hearts[i].h_x = 1500 + 50;
            h_hearts[i].h_y = 650;

            break;
        }
    }

}
void Dinosaur::heart_updateposition() {
    for (int i = 0;i < ENERMY_NUM;i++) {
        //空闲爱心状态 不计算坐标
        if (h_hearts[i].h_Free)
        {
            return;
        }

        h_hearts[i].h_x -= h_hearts[i].h_Speed;
        h_hearts[i].h_Rect.moveTo(h_hearts[i].h_x,h_hearts[i].h_y);

        //如果超出屏幕 重置空闲状态
        if (h_hearts[i].h_x <= -50)
        {
           h_hearts[i].h_Free = true;
        }
    }

}
void Dinosaur::kunkunToScene() {
    k_recorder++;
    if (k_recorder < KUN_INTERVAL)
    {
        return;
    }
    k_recorder = 0;
    for (int i = 0;i < KUN_NUM;i++)
    {
        if (k_kuns[i].k_free)
        {
            k_kuns[i].k_free = false;
            QPixmap pixmap;
            pixmap.load(KUN_PATH);
            k_kuns[i].ikun = pixmap;
            k_kuns[i].k_free = false;
            k_kuns[i].k_x = 1500 + 50;
            k_kuns[i].k_y = 120;
            break;
        }
    }
}
void Dinosaur::kun_updatePosition() {
    for (int i = 0;i < KUN_NUM;i++)
    {
        if (k_kuns[i].k_free)
        {
            return;
        }
        k_kuns[i].k_x -= k_kuns[i].k_Speed;
        k_kuns[i].k_Rect.moveTo(k_kuns[i].k_x, k_kuns[i].k_y);
        if (k_kuns[i].k_x <= -100)
        {
            k_kuns[i].k_free = true;
        }
    }

}
bool Dinosaur::collisiondDetection()
{
    QRect dinosaurRect(d_x,d_y,Dinosaur1.width(),Dinosaur1.height());
    for (int i = 0; i < ENERMY_NUM; i++)
    {
        if (m_enermys[i].m_Free == false) {
            QRect enermyRect(m_enermys[i].m_x, m_enermys[i].m_y, m_enermys[i].m_enermy.width(), m_enermys[i].m_enermy.height());
            if (dinosaurRect.intersects(enermyRect))
            {
                m_enermys[i].m_Free = true;
                return true; // 碰撞检测成功
            }
        }
        return false; // 没有碰撞
    }
}
bool Dinosaur::checkbirdCollision()
{
    QRect dinosaurRect(d_x, d_y, Dinosaur1.width(), Dinosaur1.height());
    for (int i = 0; i < BIRD_NUM; i++)
    {
        if (b_birds[i].b_free == false) {
            QRect enermyRect(b_birds[i].b_x, b_birds[i].b_y, b_birds[i].b_bird.width(), b_birds[i].b_bird.height());
            if (dinosaurRect.intersects(enermyRect))
            {
                b_birds[i].b_free = true;
                return true; // 碰撞检测成功
            }
        }
        return false; // 没有碰撞
    }
}
bool Dinosaur::checkkunkunCollision() {
    QRect dinosaurRect(d_x, d_y, Dinosaur1.width(), Dinosaur1.height());
    for (int i = 0; i < KUN_NUM; i++)
    {
        if (k_kuns[i].k_free == false) {
            QRect enermyRect(k_kuns[i].k_x, k_kuns[i].k_y, k_kuns[i].ikun.width(), k_kuns[i].ikun.height());
            if (dinosaurRect.intersects(enermyRect))
            {
                k_kuns[i].k_free = true;
                return true; // 碰撞检测成功
            }
        }
        return false; // 没有碰撞
    }
}
bool Dinosaur::checkCollision()
{

    QRect dinoRect(d_x, d_y, Dinosaur1.width(), Dinosaur1.height());
    for (int i = 0; i < HEART_NUM; i++) {
        if (h_hearts[i].h_Free == false) {
            QRect heartRect(h_hearts[i].h_x, h_hearts[i].h_y, h_hearts[i].h_heart.width(), h_hearts[i].h_heart.height());
            if (dinoRect.intersects(heartRect)) {

                h_hearts[i].h_Free = true;

                return true;
            }
        }
        return false;
    }
}
void Dinosaur::jump() {
    if (y = ground) {
        jump_once = false;
        jump_twice = false;
    }
    if(jump_twice||jump_Timer.remainingTime()>200&&jump_Timer.isActive())
    {
        return;
    }
    if (y = ground) {
        jump_Timer.start();
        jump_once = true;
    }
    if (y < ground && !jump_twice) {
        jump_Timer.start();
        jump_twice = true;
    }

}
void Dinosaur::updatePositionY() {
    if (jump_Timer.isActive()) {
        y -= jump_Timer.remainingTime() / 45;
    }
    else {
        v += 0.03;              //下落加速度
        y += v;
    }
    if (y >= ground) {
        y = ground;
    }
    setposition(d_x, y);
}
void Dinosaur::sprint() {
    if (!sprint_interval_Timer.isActive()) {
        sprint_once = false;
        sprint_twice = false;
    }
    if (sprint_twice || (sprint_Timer.remainingTime() > 5 && sprint_Timer.isActive())) {
        return;
    }
    if (!sprint_once) {
        sprint_once = true;
        sprint_Timer.start();
        sprint_interval_Timer.start();
    }
    else if (!sprint_twice) {
        sprint_twice = true;
        sprint_Timer.start();
    }
}
void Dinosaur::on_restart_clicked()
{
    //ui->groupBox->hide();
   // gamestart();
}
void Dinosaur::on_return_main_clicked()
{
    //ui->groupBox->hide();
    //ui->score->hide();
    //ui->distance->hide();
   // ui->start->show();
    //ui->intro->show();
    //update();
}