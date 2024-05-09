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
    //��ʼ������
    void  initScene();

    void paintEvent(QPaintEvent* event) override;

    explicit NewScene(Dinosaur* mainscene, QWidget* parent = nullptr);
    ~NewScene();
    Dinosaur* mainscene;
    QPushButton* introduction;
    QPushButton*startgame;
    Introduction* intro = new Introduction;
public slots:
    void onSpaceKeyPressed();    //���ڽ�����ת
    void on_intro_clicked();

signals:
    void space_key_pressed(QKeyEvent* event); // ����һ���źţ��ṩһ��QKeyEvent�������ڰ��¿ո��ʱ����

private:
    void keyPressEvent(QKeyEvent* event) override; // ��д���̰����¼�������
};

#endif // NEWSCENE_H