#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include <QtNetwork>
//#include "ui_FenClient.h"
#include "mainwindow.h"

class Server : public QWidget
{
    Q_OBJECT

    public:
        Server();
        void serverInitialisation();



    private slots:
        void on_boutonConnexion_clicked();
        void on_boutonEnvoyer_clicked();
        void on_message_returnPressed();
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);

    private:
        QTcpSocket *socket; // Représente le serveur
        quint16 tailleMessage;



        QTextEdit *listeMessages;
        QLineEdit *message;
        QPushButton *boutonConnexion;

};

#endif // SERVER_H
