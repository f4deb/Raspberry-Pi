#ifndef MPU_H
#define MPU_H
#include <QtWidgets>
#include "../../qcustomplot/qcustomplot.h"

//#include "mainwindow.h"


#define penColor QColor(Qt::red)
#define penSize 1
#define labelColor QColor(230,230,230,240)
#define labelXG "X Gravity"
#define labelYG "Y Gravity"
#define labelZG "Z Gravity"
#define labelXA "X Acceleration"
#define labelYA "Y Acceleration"
#define labelZA "Z Acceleration"



class Mpu : public QWidget
{
    Q_OBJECT
public:
    explicit Mpu(QWidget *parent = 0);




    void mpuGraphicPrint(QCustomPlot *customPlot);
    QCPMarginGroup *marginGroup;
    QCPAxisRect *wideAxisRect;


    QCPAxisRect *wideAxisRect1;
    QCPAxisRect *wideAxisRect2;
    QCPAxisRect *wideAxisRect3;
    QCPAxisRect *wideAxisRect4;
    QCPAxisRect *wideAxisRect5;
    QCPAxisRect *wideAxisRect6;

    QCPGraph *mainGraph1;
    QCPGraph *mainGraph2;
    QCPGraph *mainGraph3;
    QCPGraph *mainGraph4;
    QCPGraph *mainGraph5;
    QCPGraph *mainGraph6;

    QTimer dataTimer;

private slots:
    void realtimeDataSlot();


};


#endif // MPU

