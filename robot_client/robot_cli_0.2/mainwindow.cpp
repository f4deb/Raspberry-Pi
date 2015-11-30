#include <QtWidgets>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "mainwindow.h"


MainWindow::MainWindow(){
    createActions();
    createMenus();
    createToolBars();
    createCentral();
    createStatus();
}

void MainWindow::createActions(){
    //menuConfiguration
    actionReseau = new QAction("&Réseau", this);
    actionPortSerie = new QAction("&Port Série", this);
    actionQuitter = new QAction("&Quitter", this);
    actionQuitter->setShortcuts(QKeySequence::Quit);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    //menuAide
    actionAPropos = new QAction("A propos", this);
    connect(actionAPropos,SIGNAL(triggered()), this, SLOT(aPropos()));
}

void MainWindow::createMenus(){
    menuConfiguration = menuBar()->addMenu("&Configuration");
    menuConfiguration->addAction(actionReseau);
    menuConfiguration->addAction(actionPortSerie);
    fichiersRecents = menuConfiguration->addMenu("Fichiers &récents");
        fichiersRecents->addAction("Fichier bidon 1.txt");
        fichiersRecents->addAction("Fichier bidon 2.txt");
        fichiersRecents->addAction("Fichier bidon 3.txt");
    menuConfiguration->addAction(actionQuitter);

    menuBar()->addSeparator();

    menuAide = menuBar()->addMenu("&Aide");
    menuAide->addAction(actionAPropos);
}

void MainWindow::createToolBars(){

}

void MainWindow::createCentral(){
    onglets();

}

void MainWindow::createControls(const QString &title){

}

void MainWindow::createStatus(){
    statusBar()->showMessage(tr("Ready"));
}
