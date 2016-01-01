#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMessageBox>
#include <QtWidgets>
#include <QWidget>

#include "apropos.h"
#include "central.h"
#include "server.h"
#include "terminal.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();

    QLineEdit *serveurIP;
    QSpinBox *serveurPort;

    int getServeurPort();
    QString getServeurIp();



    public slots:
    void aPropos();

    private:
    void createActions();
    void createMenus();
    void createCentral();
    void createStatus();
    void createToolBars();
    void createControls(const QString &title);

    void zoneCentralCenter();

    void initServer();

    QPushButton *serveurConnect;
    //Server *servv;

    QWidget *zoneCentrale;
    QMenu *menuConfiguration;
    QAction *actionReseau;
    QAction *actionPortSerie;
    QMenu *fichiersRecents;
    QAction *actionQuitter;

    QMenu *menuAide;
    QAction *actionAPropos;

    Terminal *terminal;
};

#endif // MAINWINDOW_H
