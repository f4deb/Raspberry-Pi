#include <QWidget>
#include <QObject>
#include <QTimer>
#include "../../qcustomplot/qcustomplot.h"


#include "mpu.h"
#include "mainwindow.h"

MainWindow::mpuValue mpuaccess;
QCustomPlot *customPlotAccXValue;

class MainWindow;

Mpu::Mpu(QWidget *parent) {

}

void Mpu::mpuGraphicPrint(QCustomPlot *customPlot){
    // configure axis rect:
    customPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch


    // X Gravity
    wideAxisRect1 = new QCPAxisRect(customPlot);
    wideAxisRect1->setupFullAxesBox(true);
    wideAxisRect1->axis(QCPAxis::atTop,0)->setLabel(labelXG);
    wideAxisRect1->axis(QCPAxis::atTop,0)->setLabelColor(QColor(230,230,230,240));
    //wideAxisRect1->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect1->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect1->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect1->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect1->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect1->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect1->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect1->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect1->setBackground(QColor(230,230,230,240));
    wideAxisRect1->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect1->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    // Y GRAVITY
    wideAxisRect2 = new QCPAxisRect(customPlot);
    wideAxisRect2->setupFullAxesBox(true);
    wideAxisRect2->axis(QCPAxis::atTop,0)->setLabel(labelYG);
    wideAxisRect2->axis(QCPAxis::atTop,0)->setLabelColor(QColor(230,230,230,240));
    wideAxisRect2->setBackground(QColor(230,230,230,240));
    //wideAxisRect1->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect2->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect2->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect2->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect2->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect2->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect2->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect2->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect2->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect2->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    // Z GRAVITY
    wideAxisRect3 = new QCPAxisRect(customPlot);
    wideAxisRect3->setupFullAxesBox(true);
    wideAxisRect3->axis(QCPAxis::atTop,0)->setLabel(labelZG);
    wideAxisRect3->axis(QCPAxis::atTop,0)->setLabelColor(QColor(230,230,230,240));
    wideAxisRect3->setBackground(QColor(230,230,230,240));
    //wideAxisRect3->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect3->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect3->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect3->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect3->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect3->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect3->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect3->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect3->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect3->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    // X ACCELERATION
    wideAxisRect4 = new QCPAxisRect(customPlot);
    wideAxisRect4->setupFullAxesBox(true);
    wideAxisRect4->axis(QCPAxis::atTop,0)->setLabel(labelXA);
    wideAxisRect4->axis(QCPAxis::atTop,0)->setLabelColor(QColor(230,230,230,240));
    wideAxisRect4->setBackground(QColor(230,230,230,240));
    //wideAxisRect4->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect4->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect4->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect4->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect4->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect4->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect4->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect4->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect4->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect4->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    // Y ACCELERATION
    wideAxisRect5 = new QCPAxisRect(customPlot);
    wideAxisRect5->setupFullAxesBox(true);
    wideAxisRect5->axis(QCPAxis::atTop,0)->setLabel(labelYA);
    wideAxisRect5->axis(QCPAxis::atTop,0)->setLabelColor(QColor(230,230,230,240));
    wideAxisRect5->setBackground(QColor(230,230,230,240));
    //wideAxisRect5->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect5->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect5->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect5->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect5->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect5->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect5->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect5->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect5->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect5->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    // Z ACCELERATION
    wideAxisRect6 = new QCPAxisRect(customPlot);
    wideAxisRect6->setupFullAxesBox(true);
    wideAxisRect6->axis(QCPAxis::atTop,0)->setLabel(labelZA);
    wideAxisRect6->axis(QCPAxis::atTop,0)->setLabelColor(labelColor);
    wideAxisRect6->setBackground(QColor(230,230,230,240));
    //wideAxisRect6->axis(QCPAxis::atRight, 0)->setTickLabels(true);
    wideAxisRect6->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
    wideAxisRect6->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
    wideAxisRect6->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
    wideAxisRect6->axis(QCPAxis::atBottom,0)->setTickStep(2);
    wideAxisRect6->axis(QCPAxis::atTop,0)->setAutoTickStep(false);
    wideAxisRect6->axis(QCPAxis::atTop,0)->setTickStep(2);
    wideAxisRect6->axis(QCPAxis::atLeft,0)->setRange(-210,210);
    wideAxisRect6->axis(QCPAxis::atBottom, 0)->setTickLabelColor((QColor(230,230,230,240) ));
    wideAxisRect6->axis(QCPAxis::atLeft, 0)->setTickLabelColor((QColor(230,230,230,240) ));

    //QCPLayoutGrid *subLayout = new QCPLayoutGrid;
    customPlot->plotLayout()->addElement(0, 0, wideAxisRect1); // insert axis rect in first row
    customPlot->plotLayout()->addElement(0, 1, wideAxisRect2);
    customPlot->plotLayout()->addElement(0, 2, wideAxisRect3);
    customPlot->plotLayout()->addElement(1, 0, wideAxisRect4);
    customPlot->plotLayout()->addElement(1, 1, wideAxisRect5);
    customPlot->plotLayout()->addElement(1, 2, wideAxisRect6);

    marginGroup = new QCPMarginGroup(customPlot);

    wideAxisRect1->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    wideAxisRect2->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    wideAxisRect3->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    wideAxisRect4->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    wideAxisRect5->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    wideAxisRect6->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);

    // create and configure plottables:
    mainGraph1 = customPlot->addGraph(wideAxisRect1->axis(QCPAxis::atBottom), wideAxisRect1->axis(QCPAxis::atLeft));
    mainGraph1->setPen(QPen(penColor, penSize));// Axe zero

    mainGraph2 = customPlot->addGraph(wideAxisRect2->axis(QCPAxis::atBottom), wideAxisRect2->axis(QCPAxis::atLeft));
    mainGraph2->setPen(QPen(penColor, penSize));

    mainGraph3 = customPlot->addGraph(wideAxisRect3->axis(QCPAxis::atBottom), wideAxisRect3->axis(QCPAxis::atLeft));
    mainGraph3->setPen(QPen(penColor, penSize));

    mainGraph4 = customPlot->addGraph(wideAxisRect4->axis(QCPAxis::atBottom), wideAxisRect4->axis(QCPAxis::atLeft));
    mainGraph4->setPen(QPen(penColor, penSize));

    mainGraph5 = customPlot->addGraph(wideAxisRect5->axis(QCPAxis::atBottom), wideAxisRect5->axis(QCPAxis::atLeft));
    mainGraph5->setPen(QPen(penColor, penSize));

    mainGraph6 = customPlot->addGraph(wideAxisRect6->axis(QCPAxis::atBottom), wideAxisRect6->axis(QCPAxis::atLeft));
    mainGraph6->setPen(QPen(penColor, penSize));

    // rescale axes according to graph's data:
    mainGraph1->rescaleAxes(false);
    mainGraph2->rescaleAxes();
    mainGraph3->rescaleAxes();
    mainGraph4->rescaleAxes();
    mainGraph5->rescaleAxes();
    mainGraph6->rescaleAxes();

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1); // 1ms  Interval 0 means to refresh as fast as possible
}

void Mpu::realtimeDataSlot(){
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  static double lastPointKey = 0;

  if (key-lastPointKey > 0.01) // at most add point every 10 ms
  {
    double value1 = mpuaccess.AX/163.84;
    double value2 = mpuaccess.AY/163.84;
    double value3 = mpuaccess.AZ/163.84;
    double value4 = mpuaccess.AX/163.84;
    double value5 = mpuaccess.AY/163.84;
    double value6 = mpuaccess.AZ/163.84;

    // add data to lines:
    mainGraph1->addData(key, value1);
    mainGraph2->addData(key, value2);
    mainGraph3->addData(key, value3);
    mainGraph4->addData(key, value4);
    mainGraph5->addData(key, value5);
    mainGraph6->addData(key, value6);


    // remove data of lines that's outside visible range:
    mainGraph1->removeDataBefore(key-8);
    mainGraph2->removeDataBefore(key-8);
    mainGraph3->removeDataBefore(key-8);
    mainGraph4->removeDataBefore(key-8);
    mainGraph5->removeDataBefore(key-8);
    mainGraph6->removeDataBefore(key-8);

    // rescale value (vertical) axis to fit the current data:
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
    wideAxisRect1->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect2->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect3->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect4->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect5->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect6->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);

    customPlotAccXValue->replot();

}
