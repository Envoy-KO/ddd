#include "mainwindow.h"
#include "OpenGL/glwidget.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    windowinit ();
}

MainWindow::~MainWindow()
{

}

void MainWindow::windowinit ()
{
    setWindowTitle ("智能管理");
    creatActions();
    creatMenus ();
    glWidget= new myopenGl;
    setCentralWidget (glWidget);

    dock = new QDockWidget("速度表",this);
    dock->setFeatures (QDockWidget::AllDockWidgetFeatures);
    myDashboard = new Dashboard;
    dock->setWidget (myDashboard);
    addDockWidget (Qt::TopDockWidgetArea,dock);
    dock->hide ();

    dock1 = new QDockWidget("文本显示区",this);
    dock1->setFeatures (QDockWidget::AllDockWidgetFeatures);
    display = new QTextEdit();
    display->setFontPointSize (15);
    display->setFontFamily ("微软雅黑 Light");
    dock1->setWidget (display);
    display->setMinimumWidth (450);
    addDockWidget (Qt::BottomDockWidgetArea,dock1);
    dock1->hide ();

    dock2 = new QDockWidget("图表显示区",this);
    dock2->setFeatures (QDockWidget::AllDockWidgetFeatures);
    chartwidget = new mychart();
    dock2->setWidget (chartwidget);
    for (int j = 0; j < 10; ++j)
    {
        chartwidget->m_piechart->data[j]=0;
        chartwidget->m_histogram->data[j]=0;
    }
    chartwidget->m_piechart->paintpiechart ();//画图饼状图函数
    chartwidget->m_histogram->paintshapechart ();
    chartwidget->m_linechart->linedata.clear ();
    chartwidget->m_linechart->paintlinechart ();
    addDockWidget (Qt::BottomDockWidgetArea,dock2);
    dock2->hide ();

    dock3 = new QDockWidget("文本显示区",this);
    dock3->setFeatures (QDockWidget::AllDockWidgetFeatures);
    display2 = new QLabel();
    display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">你好</font></span></p></body></html>");
    dock3->setWidget (display2);
    addDockWidget (Qt::BottomDockWidgetArea,dock3);
    dock3->hide ();

    dock4 = new QDockWidget("数据汇总",this);
    dock4->setFeatures (QDockWidget::AllDockWidgetFeatures);
    themax = new Maxwidget;
    dock4->setWidget (themax);
    addDockWidget (Qt::TopDockWidgetArea,dock4);
    dock4->hide ();
}

void MainWindow::creatActions ()
{
    openDashBoard = new QAction("打开速度表",this);
    openDashBoard->setStatusTip ("打开速度表");
    connect(openDashBoard,SIGNAL(triggered()),this,SLOT(showDashBoard()));

    openTextEdit = new QAction("打开文本显示",this);
    openTextEdit->setStatusTip ("打开文本显示");
    connect(openTextEdit,SIGNAL(triggered()),this,SLOT(showTextEdit()));

    openchart = new QAction("打开统计图",this);
    openchart->setStatusTip ("打开统计图");
    connect(openchart,SIGNAL(triggered()),this,SLOT(showchart()));

    openlabel = new QAction("打开提示窗口",this);
    openlabel->setStatusTip ("打开提示窗口");
    connect(openlabel,SIGNAL(triggered()),this,SLOT(showlabel()));

    openmax = new QAction("打开汇总窗口",this);
    openmax->setStatusTip ("打开汇总窗口");
    connect(openmax,SIGNAL(triggered()),this,SLOT(showmax()));

    closeAction = new QAction("退出",this);
    connect(closeAction,SIGNAL(triggered()),this,SLOT(close()));

    startLink = new QAction("打开连接",this);
    connect(startLink,SIGNAL(triggered()),this,SLOT(TCPsocket_start()));

    getRecord = new QAction("获得使用记录",this);
    connect(getRecord,SIGNAL(triggered()),this,SLOT(TCPsocket_send0()));

    getchart = new QAction("更新所有统计数据",this);
    connect(getchart,SIGNAL(triggered()),this,SLOT(TCPsocket_send1()));

    getlinechart = new QAction("更新使用记录折线图",this);
    connect(getlinechart,SIGNAL(triggered()),this,SLOT(TCPsocket_send2()));

    getSumTime = new QAction("获得今日使用时长",this);
    connect(getSumTime,SIGNAL(triggered()),this,SLOT(TCPsocket_send3()));



}

void MainWindow::creatMenus ()
{
    fileMenu = menuBar ()->addMenu ("菜单(&E)");
    fileMenu->addAction(closeAction);
    windowMenu = menuBar ()->addMenu ("窗口(&W)");
    windowMenu->addAction(openDashBoard);
    windowMenu->addAction(openTextEdit);
    windowMenu->addAction(openchart);
    windowMenu->addAction(openlabel);
    windowMenu->addAction(openmax);
    socketMenu = menuBar ()->addMenu ("连接(&L)");
    socketMenu->addAction(startLink);
    socketMenu->addAction(getRecord);
    socketMenu->addAction(getSumTime);
    socketMenu->addAction(getchart);
    socketMenu->addAction(getlinechart);
    setStyleSheet("QMenuBar:item{background-color:#c0c0c0;}QMenuBar{background-color:#c0c0c0;}");

}

void MainWindow::TCPsocket_start ()//点击调用
{
    quint16 port2 = 9999;
    QString IPaddress2="120.24.251.22";
    theSocket->connectToHost (IPaddress2,port2,QIODevice::ReadWrite);
    connect (theSocket,SIGNAL(connected()),this,SLOT(TCPsocket_connected()));
    startTimer(200);
}

void MainWindow::TCPsocket_connected()
{
    qDebug()<<"进入状态";
    connect(theSocket,SIGNAL(readyRead()),this,SLOT(TCPsocket_read()));
}

void MainWindow::TCPsocket_read()
{
    int value,temp1,temp2,temp3;
    QByteArray      KreadByteArray = theSocket->readAll ();
    QString     KreadString ;
    KreadString = KreadByteArray.data ();
    bool ok;
    QList<QString> stringlist = KreadString.split (",");
    QListIterator<QString> strlist(stringlist);
    temp =  strlist.next ();
    if (temp=="x")
    {
        qDebug()<<"接收到数据";
        for (;strlist.hasNext ();)
        {
            value =  strlist.next ().toInt (&ok,10);
            baselist<<value;
        }
        QListIterator<int> i(baselist);
        switch (i.next ()) {
        case 0:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">跑动</font></span></p></body></html>");
            break;
        case 1:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">准备</font></span></p></body></html>");
            break;
        case 2:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">发球</font></span></p></body></html>");
            break;
        case 3:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">迎击</font></span></p></body></html>");
            break;
        case 4:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">正手挥拍</font></span></p></body></html>");
            break;
        case 5:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">反手挥拍</font></span></p></body></html>");
            break;
        case 6:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">正手挑球</font></span></p></body></html>");
            break;
        case 7:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">反手挑球</font></span></p></body></html>");
            break;
        case 8:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">正手扣杀</font></span></p></body></html>");
            break;
        case 9:
            display2->setText ("<html><head/><body><p align=\"center\"><span style=\" font-size:100pt;\"><font face=\"微软雅黑 Light\">反手扣杀</font></span></p></body></html>");
            break;
        default:
            break;
        }//这是状态
        glWidget->zrot=i.next ();
        glWidget->anglez=glWidget->zrot;
        glWidget->xrot=i.next ();
        glWidget->anglex=glWidget->xrot;
        glWidget->yrot=-i.next ();
        glWidget->angley=glWidget->yrot;
        temp1=i.next ();
        temp2=i.next ();
        if (temp1>max1)
            max1=temp1;
        if(-temp1>max1)
            max1=-temp1;
        if (temp2>max2)
            max2=temp2;
        if(-temp2>max2)
            max2=-temp2;
        themax->lcdNumber->display (max1);
        themax->lcdNumber_2->display (max2);
        myDashboard->change_Speed (temp2,temp1);
        baselist.clear ();
    }
    if (temp=="s")
    {
        qDebug()<<"收到时间";
        display->insertPlainText (strlist.next ());
    }
    if (temp=="o")
    {
        qDebug()<<"收到饼状图";
        for (;strlist.hasNext ();)
        {
            value =  strlist.next ().toInt (&ok,10);
            baselist<<value;
        }
        QListIterator<int> i(baselist);
        for (int j = 0; j < 10; ++j)
        {
            int thedata;
            thedata=i.next ();
            chartwidget->m_piechart->data[j]=(double)thedata;
            chartwidget->m_histogram->data[j]=(double)thedata;
        }
        chartwidget->m_piechart->paintpiechart ();//画图饼状图函数
        chartwidget->m_histogram->paintshapechart ();
        i.toFront ();
        temp3=i.next ();
        Calorie=temp3*0.005;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        step=temp3*2;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        step+=temp3*2;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        step+=temp3*2;
        temp3=i.next ();
        Calorie+=temp3*0.005;
        step+=temp3*2;
        temp3=i.next ();
        Calorie+=temp3*0.01;
        step+=temp3*2;
        temp3=i.next ();
        Calorie+=temp3*0.01;
        step+=temp3*2;
        themax->lcdNumber_3->display (Calorie);
        themax->lcdNumber_4->display (step);
        baselist.clear ();
    }
    if (temp=="z")
    {
        qDebug()<<"收到折线图";
        chartwidget->m_linechart->linedata.clear ();
        for (;strlist.hasNext ();)
        {
            value =  strlist.next ().toInt (&ok,10);
            chartwidget->m_linechart->linedata<<value;
        }
        chartwidget->m_linechart->linedata.removeLast ();
        chartwidget->m_linechart->linedata.removeLast ();
        chartwidget->m_linechart->paintlinechart ();
    }
}

void MainWindow::TCPsocket_sendData()
{
    QString socketsendString="q";
    QByteArray sendByte2="";
    sendByte2 = socketsendString.toLatin1 ();
    theSocket->write (sendByte2.toStdString ().c_str (),strlen(sendByte2.toStdString ().c_str ()));

}

void MainWindow::TCPsocket_send0()
{
    QString socketsendString="gettime";
    QByteArray sendByte2="";
    sendByte2 = socketsendString.toLatin1 ();
    theSocket->write (sendByte2.toStdString ().c_str (),strlen(sendByte2.toStdString ().c_str ()));
}

void MainWindow::TCPsocket_send1()
{
    QString socketsendString="geto";
    QByteArray sendByte2="";
    sendByte2 = socketsendString.toLatin1 ();
    theSocket->write (sendByte2.toStdString ().c_str (),strlen(sendByte2.toStdString ().c_str ()));
}

void MainWindow::TCPsocket_send2()
{
    QString socketsendString="getz";
    QByteArray sendByte2="";
    sendByte2 = socketsendString.toLatin1 ();
    theSocket->write (sendByte2.toStdString ().c_str (),strlen(sendByte2.toStdString ().c_str ()));
}

void MainWindow::TCPsocket_send3()
{
    QString socketsendString="getsumtime";
    QByteArray sendByte2="";
    sendByte2 = socketsendString.toLatin1 ();
    theSocket->write (sendByte2.toStdString ().c_str (),strlen(sendByte2.toStdString ().c_str ()));
}

void MainWindow::showDashBoard ()
{
    dock->show ();
}

void MainWindow::showTextEdit ()
{
    dock1->show ();
}

void MainWindow::showchart ()
{
    dock2->show ();
}

void MainWindow::showlabel ()
{
    dock3->show ();
}

void MainWindow::showmax ()
{
    dock4->show ();
}

void MainWindow::timerEvent (QTimerEvent *)
{
    TCPsocket_sendData();
}





