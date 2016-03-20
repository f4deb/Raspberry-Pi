#include <QSlider>
#include <QtSerialPort/QSerialPortInfo>
#include <QIntValidator>
#include <QLineEdit>
#include <QLabel>

#include "central.h"
#include "server.h"
#include "terminal.h"

QT_USE_NAMESPACE

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");


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

                QGroupBox *boxMPUAcc = new QGroupBox (tr("Accélération Transversale"));
                QHBoxLayout *layoutMPUAcceleration = new QHBoxLayout;
                    QVBoxLayout *AccX = new QVBoxLayout;
                    QVBoxLayout *AccY = new QVBoxLayout;
                    QVBoxLayout *AccZ = new QVBoxLayout;

                    QSlider *sliderAccX = new QSlider(Qt::Horizontal);
                    sliderAccX->setFixedWidth(100);
                    sliderAccX->setValue(50);
                    sliderAccX->setEnabled(false);


                    QSlider *sliderAccY = new QSlider(Qt::Horizontal);
                    sliderAccY->setFixedWidth(100);
                    sliderAccY->setValue(50);
                    sliderAccY->setEnabled(false);

                    QSlider *sliderAccZ = new QSlider(Qt::Horizontal);
                    sliderAccZ->setFixedWidth(100);
                    sliderAccZ->setValue(50);
                    sliderAccZ->setEnabled(false);

                    QLabel *textAccX = new QLabel;
                    QLabel *textAccY = new QLabel;
                    QLabel *textAccZ = new QLabel;

                    textAccX->setText("X");
                    textAccX->setAlignment(Qt::AlignCenter);
                    AccX->addWidget(textAccX);
                    AccX->addWidget(sliderAccX);

                    textAccY->setText("Y");
                    textAccY->setAlignment(Qt::AlignCenter);
                    AccY->addWidget(textAccY);
                    AccY->addWidget(sliderAccY);

                    textAccZ->setText("Z");
                    textAccZ->setAlignment(Qt::AlignCenter);
                    AccZ->addWidget(textAccZ);
                    AccZ->addWidget(sliderAccZ);

                    layoutMPUAcceleration->addLayout(AccX);
                    layoutMPUAcceleration->addLayout(AccY);
                    layoutMPUAcceleration->addLayout(AccZ);

                boxMPUAcc->setLayout(layoutMPUAcceleration);

                QGroupBox *boxMPUGyro = new QGroupBox (tr("Accélération Angulaire"));
                QHBoxLayout *layoutMPUGyro = new QHBoxLayout;
                    QVBoxLayout *GyroX = new QVBoxLayout;
                    QVBoxLayout *GyroY = new QVBoxLayout;
                    QVBoxLayout *GyroZ = new QVBoxLayout;

                    QDial *sliderGyroX = new QDial;
                    sliderGyroX->setValue(50);
                    sliderGyroX->setFixedWidth(100);
                    sliderGyroX->setEnabled(false);

                    QDial *sliderGyroY = new QDial;
                    sliderGyroY->setFixedWidth(100);
                    sliderGyroY->setValue(50);
                    sliderGyroY->setEnabled(false);

                    QDial *sliderGyroZ = new QDial;
                    sliderGyroZ->setFixedWidth(100);
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
            layoutMPUCentral->addWidget(boxMPUGyro);
            //boxMPUAcc->setStyleSheet("border: 1px solid red;");

            MPUGroupBox->setLayout(layoutMPUCentral);
            MPUGroupBox->setMaximumWidth(800);
            MPUGroupBox->setMaximumHeight(150);


            startMPUButton = new QPushButton (tr("Start MPU"));
            startMPUButton->setMaximumWidth(100);

            QVBoxLayout *MPUBox = new QVBoxLayout;
            MPUBox->addWidget(MPUGroupBox);
            MPUBox->addWidget(startMPUButton);
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
