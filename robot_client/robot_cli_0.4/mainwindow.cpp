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
//#include "mpu.h"
#include "mainwindow.h"


extern int etat_serial_port;
extern int etat_serveur_port;

extern MainWindow::mpuValue mpuaccess;
extern QCustomPlot *customPlotAccXValue;


extern QString adresseServeurIp;

extern QByteArray message_from_server;

extern QString serialCommandSend;
extern QString serialCommandReceived;

bool mpuGo;

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

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

    //ssetupAdvancedAxesDemo(customPlotAccXValue);
    mpu = new Mpu;
    mpu->mpuGraphicPrint(customPlotAccXValue);





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
        SleeperThread::msleep(30);


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
        //SleeperThread::msleep(10);

        mCompassNeedle->setCurrentValue(mpuaccess.compassValue);
        mAttMeter->setCurrentRoll(mpuaccess.rollValue);
        mAttMeter->setCurrentPitch(mpuaccess.pitchValue);


        mSpeedNeedle->setCurrentValue(0.55);
        mpuaccess.time_mpu++;


        QThread::msleep(50);
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



// /////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////

void MainWindow::zoneCentralCenter(void){

// -----------------Zone Central Widget ----------------//
QWidget *zoneCentrale = new QWidget;

    // ------------ Left Widget -------------------//
    QWidget *leftZoneWidget = new QWidget();

        QGroupBox *verticalGroupBox= new QGroupBox(tr("Commandes Terminal"));
        QVBoxLayout *layout = new QVBoxLayout;

        buttons_SN = new QPushButton(tr("SN"));
        buttons_mw0000 = new QPushButton(tr("mw0000"));
        buttons_mw2020 = new QPushButton(tr("mw2020"));
        buttons_mw4040 = new QPushButton(tr("mw4040"));
        buttons_mw6060 = new QPushButton(tr("mw6060"));

            layout->addWidget(buttons_SN);
            layout->addWidget(buttons_mw0000);
            layout->addWidget(buttons_mw2020);
            layout->addWidget(buttons_mw4040);
            layout->addWidget(buttons_mw6060);

        verticalGroupBox->setLayout(layout);

        // -----------

        serveurGroupBox= new QGroupBox(tr("Serveur"));
            serveurIP = new QLineEdit;
            serveurPort = new QSpinBox;
            serveurConnect = new QPushButton("Connect");

            QFormLayout *layoutLeft1 = new QFormLayout;

            layoutLeft1->addRow("IP", serveurIP);
            layoutLeft1->addRow("Port", serveurPort);
            layoutLeft1->addWidget(serveurConnect);

        serveurGroupBox->setLayout(layoutLeft1);
        serveurGroupBox->setMaximumHeight(120);

        //------------
        serialGroupBox= new QGroupBox(tr("Port Serie"));
            serialPortInfoListBox = new QComboBox;
            baudRateBox = new QComboBox;
            dataBitsBox = new QComboBox;
            parityBox = new QComboBox;
            stopBitsBox = new QComboBox;
            flowControlBox = new QComboBox;

            QFormLayout *layoutLeft2 = new QFormLayout;
            layoutLeft2->addRow("Serial Port",serialPortInfoListBox);
            layoutLeft2->addRow("BaudRate",baudRateBox);
            layoutLeft2->addRow("Data bits",dataBitsBox);
            layoutLeft2->addRow("Parity",parityBox);
            layoutLeft2->addRow("Stop bits",stopBitsBox);
            layoutLeft2->addRow("Flow control",flowControlBox);

            SerialConnectButton = new QPushButton(tr("Connect"));
            layoutLeft2->addWidget(SerialConnectButton);

        serialGroupBox->setLayout(layoutLeft2);
        fillPortsParameters();
        fillPortsInfo();

    //-------------
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(serveurGroupBox);
    vbox->addWidget(serialGroupBox);
    vbox->addWidget(verticalGroupBox);

    leftZoneWidget->setLayout(vbox);
    leftZoneWidget->setMaximumWidth(240);


    // --------------Onglets Widget ------------------//
    QTabWidget *onglets = new QTabWidget(this);

        // Créer les pages, en utilisant un widget parent pour contenir chacune des pages
        QWidget *layoutTitanCenter = new QWidget;
        QWidget *layoutTerminal = new QWidget;
        QWidget *layoutMPU = new QWidget;
        QLabel *layoutElectronicalMainBoard = new QLabel; // Comme un QLabel est aussi un QWidget (il en hérite), on peut aussi s'en servir de page
        QWidget *layoutElectronicalMotorBoard = new QWidget;
        QWidget *layoutBeaconReceiver = new QWidget;
        QWidget *layoutMechanicalMainBoard1 = new QWidget;
        QWidget *layoutMechanicalMainBoard2 = new QWidget;

        // Créer le contenu des pages de widgets
            // Titan Center
            QLineEdit *lineEdit = new QLineEdit("Entrez votre nom");
            QPushButton *bouton1 = new QPushButton("Cliquez ici");
            QPushButton *bouton2 = new QPushButton("Ou là…");

            QVBoxLayout *vboxTitanCenter = new QVBoxLayout;
            vboxTitanCenter->addWidget(lineEdit);
            vboxTitanCenter->addWidget(bouton1);
            vboxTitanCenter->addWidget(bouton2);

            layoutTitanCenter->setLayout(vboxTitanCenter);

            // Terminal
            QGroupBox *commandeTerminalGroupBox= new QGroupBox(tr("Commande Terminal"));
            QVBoxLayout *layoutTerminal1 = new QVBoxLayout;
            QHBoxLayout *layoutTerminal11 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal12 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal13 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal14 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal15 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal16 = new QHBoxLayout;
            QHBoxLayout *layoutTerminal17 = new QHBoxLayout;
            terminalText1 = new QLineEdit;
            button_terminal_text1 = new QPushButton(textButtonSendTerminal);
            button_terminal_text1->setMaximumWidth(60);
            terminalText2 = new QLineEdit;
            button_terminal_text2 = new QPushButton(textButtonSendTerminal);
            button_terminal_text2->setMaximumWidth(60);
            terminalText3 = new QLineEdit;
            button_terminal_text3 = new QPushButton(textButtonSendTerminal);
            button_terminal_text3->setMaximumWidth(60);
            terminalText4 = new QLineEdit;
            button_terminal_text4 = new QPushButton(textButtonSendTerminal);
            button_terminal_text4->setMaximumWidth(60);
            terminalText5 = new QLineEdit;
            button_terminal_text5 = new QPushButton(textButtonSendTerminal);
            button_terminal_text5->setMaximumWidth(60);
            terminalText6 = new QLineEdit;
            button_terminal_text6 = new QPushButton(textButtonSendTerminal);
            button_terminal_text6->setMaximumWidth(60);
            terminalText7 = new QLineEdit;
            button_terminal_text7 = new QPushButton(textButtonSendTerminal);
            button_terminal_text7->setMaximumWidth(60);
            button_terminal_1= new QPushButton(tr(messageButtonTerminal1));
            button_terminal_2= new QPushButton(tr(messageButtonTerminal2));
            button_terminal_3= new QPushButton(tr(messageButtonTerminal3));
            button_terminal_4= new QPushButton(tr(messageButtonTerminal4));
                layoutTerminal11->addWidget(terminalText1);
                layoutTerminal11->addWidget(button_terminal_text1);
                layoutTerminal12->addWidget(terminalText2);
                layoutTerminal12->addWidget(button_terminal_text2);
                layoutTerminal13->addWidget(terminalText3);
                layoutTerminal13->addWidget(button_terminal_text3);
                layoutTerminal14->addWidget(terminalText4);
                layoutTerminal14->addWidget(button_terminal_text4);
                layoutTerminal15->addWidget(terminalText5);
                layoutTerminal15->addWidget(button_terminal_text5);
                layoutTerminal16->addWidget(terminalText6);
                layoutTerminal16->addWidget(button_terminal_text6);
                layoutTerminal17->addWidget(terminalText7);
                layoutTerminal17->addWidget(button_terminal_text7);

                layoutTerminal1->addLayout(layoutTerminal11);
                layoutTerminal1->addLayout(layoutTerminal12);
                layoutTerminal1->addLayout(layoutTerminal13);
                layoutTerminal1->addLayout(layoutTerminal14);
                layoutTerminal1->addLayout(layoutTerminal15);
                layoutTerminal1->addLayout(layoutTerminal16);
                layoutTerminal1->addLayout(layoutTerminal17);
                layoutTerminal1->addWidget(button_terminal_1);
                layoutTerminal1->addWidget(button_terminal_2);
                layoutTerminal1->addWidget(button_terminal_3);
                layoutTerminal1->addWidget(button_terminal_4);

            commandeTerminalGroupBox->setLayout(layoutTerminal1);
            commandeTerminalGroupBox->setMaximumWidth(180);

            terminal= new Terminal;
            terminal->setEnabled(false);

            QHBoxLayout *hboxTerminal = new QHBoxLayout;
            hboxTerminal->addWidget(commandeTerminalGroupBox);
            hboxTerminal->addWidget(terminal);

            layoutTerminal->setLayout(hboxTerminal);

            // MPU

            QGroupBox *MPUGroupBox= new QGroupBox(tr("Data Transfer"));

            QHBoxLayout *layoutMPUCentral = new QHBoxLayout(MPUGroupBox);

                QGroupBox *boxMPUAcc = new QGroupBox;// (tr("Accélération Transversale"));
                QHBoxLayout *layoutMPUAcceleration = new QHBoxLayout;
                    QVBoxLayout *AccX = new QVBoxLayout;
                    QVBoxLayout *AccY = new QVBoxLayout;
                    QVBoxLayout *AccZ = new QVBoxLayout;

                    sliderAccX = new QSlider(Qt::Horizontal);
                    sliderAccX->setFixedWidth(100);
                    sliderAccX->setValue(50);
                    sliderAccX->setEnabled(false);

                    sliderAccY = new QSlider(Qt::Horizontal);
                    sliderAccY->setFixedWidth(100);
                    sliderAccY->setValue(50);
                    sliderAccY->setEnabled(false);

                    sliderAccZ = new QSlider(Qt::Horizontal);
                    sliderAccZ->setFixedWidth(100);
                    sliderAccZ->setValue(50);
                    sliderAccZ->setEnabled(false);

                    QLabel *textAccX = new QLabel;
                    textAccXValue = new QLabel;
                    QLabel *textAccY = new QLabel;
                    textAccYValue = new QLabel;
                    QLabel *textAccZ = new QLabel;
                    textAccZValue = new QLabel;

                    customPlotAccXValue = new QCustomPlot;
                    customPlotAccXValue->setFixedHeight(270);
                    customPlotAccXValue->setFixedWidth(750);
                    customPlotAccXValue->setBackground(QColor(29, 11, 57, 240));

                    textAccX->setText("X");
                    textAccX->setAlignment(Qt::AlignCenter);
                    //AccX->addWidget(textAccX);
                    //AccX->addWidget(textAccXValue);
                    //AccX->addWidget(sliderAccX);
                    AccX->addWidget(customPlotAccXValue);

                    layoutMPUAcceleration->addLayout(AccX);
                    layoutMPUAcceleration->addLayout(AccY);
                    layoutMPUAcceleration->addLayout(AccZ);

                boxMPUAcc->setLayout(layoutMPUAcceleration);

                QGroupBox *boxMPUGyro = new QGroupBox (tr("Accélération Angulaire"));
                QHBoxLayout *layoutMPUGyro = new QHBoxLayout;
                    QVBoxLayout *GyroX = new QVBoxLayout;
                    QVBoxLayout *GyroY = new QVBoxLayout;
                    QVBoxLayout *GyroZ = new QVBoxLayout;

                    sliderGyroX = new QDial;
                    sliderGyroX->setValue(50);
                    sliderGyroX->setFixedWidth(60);
                    sliderGyroX->setEnabled(false);

                    sliderGyroY = new QDial;
                    sliderGyroY->setFixedWidth(60);
                    sliderGyroY->setValue(50);
                    sliderGyroY->setEnabled(false);

                    sliderGyroZ = new QDial;
                    sliderGyroZ->setFixedWidth(60);
                    sliderGyroZ->setValue(50);
                    sliderGyroZ->setEnabled(false);

                    QLabel *textGyroX = new QLabel;
                    QLabel *textGyroY = new QLabel;
                    QLabel *textGyroZ = new QLabel;

                    textGyroX->setText("X");
                    textGyroX->setAlignment(Qt::AlignCenter);
                    GyroX->addWidget(textGyroX);
                    GyroX->addWidget(sliderGyroX);

                    textGyroY->setText("Y");
                    textGyroY->setAlignment(Qt::AlignCenter);
                    GyroY->addWidget(textGyroY);
                    GyroY->addWidget(sliderGyroY);

                    textGyroZ->setText("Z");
                    textGyroZ->setAlignment(Qt::AlignCenter);
                    GyroZ->addWidget(textGyroZ);
                    GyroZ->addWidget(sliderGyroZ);

                    layoutMPUGyro->addLayout(GyroX);
                    layoutMPUGyro->addLayout(GyroY);
                    layoutMPUGyro->addLayout(GyroZ);

                boxMPUGyro->setLayout(layoutMPUGyro);

            layoutMPUCentral->addWidget(boxMPUAcc);
            //layoutMPUCentral->addWidget(boxMPUGyro);
            //boxMPUAcc->setStyleSheet("border: 1px solid red;");

            MPUGroupBox->setLayout(layoutMPUCentral);
            MPUGroupBox->setMaximumWidth(800);
            MPUGroupBox->setMaximumHeight(350);


            //*****************************************//
            QGroupBox *GaugeGroupBox= new QGroupBox(tr("Graphique"));
            QHBoxLayout *layoutGaugeCentral = new QHBoxLayout(GaugeGroupBox);


            //************ SPEED DESIGN *************//

            mSpeedGauge = new QcGaugeWidget;
            mSpeedGauge->addBackground(99);

            QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
            bkg1->clearrColors();
            bkg1->addColor(0.1,Qt::black);
            bkg1->addColor(1.0,Qt::white);

            QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
            bkg2->clearrColors();
            bkg2->addColor(0.1,Qt::gray);
            bkg2->addColor(1.0,Qt::darkGray);

            mSpeedGauge->addArc(55);
            mSpeedGauge->addDegrees(65)->setValueRange(0,1);// position de la bande noire
            mSpeedGauge->addColorBand(50);//position des bandes de couleur

            mSpeedGauge->addValues(80)->setValueRange(0,1);// position des echelles /// valeur max

            mSpeedGauge->addLabel(60)->setText("m/s"); // position //unité
            QcLabelItem *lab = mSpeedGauge->addLabel(40); //position du texte de la vitesse
            lab->setText("0");
            mSpeedNeedle = mSpeedGauge->addNeedle(60);//longueure de l'aiguille
            mSpeedNeedle->setLabel(lab);//valeur d'init
            mSpeedNeedle->setColor(Qt::white);//couleur de l'aiguille
            mSpeedNeedle->setValueRange(0,1);//min et max de l'aiguille
            mSpeedGauge->addBackground(7);
            mSpeedGauge->addGlass(88); //reflet
            mSpeedGauge->setFixedHeight(130);//dimension

            //************** ATTITUDE DESIGN **************//
            mAttitudeGauge = new QcGaugeWidget;
            mAttitudeGauge->addBackground(99);
            QcBackgroundItem *bkg = mAttitudeGauge->addBackground(92);
            bkg->clearrColors();
            bkg->addColor(0.1,Qt::black);
            bkg->addColor(1.0,Qt::white);
            mAttMeter = mAttitudeGauge->addAttitudeMeter(88);

            mAttitudeNeedle = mAttitudeGauge->addNeedle(70);
            mAttitudeNeedle->setMinDegree(0);
            mAttitudeNeedle->setMaxDegree(180);
            mAttitudeNeedle->setValueRange(0,180);
            mAttitudeNeedle->setCurrentValue(90);
            mAttitudeNeedle->setColor(Qt::white);
            mAttitudeNeedle->setNeedle(QcNeedleItem::AttitudeMeterNeedle);
            mAttitudeGauge->addGlass(80);
            mAttitudeGauge->setFixedHeight(130);


            //************** COMPASS DESIGN *********************//
            mCompassGauge = new QcGaugeWidget;

            mCompassGauge->addBackground(99);
            QcBackgroundItem *bkg3 = mCompassGauge->addBackground(92);
            bkg3->clearrColors();
            bkg3->addColor(0.1,Qt::black);
            bkg3->addColor(1.0,Qt::white);

            QcBackgroundItem *bkg4 = mCompassGauge->addBackground(88);
            bkg4->clearrColors();
            bkg4->addColor(0.1,Qt::white);
            bkg4->addColor(1.0,Qt::black);

            QcLabelItem *w = mCompassGauge->addLabel(80);
            w->setText("W");
            w->setAngle(0);
            w->setColor(Qt::white);

            QcLabelItem *n = mCompassGauge->addLabel(80);
            n->setText("N");
            n->setAngle(90);
            n->setColor(Qt::white);

            QcLabelItem *e = mCompassGauge->addLabel(80);
            e->setText("E");
            e->setAngle(180);
            e->setColor(Qt::white);

            QcLabelItem *s = mCompassGauge->addLabel(80);
            s->setText("S");
            s->setAngle(270);
            s->setColor(Qt::white);

            QcDegreesItem *deg = mCompassGauge->addDegrees(70);
            deg->setStep(5);
            deg->setMaxDegree(360);
            deg->setMinDegree(0);
            deg->setColor(Qt::white);
            mCompassNeedle = mCompassGauge->addNeedle(60);
            mCompassNeedle->setNeedle(QcNeedleItem::CompassNeedle);
            mCompassNeedle->setValueRange(0,360);
            mCompassNeedle->setMaxDegree(360);
            mCompassNeedle->setMinDegree(0);
            mCompassGauge->addBackground(7);
            mCompassGauge->addGlass(88);
            mCompassGauge->setFixedHeight(130);


            mTempGauge = new QLabel;
            mTempGauge->setText("0°C");


            //************************//

            layoutGaugeCentral->addWidget(mSpeedGauge);
            layoutGaugeCentral->addWidget(mAttitudeGauge);
            layoutGaugeCentral->addWidget(mCompassGauge);
            layoutGaugeCentral->addWidget(mTempGauge);

            GaugeGroupBox->setLayout(layoutGaugeCentral);

            startMPUButton = new QPushButton (tr("Start MPU"));
            startMPUButton->setMaximumWidth(100);

            stopMPUButton = new QPushButton (tr("Stop MPU"));
            stopMPUButton->setMaximumWidth(100);

            QVBoxLayout *MPUBox = new QVBoxLayout;
            MPUBox->addWidget(MPUGroupBox);

            MPUBox->addWidget(GaugeGroupBox);

            MPUBox->addWidget(startMPUButton);
            MPUBox->addWidget(stopMPUButton);
            layoutMPU->setLayout(MPUBox);

            // Page 3 (je ne vais afficher qu'une image ici, pas besoin de layout)

            layoutElectronicalMainBoard->setPixmap(QPixmap("icone.png"));
            layoutElectronicalMainBoard->setAlignment(Qt::AlignCenter);

            // Page 4


            // Page 5


            // Page 6


                // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
                onglets->addTab(layoutTitanCenter, "Titan Center");
                onglets->addTab(layoutTerminal, "Terminal");
                onglets->addTab(layoutMPU,"Motion Processor Unit");
                onglets->addTab(layoutElectronicalMainBoard, "Electronical Main Board");
                onglets->addTab(layoutElectronicalMotorBoard, "Electronical Motor Board");
                onglets->addTab(layoutBeaconReceiver, "Beacon Receiver");
                onglets->addTab(layoutMechanicalMainBoard1, "Mechanical Main Board 1");
                onglets->addTab(layoutMechanicalMainBoard2, "Mechanical Main Board 2");

    QHBoxLayout *layoutPrincipal = new QHBoxLayout;

    layoutPrincipal->addWidget(leftZoneWidget);
    layoutPrincipal->addWidget(onglets);

    zoneCentrale->setLayout(layoutPrincipal);
    setCentralWidget(zoneCentrale);
}


void MainWindow::fillPortsParameters(){
    baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    baudRateBox->setCurrentIndex(3);

    dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    dataBitsBox->setCurrentIndex(3);

    parityBox->addItem(tr("None"), QSerialPort::NoParity);
    parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void MainWindow::fillPortsInfo()
{
    serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        serialPortInfoListBox->addItem(list.first(), list);
    }

    serialPortInfoListBox->addItem(tr("Custom"));
}





