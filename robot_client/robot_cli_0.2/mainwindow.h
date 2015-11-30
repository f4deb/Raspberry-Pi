#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMessageBox>
#include <QtWidgets>
#include <QWidget>

#include "apropos.h"
#include "central.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();

    public slots:
    void aPropos();

    private:
    void createActions();
    void createMenus();
    void createCentral();
    void createStatus();
    void createToolBars();
    void createControls(const QString &title);

    void onglets();


    QWidget *zoneCentrale;
    QMenu *menuConfiguration;
    QAction *actionReseau;
    QAction *actionPortSerie;
    QMenu *fichiersRecents;
    QAction *actionQuitter;

    QMenu *menuAide;
    QAction *actionAPropos;



};

#endif // MAINWINDOW_H
