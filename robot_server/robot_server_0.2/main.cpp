#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setGeometry(0,0,400,200);
    w.show();


    return app.exec();
}
