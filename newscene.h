#pragma once
#ifndef NEWSCENE_H
#define NEWSCENE_H
#include<QIcon>
#include<QPainter>
#include <QWidget>
#include<QTimer>
#include <QWidget>
#include"dinosaur.h"
#include <QKeyEvent>
#include"introduction.h"
#include"ui_introduction.h"
class Dinosaur;
class NewScene : public QWidget
{
    Q_OBJECT

public:
    //初始化场景
    void  initScene();

    void paintEvent(QPaintEvent* event) override;

    explicit NewScene(Dinosaur* mainscene, QWidget* parent = nullptr);
    ~NewScene();
    Dinosaur* mainscene;
    QPushButton* introduction;
    QPushButton*startgame;
    Introduction* intro = new Introduction;
public slots:
    void onSpaceKeyPressed();    //用于界面跳转
    void on_intro_clicked();

signals:
    void space_key_pressed(QKeyEvent* event); // 定义一个信号，提供一个QKeyEvent参数，在按下空格键时发出

private:
    void keyPressEvent(QKeyEvent* event) override; // 重写键盘按下事件处理函数
};

#endif // NEWSCENE_H