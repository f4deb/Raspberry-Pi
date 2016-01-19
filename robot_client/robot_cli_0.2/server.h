#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets>
#include <QtNetwork>

//#include "mainwindow.h"

class Server : public QWidget
{
    Q_OBJECT

    public:
        explicit Server(QWidget *parent = 0);

        //bool etat_connexion;
        void serverInitialisation();
        void write(QByteArray paquet);

        //singleton
        static Server *instances();
        int  GetValue();
        void SetValue(int value);

    signals:
        void on_connect(char *mess_con);
        void on_error_connect();
        void dataServerReceived();

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

        int p_value;//singleton


};

#endif // SERVER_H
