#include "car.h"

car::car(QWidget *parent) : QWidget(parent)
{
    this->resize (400,255);
    label_Scale = new QLabel(this);
    label_Scale->setGeometry(QRect(0, 0, 400, 255));
    label_Scale->setStyleSheet ("border-image:url(:/new/prefix1/Km/Km_background.png)");
    label_Scale->show ();
    label = new QLabel(this);
    label->setGeometry(QRect(175, 180, 50, 50));
    label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/Km/pointhover.png);"));
    label->show ();
    m_pointX = 200;
    m_pointY = 200;
    m_degreespeed = 0;
    m_degreeRotate = 0;
}


void car::paintEvent (QPaintEvent *)
{
    QImage imagePointer(":/new/prefix1/Km/Point.png");
    QPainter painter(this);
    QRect rct(32,39,324,324);
    painter.translate(m_pointX,m_pointY);
    painter.rotate(-14+m_degreespeed);              //m_degreespeed是转动的角度，0就是指向速度表的开始
    painter.translate((0 - m_pointX),(0-m_pointY));
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
    painter.drawImage(rct,imagePointer);
    painter.save();
    painter.restore();
}

void car::change_Speed(float temp)
{
    m_degreespeed = temp;                   //m_degreespeed定时增加，所以指针会跟随着转动
    update();
}
