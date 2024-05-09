#include "button.h"

//按钮操作:控制游戏暂停和继续的按钮，需要重写鼠标按下事件。

Button::Button(QTimer * t)
{
    //   sound = s;
    timer = t;
}

//返回 按钮 所在的矩形区域
QRectF Button::boundingRect() 
{
    return QRectF(1000, 150, 160, 40);
}

//绘制按钮，根据是否点击按钮 绘制 “pause” 或者 “continue”
void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)

        //按钮图片
        painter->drawPixmap(QRect(1000, 150, 160, 40), QPixmap(":/Dinosaur/E:/1/Button.png"));
    painter->setPen(Qt::green);

    //设置文本格式
    QFont font("Calibri", 18, QFont::Bold, true);
    painter->setFont(font);

    //正在运行定时器，游戏正在进行，显示“pause”按钮
    if (timer->isActive())
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE");
    //游戏停止，显示“continue”按钮
    else
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
}

//鼠标左键点击事件：更改定时器（停止or启动）以及音乐
void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive())
        {
            //sound->stop();
            timer->stop();
        }
        else
        {
            //sound->play();
            timer->start();
        }
    }
    //update（）会在多次调用以后，系统会在合适的时机重绘一次，
    //而repaint（）系统会立即响应，调用多少次repaint就会重绘多少次。
    //所以使用update更好
    //https://blog.csdn.net/mojianc/article/details/51612851
   // update();
}
