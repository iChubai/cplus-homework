#pragma once
#include<QGraphicsScene>
#include<QTimer>
#include<QGraphicsView>
#include <QtWidgets/QMainWindow>
#include "ui_Dinosaur.h"
#include <QPixmap>
#include <qtimer>
#include <Qpainter>
#include <QRect>
#include <QKeyEvent>
#include <QPushButton>
#include <QMouseEvent>
#include "enemy.h"
#include "config.h"
#include "cloud.h"
#include "bird.h"
#include "heart.h"
#include "kunkun.h"
#include "button.h"
class Dinosaur : public QMainWindow
{
    Q_OBJECT

public:
    Dinosaur(QWidget *parent = nullptr);
    ~Dinosaur();
    void setposition(int x, int y);
    QPixmap Dinosaur1;
    QPixmap Dinosaur4;
    QPixmap Dinosaur2;
    QPixmap Dinosaur3;
    QPixmap Dinosaur_max1;
    QPixmap Dinosaur_max2;
    QPixmap Dinosaur_max3;
    QPixmap Dinosaur_max4;
    QPixmap Dinosaur_max5;
    QPixmap Dinosaur_max6;
    QPixmap Dinosaur_max7;
    QPixmap Dinosaur_max8;
    QPixmap lsz;
    QPixmap lsz22;
    bool lsz_flag = false;
    int lsz22_x=50, lsz22_y=670;
    void lszPosition();
    void jump();
    void sprint();
    void updatePositionY();
   /* QPixmap m_enermy;
    QPixmap m_enermy1;
    QPixmap m_enermy2;
    QPixmap m_enermy3;
    QPixmap m_enermy4;
    QPixmap m_enermy5;
    QPixmap m_enermy6;
    QRectF m_Collision;
    //位置(仙人掌)
    int m_x=0;
    int m_y=790;
   bool m_Free = true;
   double m_Speed = 3;

    QRect m_Rect;
    QRect m_Rect1;
    QRect m_Rect2;
    QRect m_Rect3;
    QRect m_Rect4;
    QRect m_Rect5;
    QRect m_Rect6;
    //状态(仙人掌)
    bool m_Free;
    //速度(仙人掌)
    int m_Speed;

    void enemy_updateposition();
    void enermyToScene();
    int m_enermys[12];//仙人掌数组
    int m_recorder;//仙人掌出现间隔*/
    

    void enermyToScene();
    Enermy m_enermys[ENERMY_NUM];//仙人掌数组
    int m_recorder;//仙人掌出现间隔
    void enemy_updatePosition();
    int m_speed = ENERMY_SPEED;
    //恐龙碰撞矩形
    QRect d_rect;
    int d_x;
    int d_y;
    bool dino_flag=true;
    int dino_change=0;
    //恐龙属性
    double y;//纵坐标
    double v ;
    double g ;
    double a;
    const int ground;
    bool is_jumping;
    bool is_releasing;
    bool is_flying;
    bool dis_flying;
    double last_v;
    double last_h = 0.0;
    //重新开始游戏
    void paintEvent(QPaintEvent* event);
    QPushButton* m_restartBtn;
    //绘制地图
    QPixmap m_map1;
    QPixmap m_map2;
    //地图坐标位置和速度
    int m_map1_posX;
    int m_map2_posX;
    int m_scroll_speed;
    //滚动地图
    void mapPosition();
    //Cloud
    void cloudToScene();
    Cloud c_clouds[CLOUD_NUM];//云数组
    int c_recorder;//云出现间隔
    void cloud_updatePosition();
    //bird
    void birdToScene();
    Bird b_birds[ENERMY_NUM];
    int b_recorder;
    void bird_updatePosition();
    //kunkun
    void kunkunToScene();
    kunkun k_kuns[ENERMY_NUM];
    int k_recorder;
    void kun_updatePosition();
    //heart
    void heartToScene();
    Heart h_hearts[ENERMY_NUM];
    int h_recorder;
    void heart_updateposition();
    //启动游戏
    void gamestart();
    void restartGame();
    int mark;
    int m_gameover = 1;
    //QTimer* time = new QTimer;
    QTimer m_timer;
    QTimer sprint_Timer;
    QTimer sprint_interval_Timer;
    QTimer protected_Timer;
    QTimer jump_Timer;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
   // void updateposition();
    bool collisiondDetection();
    bool checkbirdCollision();
    bool checkkunkunCollision();
    bool checkCollision();
    bool sprint_once;
    bool sprint_twice;
    bool jump_once;
    bool jump_twice;
    QGraphicsScene* scene;
private slots:
    void dinoo();
    void onTimer();
    void on_restart_clicked();

    void on_return_main_clicked();
private:
    Ui::DinosaurClass ui;
};
