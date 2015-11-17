#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include "robot_uart.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>

MainWindow::MainWindow()
{
    //QMainWindow(parent),

    serial = new QSerialPort(this);

    settings = new SettingsDialog;

    // Création et disposition des widgets de la fenêtre
    etatServeur = new QLabel;
    boutonQuitter = new QPushButton(tr("Quitter"));
    buttonUartConnect = new QPushButton(tr("Open Uart"));
    buttonUartDisconnect = new QPushButton(tr("Close Uart"));
    buttonSettings = new QPushButton(tr("Uart Settings"));
    buttona = new QPushButton(tr("1"));


    connect(buttona, SIGNAL(clicked()), this, SLOT(open1()));


    connect(buttonUartConnect, SIGNAL(clicked()), this, SLOT(openSerialPort()));
    connect(buttonUartDisconnect, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(buttonSettings, SIGNAL(clicked()), settings, SLOT(show()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(etatServeur);
    layout->addWidget(buttona);
    layout->addWidget(buttonSettings);
    layout->addWidget(buttonUartConnect);
    layout->addWidget(buttonUartDisconnect);
    layout->addWidget(boutonQuitter);
    setLayout(layout);

    setWindowTitle(tr("ZeroChat - Serveur"));

    // Gestion du serveur
    serveur = new QTcpServer(this);
    if (!serveur->listen(QHostAddress::Any, 50885)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
    {
        // Si le serveur n'a pas été démarré correctement
        etatServeur->setText(tr("Le serveur n'a pas pu être démarré. Raison :<br />") + serveur->errorString());
    }
    else
    {
        // Si le serveur a été démarré correctement
        etatServeur->setText(tr("Le serveur a été démarré sur le port <strong>") + QString::number(serveur->serverPort()) + tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }
    tailleMessage = 0;
}

void MainWindow::nouvelleConnexion()
{
    envoyerATous(tr("<em>Un nouveau client vient de se connecter</em>"));

    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

void MainWindow::donneesRecues()
{
    // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    // Si tout va bien, on continue : on récupère le message

    QDataStream in(socket);

    if (tailleMessage == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
             return;

        in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (socket->bytesAvailable() < tailleMessage) // Si on n'a pas encore tout reçu, on arrête la méthode
        return;

    // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
    QString message;
    in >> message;

    // 2 : on renvoie le message à tous les clients
    QString mess = message;
    envoyerATous(mess);

    // Et sur la liaison serie
    QString tmp = message;
    QByteArray text = tmp.toLocal8Bit();
    char *data = new char[text.size() + 1];
    strcpy(data, text.data());
    delete [] data;

    serial->write(text);







    // 3 : remise de la taille du message à 0 pour permettre la réception des futurs messages
    tailleMessage = 0;

}

void MainWindow::deconnexionClient()
{
    envoyerATous(tr("<em>Un client vient de se déconnecter</em>"));

    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    clients.removeOne(socket);

    socket->deleteLater();
}


void MainWindow::envoyerATous(const QString &message)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    // Envoi du paquet préparé à tous les clients connectés au serveur
    for (int i = 0; i < clients.size(); i++)
    {
        clients[i]->write(paquet);
    }
}






void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
//      console->setEnabled(true);
//      console->setLocalEchoEnabled(p.localEchoEnabled);
    //  ui->actionConnect->setEnabled(false);
    //  ui->actionDisconnect->setEnabled(true);
    //  ui->actionConfigure->setEnabled(false);
//      showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
//                      .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
//                      .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
        } else {
//          QMessageBox::critical(this, tr("Error"), serial->errorString());

            showStatusMessage(tr("Open error"));
        }
    QByteArray datas = "mw2020";
    serial->write(datas);
}

void MainWindow::closeSerialPort()
{
    QByteArray datas = "mw0000";
    serial->write(datas);
    if (serial->isOpen())
        serial->close();

//    console->setEnabled(false);
//    ui->actionConnect->setEnabled(true);
//    ui->actionDisconnect->setEnabled(false);
//    ui->actionConfigure->setEnabled(true);
//    showStatusMessage(tr("Disconnected"));
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}




void MainWindow::open1()
{
    QByteArray datas = "mw0000";
    serial->write(datas);
}









