#include <QSlider>

#include "central.h"
#include "server.h"
#include "terminal.h"

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

        QGroupBox *serveurGroupBox= new QGroupBox(tr("Serveur"));

            serveurIP = new QLineEdit;
            serveurPort = new QSpinBox;
            serveurConnect = new QPushButton("Connexion");

            QFormLayout *layoutLeft1 = new QFormLayout;

            layoutLeft1->addRow("IP", serveurIP);
            layoutLeft1->addRow("Port", serveurPort);
            layoutLeft1->addWidget(serveurConnect);

        serveurGroupBox->setLayout(layoutLeft1);
        serveurGroupBox->setMaximumHeight(120);

        //------------
        QGroupBox *serialGroupBox= new QGroupBox(tr("Port Serie"));
            QLineEdit *age = new QLineEdit;

            QFormLayout *layoutLeft2 = new QFormLayout;
            layoutLeft2->addRow("Serial Port", age);

            QPushButton *SNButton = new QPushButton;
            SNButton = new QPushButton(tr("Connexion"));
            layoutLeft2->addWidget(SNButton);

        serialGroupBox->setLayout(layoutLeft2);

    //-------------
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(serveurGroupBox);
    vbox->addWidget(serialGroupBox);
    vbox->addWidget(verticalGroupBox);

    leftZoneWidget->setLayout(vbox);
    leftZoneWidget->setMaximumWidth(200);


    // --------------Onglets Widget ------------------//
    QTabWidget *onglets = new QTabWidget(this);

        // Créer les pages, en utilisant un widget parent pour contenir chacune des pages
        QWidget *layoutTitanCenter = new QWidget;
        QWidget *layoutTerminal = new QWidget;
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
            QVBoxLayout *layouta = new QVBoxLayout;

            QPushButton *buttonas= new QPushButton(tr("Button 1"));
            QPushButton *buttonbs= new QPushButton(tr("Button 2"));
                layouta->addWidget(buttonas);
                layouta->addWidget(buttonbs);

            commandeTerminalGroupBox->setLayout(layouta);

            Terminal *terminal;

            terminal= new Terminal;
            terminal->setEnabled(false);

            QHBoxLayout *hboxTerminal = new QHBoxLayout;
            hboxTerminal->addWidget(commandeTerminalGroupBox);
            hboxTerminal->addWidget(terminal);

            layoutTerminal->setLayout(hboxTerminal);

            // Page 3 (je ne vais afficher qu'une image ici, pas besoin de layout)

            layoutElectronicalMainBoard->setPixmap(QPixmap("icone.png"));
            layoutElectronicalMainBoard->setAlignment(Qt::AlignCenter);

            // Page 4


            // Page 5


            // Page 6


                // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
                onglets->addTab(layoutTitanCenter, "Titan Center");
                onglets->addTab(layoutTerminal, "Terminal");
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
