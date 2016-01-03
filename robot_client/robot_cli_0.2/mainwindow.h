#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMessageBox>
#include <QtWidgets>
#include <QWidget>

#include "apropos.h"
#include "central.h"
#include "server.h"
#include "settingsdialog.h"
#include "terminal.h"

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
    MainWindow();

    QLineEdit *serveurIP;
    QSpinBox *serveurPort;

    int getServeurPort();
    QString getServeurIp();

    QStatusBar *barreEtat1;
    QLabel *statusLabel;

    QComboBox *serialPortInfoListBox;
    QComboBox *baudRateBox;
    QComboBox *dataBitsBox;
    QComboBox *parityBox;
    QComboBox *stopBitsBox;
    QComboBox *flowControlBox;

    void openSerialPort();
    void closeSerialPort();


    public slots:
    void aPropos();
    void status_en_cours();
    void status_connecte(char *toto, bool etat_connection);
    void status_erreur_connection();

    private:
    void createActions();
    void createMenus();
    void createCentral();
    void createStatus();
    void createToolBars();
    void createControls(const QString &title);

    void zoneCentralCenter();

    void initServer();

    void fillPortsParameters();
    void fillPortsInfo();

    QPushButton *serveurConnect;
    //Server *servv;

    QWidget *zoneCentrale;
    QMenu *menuConfiguration;
    QAction *actionReseau;
    QAction *actionPortSerie;
    QMenu *fichiersRecents;
    QAction *actionQuitter;

    QMenu *menuAide;
    QAction *actionAPropos;

    QPushButton *buttons_SN;
    QPushButton *buttons_mw0000;
    QPushButton *buttons_mw2020;
    QPushButton *buttons_mw4040;
    QPushButton *buttons_mw6060;

    Ui::MainWindow *ui;
    QLabel *status;
    Terminal *terminal;
    SettingsDialog *settings;
    QSerialPort *serial;
    QTimer      m_timer;
    QThread     m_tempo;


};

#endif // MAINWINDOW_H
