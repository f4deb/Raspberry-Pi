#ifndef MPU_H
#define MPU_H
#include <QtWidgets>


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



class Mpus : public QWidget
{
    Q_OBJECT
public:
    explicit Mpus(QWidget *parent = 0);

    void toto();

};


#endif // MPU

