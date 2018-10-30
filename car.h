#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QPainter>

class car : public QWidget
{
    Q_OBJECT
public:
    explicit car(QWidget *parent = 0);
    QLabel *label_Scale;
    QLabel *label;
    int m_pointX;
    int m_pointY;
    float m_degreespeed;
    float m_degreeRotate;

    void paintEvent(QPaintEvent *);
    void change_Speed(float temp);

signals:

public slots:
};

#endif // CAR_H
