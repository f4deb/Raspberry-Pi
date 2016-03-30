#ifndef TERMINAL
#define TERMINAL

#include <QPlainTextEdit>
#include <QTextEdit>
#include <QDialog>
#include <QtSerialPort/QSerialPort>

class Terminal : public QPlainTextEdit//QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);
    void openSerialPortTerminal();
    void closeSerialPortTerminal();

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };



    explicit Terminal(QWidget *parent = 0);

    Settings settings() const;

    void putData(const QByteArray &data, int dir);
    void setLocalEchoEnabled(bool set);
    void terminalInitialisation();


    static Terminal *instances();
    int getEtatConnexionSerial();
    void setEtatConnexionSerial(int);


protected:

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;

    int etat_connexion_serial;


    void updateSettings();

    Settings currentSettings;

    QPalette p;

private slots:
    void on_bouton_serial_connexion_clicked();
};

#endif // TERMINAL

