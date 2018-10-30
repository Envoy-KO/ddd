#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include"curve/cpiechart.h"
#include"curve/chistogram.h"
#include"curve/clinechart.h"
#include <list>
#include <QMutableListIterator>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class mychart : public QWidget
{
    Q_OBJECT
public:
    explicit mychart(QWidget *parent = 0);
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;

    Cpiechart *m_piechart;
    Chistogram *m_histogram;
    Clinechart *m_linechart;


};

#endif // MYCHART_H
