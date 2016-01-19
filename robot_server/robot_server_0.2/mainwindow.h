#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow();
        void envoyerATous(const QString &message);
        char *messages;
        bool first;

    private slots:
        void nouvelleConnexion();
        void donneesRecues();
        void deconnexionClient();
        void openSerialPort();
        void closeSerialPort();
        void open1();
        void readData();
        //QByteArray reaAlldData();

    private:
        QLabel *etatServeur;
        QPushButton *boutonQuitter;
        QPushButton *buttonUartConnect;
        QPushButton *buttonUartDisconnect;
        QPushButton *buttonSettings;
        QPushButton *buttona;
        QTcpServer *serveur;
        QList<QTcpSocket *> clients;
        quint16 tailleMessage;

        void showStatusMessage(const QString &message);


        Ui::MainWindow *ui;
        QLabel *status;
        Console *console;
        SettingsDialog *settings;
        QSerialPort *serial;
        QTimer      m_timer;
        QThread     m_tempo;

};

#endif // MAINWINDOW_H

