#include <QtWidgets>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QLineEdit>
#include <QCoreApplication>
#include <QtConcurrent/qtconcurrentrun.h>
#include <QThread>

#include "../../Qt-custom-gauge-widget-master/source/qcgaugewidget.h"
#include "../../qcustomplot/qcustomplot.h"

#include "singleton.h"
#include "mainwindow.h"

extern int etat_serial_port;
extern int etat_serveur_port;

extern QString adresseServeurIp;

extern QByteArray message_from_server;

extern QString serialCommandSend;
extern QString serialCommandReceived;

bool mpuGo;

MainWindow::MainWindow(){

    mpuaccess.time_mpu = 0;

    createActions();
    createMenus();
    createToolBars();
    createCentral();
    createStatus();

    initServer();
    initSerialPort();
    initTerminalConnections();
    initMPU();

    serial = new QSerialPort;
    //Terminal::instances()->setEtatConnexionSerial (0);
    etat_serial_port = 0;
    etat_serveur_port=0;

    setWindowTitle(tr("Titan Control Center V 0.4.1"));


    //setupRealtimeDataDemo(customPlotAccYValue);
    setupAdvancedAxesDemo(customPlotAccXValue);
    //setupRealtimeDataDemo(customPlotAccZValue);




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

    serveurIP->setText("192.168.10.1");
    QObject::connect(serveurConnect, SIGNAL(clicked()), this, SLOT(status_en_cours()));
    QObject::connect(serveurConnect, SIGNAL(clicked()), servv, SLOT(on_boutonConnexion_clicked()));
    QObject::connect(servv,SIGNAL(on_connect(char *)),this,SLOT(status_connecte(char *)));
    QObject::connect(servv,SIGNAL(on_error_connect()),this,SLOT(status_erreur_connection()));
}

void MainWindow::status_en_cours(){
    statusBar()->showMessage(tr("Tentative de connexion en cours..."));
    getServeurPort();
    getServeurIpM();
}

void MainWindow::status_connecte(char *toto){
    statusBar()->showMessage(tr(toto));
    if (etat_serveur_port){
        serveurConnect->setText("Connected");
        serialGroupBox->setTitle("Port série distant");
        QObject::connect(servv, SIGNAL(dataReadyRead()), servv, SLOT(donneesRecues()));
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
    Server::instances()->SetPortValue(serveurPort->value());
    return serveurPort->value();
}

QString MainWindow::getServeurIpM(){
    adresseServeurIp= serveurIP->text();
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

void MainWindow::readData(){
    if (etat_serial_port){
        QByteArray data = serial->readAll();
        terminal->putData(data,1);
    }
    if (etat_serveur_port){
        QByteArray data = message_from_server;
        terminal->putData(data,1);
    }
}

// ***************************** MOTION PROCESSOR UNIT ***************************

void MainWindow::mpuCalculate(){
    while (mpuGo){
        writeData ("JA");
        SleeperThread::msleep(20);


        // calcul de la temperature
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-3,3);
        QString temp = serialCommandReceived.right(4);
        bool ok;
        mpuaccess.temp = temp.toInt(&ok, 16);
        // enregistre la valeur
        mTempGauge->setText(QString::number(mpuaccess.temp));

        // calcul gyro Z
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString GZ = serialCommandReceived.right(4);
        mpuaccess.GZ=GZ.toInt(&ok, 16);
        sliderGyroZ->setValue(mpuaccess.GZ);

        // calcul gyro Y
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString GY = serialCommandReceived.right(4);
        mpuaccess.GY=GY.toInt(&ok, 16);
        sliderGyroY->setValue(mpuaccess.GY);

        // calcul gyro X
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString GX = serialCommandReceived.right(4);
        mpuaccess.GX=GX.toInt(&ok, 16);
        sliderGyroX->setValue(mpuaccess.GX);

        // calcul gravité Z
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString AZ = serialCommandReceived.right(4);
        mpuaccess.AZ=AZ.toInt(&ok, 16);
        sliderAccZ->setValue(mpuaccess.AZ);

        textAccZValue->setText(QString::number(mpuaccess.AZ));


        // calcul gravité Y
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString AY = serialCommandReceived.right(4);
        mpuaccess.AY=AY.toInt(&ok, 16);
        sliderAccY->setValue(mpuaccess.AY);

        textAccYValue->setText(QString::number(mpuaccess.AY));


        // calcul gravité X
        serialCommandReceived = serialCommandReceived.remove(serialCommandReceived.length()-5,5);
        QString AX = serialCommandReceived.right(4);
        mpuaccess.AX=AX.toInt(&ok, 16);

        sliderAccX->setValue(mpuaccess.AX);

        textAccXValue->setText(QString::number(mpuaccess.AX));




        mpuaccess.compassValue = 10;

        mpuaccess.rollValue = 10;
        mpuaccess.pitchValue = 10;

        mpuaccess.speedValue = 1;


        if (mpuaccess.compassValue < 270) {
            mpuaccess.compassValue = mpuaccess.compassValue + 90;
        }
        else {
            mpuaccess.compassValue = mpuaccess.compassValue - 270;
        }
        SleeperThread::msleep(10);

        mCompassNeedle->setCurrentValue(mpuaccess.compassValue);
        mAttMeter->setCurrentRoll(mpuaccess.rollValue);
        mAttMeter->setCurrentPitch(mpuaccess.pitchValue);


        mSpeedNeedle->setCurrentValue(0.55);
        mpuaccess.time_mpu++;


        QThread::msleep(100);
    }
}


void MainWindow::buttonStartMPU(){
    QFuture<void> t1 = QtConcurrent::run(this,&MainWindow::mpuCalculate);
    mpuGo = true;
}

void MainWindow::buttonStopMPU(){
    mpuGo = false;
}

void MainWindow::initMPU(){
    QObject::connect(startMPUButton ,SIGNAL(clicked()),this,SLOT(buttonStartMPU()));
    QObject::connect(stopMPUButton ,SIGNAL(clicked()),this,SLOT(buttonStopMPU()));

    mpuGo = true;
}

void MainWindow::setupAdvancedAxesDemo(QCustomPlot *customPlot){
  // configure axis rect:
  customPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch

  // X Gravity
  wideAxisRect1 = new QCPAxisRect(customPlot);
  wideAxisRect1->setupFullAxesBox(true);
  //wideAxisRect1->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect1->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect1->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect1->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect1->axis(QCPAxis::atBottom,0)->setTickStep(2);

  // Y GRAVITY
  wideAxisRect2 = new QCPAxisRect(customPlot);
  wideAxisRect2->setupFullAxesBox(true);
  //wideAxisRect1->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect2->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect2->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect2->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect2->axis(QCPAxis::atBottom,0)->setTickStep(2);

  // Z GRAVITY
  wideAxisRect3 = new QCPAxisRect(customPlot);
  wideAxisRect3->setupFullAxesBox(true);
  //wideAxisRect3->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect3->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect3->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect3->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect3->axis(QCPAxis::atBottom,0)->setTickStep(2);

  // X ACCELERATION
  wideAxisRect4 = new QCPAxisRect(customPlot);
  wideAxisRect4->setupFullAxesBox(true);
  //wideAxisRect4->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect4->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect4->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect4->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect4->axis(QCPAxis::atBottom,0)->setTickStep(2);

  // Y ACCELERATION
  wideAxisRect5 = new QCPAxisRect(customPlot);
  wideAxisRect5->setupFullAxesBox(true);
  //wideAxisRect5->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect5->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect5->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect5->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect5->axis(QCPAxis::atBottom,0)->setTickStep(2);

  // Z ACCELERATION
  wideAxisRect6 = new QCPAxisRect(customPlot);
  wideAxisRect6->setupFullAxesBox(true);
  //wideAxisRect6->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect6->axis(QCPAxis::atBottom,0)->setTickLabelType(QCPAxis::ltDateTime);
  wideAxisRect6->axis(QCPAxis::atBottom,0)->setDateTimeFormat("hh:mm:ss");
  wideAxisRect6->axis(QCPAxis::atBottom,0)->setAutoTickStep(false);
  wideAxisRect6->axis(QCPAxis::atBottom,0)->setTickStep(2);

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
  mainGraph1->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph1->setBrush(QColor(110, 170, 110, 30));

  mainGraph2 = customPlot->addGraph(wideAxisRect2->axis(QCPAxis::atBottom), wideAxisRect2->axis(QCPAxis::atLeft));
  mainGraph2->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph2->setBrush(QColor(110, 170, 110, 30));

  mainGraph3 = customPlot->addGraph(wideAxisRect3->axis(QCPAxis::atBottom), wideAxisRect3->axis(QCPAxis::atLeft));
  mainGraph3->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph3->setBrush(QColor(110, 170, 110, 30));

  mainGraph4 = customPlot->addGraph(wideAxisRect4->axis(QCPAxis::atBottom), wideAxisRect4->axis(QCPAxis::atLeft));
  mainGraph4->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph4->setBrush(QColor(110, 170, 110, 30));

  mainGraph5 = customPlot->addGraph(wideAxisRect5->axis(QCPAxis::atBottom), wideAxisRect5->axis(QCPAxis::atLeft));
  mainGraph5->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph5->setBrush(QColor(110, 170, 110, 30));

  mainGraph6 = customPlot->addGraph(wideAxisRect6->axis(QCPAxis::atBottom), wideAxisRect6->axis(QCPAxis::atLeft));
  mainGraph6->setPen(QPen(QColor("#8070B8"), 2));
  mainGraph6->setBrush(QColor(110, 170, 110, 30));

  // rescale axes according to graph's data:
  mainGraph1->rescaleAxes();
  mainGraph2->rescaleAxes();
  mainGraph3->rescaleAxes();
  mainGraph4->rescaleAxes();
  mainGraph5->rescaleAxes();
  mainGraph6->rescaleAxes();

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot(){
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
    mainGraph1->rescaleValueAxis();
    mainGraph2->rescaleValueAxis();
    mainGraph3->rescaleValueAxis();
    mainGraph4->rescaleValueAxis();
    mainGraph5->rescaleValueAxis();
    mainGraph6->rescaleValueAxis();
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
    wideAxisRect1->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect2->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect3->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect4->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect5->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);
    wideAxisRect6->axis(QCPAxis::atBottom, 0)->setRange(key+0.25, 4, Qt::AlignRight);

    mainGraph1->rescaleKeyAxis(true);
    mainGraph2->rescaleKeyAxis(true);
    mainGraph3->rescaleKeyAxis(true);
    mainGraph4->rescaleKeyAxis(true);
    mainGraph5->rescaleKeyAxis(true);
    mainGraph6->rescaleKeyAxis(true);

    customPlotAccXValue->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    statusBar()->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(mainGraph2->data()->count()+mainGraph3->data()->count())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}
