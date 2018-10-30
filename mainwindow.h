#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QTextEdit>
#include <QGridLayout>
#include "OpenGL/glwidget.h"
#include "Dashboard/dashboard.h"
#include "chart/mychart.h"
#include <list>
#include <QMutableListIterator>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QComboBox>
#include <QTcpSocket>
#include <Max/maxwidget.h>
#include <QtMath>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void windowinit();
    void timerEvent (QTimerEvent *);

    void creatActions();
    void creatMenus();
    void creatToolBars();

    Maxwidget *themax;
    Dashboard *myDashboard;
    QTextEdit *display;
    QLabel *display2;
    mychart *chartwidget;
    QDockWidget *dock,*dock1,*dock2,*dock3,*dock4;
    QHBoxLayout *alllayout;
    QTcpSocket *theSocket = new QTcpSocket();

    QString temp;
    QList<int> baselist;

    int max1 = 0,max2 = 0,step = 0;
    double Calorie = 0;

public slots:
    void    TCPsocket_start();
    void    TCPsocket_connected();
    void    TCPsocket_read();
    void    TCPsocket_sendData();
    void    TCPsocket_send0();
    void    TCPsocket_send1();
    void    TCPsocket_send2();
    void    TCPsocket_send3();

    void    showTextEdit();
    void    showchart();
    void    showDashBoard();
    void    showlabel();
    void    showmax();

private:
    myopenGl *glWidget;
    myopenGl *currentGlWidget;

    QMenu *fileMenu;
    QMenu *windowMenu;
    QMenu *socketMenu;

    QAction *closeAction;

    QAction *openDashBoard;
    QAction *openchart;
    QAction *openTextEdit;
    QAction *openlabel;
    QAction *openmax;

    QAction *startLink;
    QAction *getRecord;
    QAction *getSumTime;
    QAction *getchart;
    QAction *getlinechart;
};

#endif // MAINWINDOW_H
