#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include <QtNetwork>

#include "mainwindow.h"

class Server : public QWidget
{
    Q_OBJECT

    public:
        Server(QWidget *parent = 0);
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

        const char *getServeurIP();
        int getServeurPort();

};

#endif // SERVER_H
