#include <QApplication>
#include <QtWidgets>

#include "mainwindow.h"

int main(int argc, char *argv[])

{
    QApplication app(argc, argv);
    MainWindow MainWindow;
    MainWindow.setGeometry(0,0,700,700);
    MainWindow.show();

    return app.exec();
}
