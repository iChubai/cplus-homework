#include <QPushButton>
#include <QDebug>
#include "dinosaur.h"
#include <QIcon>
#include <QPainter>
#include <QKeyEvent>
#include "enemy.h"
#include "dinosaur.h"
#include "newscene.h"
#include "config.h"
#include "introduction.h"
#include "ui_introduction.h"
#include <QFontDatabase>
#include <QString>
#include <ctime>
void NewScene::initScene() {
    setFixedSize(1500, 900);
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon(GAME_Icon));
}
NewScene::NewScene(Dinosaur* mainscene, QWidget* parent) :QWidget(parent)
{
    initScene();  
    this->mainscene = mainscene;
    startgame = new QPushButton(this);
    startgame->setFixedSize(250, 70);
    startgame->move(620, 320);
    startgame->setText("START");
    connect(startgame, &QPushButton::clicked, this, &NewScene::onSpaceKeyPressed);
    introduction = new QPushButton(this);
    introduction->setFixedSize(250, 70);
    introduction->move(620, 400);
    introduction->setText("Game Description");
    connect(introduction, &QPushButton::clicked, this, &NewScene::on_intro_clicked);
}
NewScene::~NewScene() {}
void NewScene::keyPressEvent(QKeyEvent* event)
{

    qDebug() << "Signal connection:" << connect(this, &NewScene::space_key_pressed, this, &NewScene::onSpaceKeyPressed);
    if (event->key() == Qt::Key_Space)
    {
        emit space_key_pressed(event);
    }
    else
    {
        QWidget::keyPressEvent(event);

    }
}
void NewScene::onSpaceKeyPressed()
{

    hide(); // 隐藏当前窗口

    mainscene->show(); // 显示MainScene
}
void NewScene::on_intro_clicked()           //游戏介绍按键
{
    intro = new Introduction;
    intro->setWindowFlags(Qt::WindowStaysOnTopHint);
    intro->show();
}




void NewScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawPixmap(0, 660,150,150, QPixmap(":/Dinosaur/E:/1/up.png"));
    painter.drawPixmap(0, 800, QPixmap(MAP_PATH));
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, "Press space to start");
    
}

