#include "mychart.h"

mychart::mychart(QWidget *parent) : QWidget(parent)
{
    verticalLayout = new QVBoxLayout(this);
    tabWidget = new QTabWidget(this);
    verticalLayout->addWidget(tabWidget);
    m_piechart=new Cpiechart;
    m_histogram=new Chistogram;
    m_linechart=new Clinechart;

    m_piechart->paintpiechart ();//画图饼状图函数
    m_histogram->paintshapechart ();
    m_linechart->paintlinechart ();

    tabWidget->clear();
    tabWidget->addTab(m_piechart,"饼图");
    tabWidget->addTab(m_histogram,"柱状图");
    tabWidget->addTab(m_linechart,"折线图");
}



