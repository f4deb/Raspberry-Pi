#include <QtWidgets>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "server.h"
//#include "settingsdialog.h"
#include "singleton.h"
#include "mainwindow.h"



MainWindow::MainWindow(){

    createActions();
    createMenus();
    createToolBars();
    createCentral();
    createStatus();

    initServer();

    setWindowTitle(tr("Titan Control Center"));
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
    zoneCentralCenter();

}

void MainWindow::createControls(const QString &title){

}

void MainWindow::createStatus(){

    statusLabel = new QLabel(this);
    statusLabel->setText("Status Label");
    statusBar()->addPermanentWidget(statusLabel);
    statusBar()->showMessage("Status");
    statusLabel->setText("totoLabel");
}

// *************** SERVER PORT ****************

void MainWindow::initServer(){
    Server *servv = new Server;
    servv->serverInitialisation();

    serveurPort->setMaximum(1024);
    serveurPort->setMaximum(65535);
    serveurPort->setValue(50885);

    serveurIP->setText("127.0.0.1");
    QObject::connect(serveurConnect, SIGNAL(clicked()), this, SLOT(status_en_cours()));
    QObject::connect(serveurConnect, SIGNAL(clicked()), servv, SLOT(on_boutonConnexion_clicked()));
    QObject::connect(servv,SIGNAL(on_connect(char *,bool)),this,SLOT(status_connecte(char *,bool)));
    QObject::connect(servv,SIGNAL(on_error_connect()),this,SLOT(status_erreur_connection()));
}

void MainWindow::status_en_cours(){
    statusBar()->showMessage(tr("Tentative de connexion en cours..."));
    getServeurPort();
}

void MainWindow::status_connecte(char *toto, bool etat_connection){
    statusBar()->showMessage(tr(toto));
    if (etat_connection){
        serveurConnect->setText("Connected");
        }
    else{
        serveurConnect->setText("Disconnected");
    }
}

void MainWindow::status_erreur_connection(){
    statusBar()->showMessage(tr("Erreur Serveur!!!"));
}

int MainWindow::getServeurPort(){
    Server::instances()->SetValue(serveurPort->value());
    return serveurPort->value();
}

QString MainWindow::getServeurIp(){
    return serveurIP->text();
}

//************************ SERIEAL PORT ****************



