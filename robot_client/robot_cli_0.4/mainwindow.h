#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QIcon>
#include <QMessageBox>
#include <QtWidgets>
#include <QWidget>


#include "../../Qt-custom-gauge-widget-master/source/qcgaugewidget.h"
#include "../../qcustomplot/qcustomplot.h"

#include "apropos.h"
#include "central.h"
#include "mpu.h"
#include "server.h"
#include "terminal.h"


QT_BEGIN_NAMESPACE

class QLabel;


namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

#define messageButtonTerminal1 "SN"
#define messageButtonTerminal2 "mw2020"
#define messageButtonTerminal3 "mw4040"
#define messageButtonTerminal4 "mw0000"
#define textButtonSendTerminal "->send"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct mpuValue{
        short AX;
        short AY;
        short AZ;
        short GX;
        short GY;
        short GZ;
        int compassValue;
        short rollValue;
        short pitchValue;
        short speedValue;
        int temp;
        int time_mpu;
    };

    MainWindow();
    void ssetupAdvancedAxesDemo(QCustomPlot *customPlot);
    //void realtimeDataSlot();

    QCPMarginGroup *marginGroup;
    QCPAxisRect *wideAxisRect;


    QCPAxisRect *wideAxisRect1;
    QCPAxisRect *wideAxisRect2;
    QCPAxisRect *wideAxisRect3;
    QCPAxisRect *wideAxisRect4;
    QCPAxisRect *wideAxisRect5;
    QCPAxisRect *wideAxisRect6;

    QCPGraph *mainGraph1;
    QCPGraph *mainGraph2;
    QCPGraph *mainGraph3;
    QCPGraph *mainGraph4;
    QCPGraph *mainGraph5;
    QCPGraph *mainGraph6;

    QTimer dataTimer;
    QCustomPlot *customPlotAccXValue;
    QCustomPlot *customPlotAccYValue;
    QCustomPlot *customPlotAccZValue;

    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void setupAdvancedAxesDemo(QCustomPlot *customPlot);










    QLineEdit *serveurIP;
    QSpinBox *serveurPort;

    int getServeurPort();
    QString getServeurIpM();

    QStatusBar *barreEtat1;
    QLabel *statusLabel;

    QComboBox *serialPortInfoListBox;
    QComboBox *baudRateBox;
    QComboBox *dataBitsBox;
    QComboBox *parityBox;
    QComboBox *stopBitsBox;
    QComboBox *flowControlBox;

    bool first;

    mpuValue mpuaccess;

    QcGaugeWidget * mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;

    QcGaugeWidget * mAttitudeGauge;
    QcNeedleItem * mAttitudeNeedle;
    QcAttitudeMeter *mAttMeter;

    QcGaugeWidget * mCompassGauge;
    QcNeedleItem *mCompassNeedle;

    QLabel *mTempGauge;

    QPushButton *startMPUButton;
    QPushButton *stopMPUButton ;

    QLabel *status;
    Terminal *terminal;

    Server *servv;

    QSerialPort *serial;

    Mpus *test;

public slots:
    void aPropos();
    void status_en_cours();
    void status_connecte(char *toto);
    void status_erreur_connection();
    void openSerialPort();
    void closeSerialPort();



private slots :
    void writeData(const QByteArray &data);
    void readData();
    void buttonTerminalText1();
    void buttonTerminalText2();
    void buttonTerminalText3();
    void buttonTerminalText4();
    void buttonTerminalText5();
    void buttonTerminalText6();
    void buttonTerminalText7();
    void buttonTerminal1();
    void buttonTerminal2();
    void buttonTerminal3();
    void buttonTerminal4();

    void buttonStartMPU();
    void buttonStopMPU();

    void realtimeDataSlot();


private:

    void mpuCalculate();
    void createActions();
    void createMenus();
    void createCentral();
    void createStatus();
    void createToolBars();
    void createControls(const QString &title);

    void zoneCentralCenter();

    void initServer();
    void initSerialPort();

    void initTerminalConnections();

    void initMPU();

    void fillPortsParameters();
    void fillPortsInfo();

    QPushButton *serveurConnect;
    //Server *servv;

    QGroupBox *serveurGroupBox;
    QGroupBox *serialGroupBox;

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

    //button Terminal tab
    QLineEdit *terminalText1;
    QLineEdit *terminalText2;
    QLineEdit *terminalText3;
    QLineEdit *terminalText4;
    QLineEdit *terminalText5;
    QLineEdit *terminalText6;
    QLineEdit *terminalText7;
    QPushButton *button_terminal_text1;
    QPushButton *button_terminal_text2;
    QPushButton *button_terminal_text3;
    QPushButton *button_terminal_text4;
    QPushButton *button_terminal_text5;
    QPushButton *button_terminal_text6;
    QPushButton *button_terminal_text7;
    QPushButton *button_terminal_1;
    QPushButton *button_terminal_2;
    QPushButton *button_terminal_3;
    QPushButton *button_terminal_4;

    // Serial
    QPushButton *SerialConnectButton;


    //MPU
    QSlider *sliderAccX;
    QSlider *sliderAccY;
    QSlider *sliderAccZ;

    QLabel *textAccXValue;
    QLabel *textAccYValue;
    QLabel *textAccZValue;

    QDial *sliderGyroX;
    QDial *sliderGyroY;
    QDial *sliderGyroZ;



};

class SleeperThread : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};

#endif // MAINWINDOW_H
