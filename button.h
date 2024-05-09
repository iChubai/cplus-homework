
#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include <QTimer>
//#include <QSound>
//#include "other.h"

//���Ͻǵİ�ť����ͣ or ������

class Button
{
public:
    Button(QTimer* t);
    QRectF boundingRect();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) ;
private:
    // QSound *sound;
    QTimer* timer;
};

#endif // BUTTON_H
