#include <QtWidgets>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QLineEdit>

//#include "server.h"
//#include "settingsdialog.h"
#include "singleton.h"
#include "mainwindow.h"

extern int etat_serial_port;
extern int etat_serveur_port;

extern QByteArray message_from_server;

MainWindow::MainWindow(){

    createActions();
    createMenus();
    createToolBars();
    createCentral();
    createStatus();

    initServer();
    initSerialPort();
    initTerminalConnections();

    serial = new QSerialPort;
    //Terminal::instances()->setEtatConnexionSerial (0);
    etat_serial_port = 0;
    etat_serveur_port=0;

    setWindowTitle(tr("Titan Control Center V 0.2.3"));
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
    servv = new Server;
    servv->serverInitialisation();

    serveurPort->setMaximum(1024);
    serveurPort->setMaximum(65535);
    serveurPort->setValue(50885);

    serveurIP->setText("127.0.0.1");
    QObject::connect(serveurConnect, SIGNAL(clicked()), this, SLOT(status_en_cours()));
    QObject::connect(serveurConnect, SIGNAL(clicked()), servv, SLOT(on_boutonConnexion_clicked()));
    QObject::connect(servv,SIGNAL(on_connect(char *)),this,SLOT(status_connecte(char *)));
    QObject::connect(servv,SIGNAL(on_error_connect()),this,SLOT(status_erreur_connection()));
}

void MainWindow::status_en_cours(){
    statusBar()->showMessage(tr("Tentative de connexion en cours..."));
    getServeurPort();
}

void MainWindow::status_connecte(char *toto){
    statusBar()->showMessage(tr(toto));
    if (etat_serveur_port){
        serveurConnect->setText("Connected");
        serialGroupBox->setTitle("Port série distant");
        QObject::connect(servv, SIGNAL(readyRead()), servv, SLOT(donneesRecues()));
        QObject::connect(servv, SIGNAL(dataServerReceived()), this, SLOT(readData()));
        }
    else{
        serveurConnect->setText("Disconnected");
        serialGroupBox->setTitle("Port série local");
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

void MainWindow::initSerialPort(){
    Terminal *serial1 = new Terminal;
    serial1->terminalInitialisation();

    QObject::connect(SerialConnectButton, SIGNAL(clicked()), serial1, SLOT(on_bouton_serial_connexion_clicked()));
    QObject::connect(serial1,SIGNAL(openSerialPortTerminal()),this,SLOT(openSerialPort()));
    QObject::connect(serial1,SIGNAL(closeSerialPortTerminal()),this,SLOT(closeSerialPort()));
}

void MainWindow::openSerialPort(){
    if (serial->isOpen()){
        serial->close();
    }

    serial->setPortName(serialPortInfoListBox->currentText());
    serial->setBaudRate(static_cast<QSerialPort::BaudRate>(baudRateBox->itemData(baudRateBox->currentIndex()).toInt()));
    serial->setDataBits(static_cast<QSerialPort::DataBits>(dataBitsBox->itemData(dataBitsBox->currentIndex()).toInt()));
    serial->setParity(static_cast<QSerialPort::Parity>(parityBox->itemData(parityBox->currentIndex()).toInt()));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(stopBitsBox->itemData(stopBitsBox->currentIndex()).toInt()));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(flowControlBox->itemData(flowControlBox->currentIndex()).toInt()));
    if (serial->open(QIODevice::ReadWrite)) {
        SerialConnectButton->setText("Connected");
        statusBar()->showMessage(tr("Serial Port Connected"));
        QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        etat_serial_port = 1;
    } else {
        SerialConnectButton->setText("Disconnected");
        QObject::disconnect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        statusBar()->showMessage(tr("Serial Port Error"));
        etat_serial_port = -1;
    }
}

void MainWindow::closeSerialPort(){
    if (serial->isOpen())
        serial->close();
    if (!serial->isOpen())
        SerialConnectButton->setText("Disconnected");
        statusBar()->showMessage(tr("Serial Port Disconnected"));
        etat_serial_port = 0;
}

// ************************* Terminal ********************

void MainWindow::initTerminalConnections(){
    //QObject::connect(button_terminal_text1, SIGNAL(clicked()), Terminal, SLOT(clear()));
    QObject::connect(button_terminal_text1,SIGNAL(clicked()),this,SLOT(buttonTerminalText1()));
    QObject::connect(button_terminal_text2,SIGNAL(clicked()),this,SLOT(buttonTerminalText2()));
    QObject::connect(button_terminal_text3,SIGNAL(clicked()),this,SLOT(buttonTerminalText3()));
    QObject::connect(button_terminal_text4,SIGNAL(clicked()),this,SLOT(buttonTerminalText4()));
    QObject::connect(button_terminal_text5,SIGNAL(clicked()),this,SLOT(buttonTerminalText5()));
    QObject::connect(button_terminal_text6,SIGNAL(clicked()),this,SLOT(buttonTerminalText6()));
    QObject::connect(button_terminal_text7,SIGNAL(clicked()),this,SLOT(buttonTerminalText7()));

    QObject::connect(button_terminal_1,SIGNAL(clicked()),this,SLOT(buttonTerminal1()));
    QObject::connect(button_terminal_2,SIGNAL(clicked()),this,SLOT(buttonTerminal2()));
    QObject::connect(button_terminal_3,SIGNAL(clicked()),this,SLOT(buttonTerminal3()));
    QObject::connect(button_terminal_4,SIGNAL(clicked()),this,SLOT(buttonTerminal4()));

}

void MainWindow::buttonTerminalText1 (){
    writeData (terminalText1->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText2 (){
    writeData (terminalText2->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText3 (){
    writeData (terminalText3->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText4 (){
    writeData (terminalText4->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText5 (){
    writeData (terminalText5->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText6 (){
    writeData (terminalText6->text().toStdString().c_str());
}

void MainWindow::buttonTerminalText7 (){
    writeData (terminalText7->text().toStdString().c_str());
}


void MainWindow::buttonTerminal1 (){
    writeData (messageButtonTerminal1);
}

void MainWindow::buttonTerminal2 (){
    writeData (messageButtonTerminal2);
}

void MainWindow::buttonTerminal3 (){
    writeData (messageButtonTerminal3);
}

void MainWindow::buttonTerminal4 (){
    writeData (messageButtonTerminal4);
}


// *************************** Transfert data **********


void MainWindow::writeData(const QByteArray &data){
    if (etat_serial_port){
        serial->write(data);
        terminal->putData(data,0);
    }
    if (etat_serveur_port){
        servv->write(data);
        terminal->putData(data,0);
    }
}

void MainWindow::readData()
{
    if (etat_serial_port){
        QByteArray data = serial->readAll();
        terminal->putData(data,1);
    }
    if (etat_serveur_port){
        QByteArray data = message_from_server;
        terminal->putData(data,1);
    }
}
