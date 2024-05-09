#include "button.h"

//��ť����:������Ϸ��ͣ�ͼ����İ�ť����Ҫ��д��갴���¼���

Button::Button(QTimer * t)
{
    //   sound = s;
    timer = t;
}

//���� ��ť ���ڵľ�������
QRectF Button::boundingRect() 
{
    return QRectF(1000, 150, 160, 40);
}

//���ư�ť�������Ƿ�����ť ���� ��pause�� ���� ��continue��
void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
        Q_UNUSED(widget)

        //��ťͼƬ
        painter->drawPixmap(QRect(1000, 150, 160, 40), QPixmap(":/Dinosaur/E:/1/Button.png"));
    painter->setPen(Qt::green);

    //�����ı���ʽ
    QFont font("Calibri", 18, QFont::Bold, true);
    painter->setFont(font);

    //�������ж�ʱ������Ϸ���ڽ��У���ʾ��pause����ť
    if (timer->isActive())
        painter->drawText(boundingRect(), Qt::AlignCenter, "PAUSE");
    //��Ϸֹͣ����ʾ��continue����ť
    else
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
}

//����������¼������Ķ�ʱ����ֹͣor�������Լ�����
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
    //update�������ڶ�ε����Ժ�ϵͳ���ں��ʵ�ʱ���ػ�һ�Σ�
    //��repaint����ϵͳ��������Ӧ�����ö��ٴ�repaint�ͻ��ػ���ٴΡ�
    //����ʹ��update����
    //https://blog.csdn.net/mojianc/article/details/51612851
   // update();
}
