#include <QtWidgets>
#include <QMainWindow>

#include "server.h"
#include "singleton.h"
#include "mainwindow.h"

int etat_serveur_port;
QString adresseServeurIp;

QByteArray message_from_server;

Server *p_instances = 0;

Server::Server(QWidget *parent) : QWidget(parent){
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    //etat_connexion  = false;
    etat_serveur_port = 0;
    tailleMessage = 0;
}

void Server::serverInitialisation(){

}

// Tentative de connexion/deconnexion au serveur
void Server::on_boutonConnexion_clicked(){

    if (etat_serveur_port == 0)
    {
        socket->abort(); // On désactive les connexions précédentes s'il y en a
        socket->connectToHost(getServeurIP(), getServeurPort()); // On se connecte au serveur demandé
    }
    else{
        socket->disconnectFromHost();
    }
}

void Server::write(QByteArray paquet){

    QDataStream out(&paquet, QIODevice::WriteOnly);
    // On prépare le paquet à envoyer
    QString messageAEnvoyer = paquet;

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); // On envoie le paquet
}

// Envoi d'un message au serveur
void Server::on_boutonEnvoyer_clicked()
{
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On prépare le paquet à envoyer
    QString messageAEnvoyer = message->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); // On envoie le paquet

    message->clear(); // On vide la zone d'écriture du message
    message->setFocus(); // Et on remet le curseur à l'intérieur
}

// Appuyer sur la touche Entrée a le même effet que cliquer sur le bouton "Envoyer"
void Server::on_message_returnPressed()
{
    on_boutonEnvoyer_clicked();
}

// On a reçu un paquet (ou un sous-paquet)
void Server::donneesRecues()
{
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaie de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;

    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;
    message_from_server = messageRecu.toUtf8();

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
    emit dataServerReceived();
}

// Ce slot est appelé lorsque la connexion au serveur a réussi
void Server::connecte(){
    etat_serveur_port = 1;
    emit on_connect("Connexion réussie !");
}

// Ce slot est appelé lorsqu'on est déconnecté du serveur
void Server::deconnecte(){
    etat_serveur_port = 0;
    emit on_connect("Déconnexion réussie !");
}

// Ce slot est appelé lorsqu'il y a une erreur
void Server::erreurSocket(QAbstractSocket::SocketError erreur){
    switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            listeMessages->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
    //        listeMessages->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            listeMessages->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            listeMessages->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }
}

 const char *Server::getServeurIP(void){
     QString tata = adresseServeurIp;
     const char *toto;
     toto = adresseServeurIp.toStdString().c_str();
    return (toto);
}

int Server::getServeurPort(void){
    int value = Server::instances()->GetPortValue();
    return (value);
}

Server *Server::instances()
{
    if(!p_instances) p_instances = new Server();
    return p_instances;
}

int Server::GetPortValue()
{
    return port_value;
}
void Server::SetPortValue(int value)
{
    port_value = value;
}
