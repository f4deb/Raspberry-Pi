#ifndef TERMINAL
#define TERMINAL

#include <QPlainTextEdit>
#include <QDialog>
#include <QtSerialPort/QSerialPort>

class Terminal : public QPlainTextEdit
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

    void putData(const QByteArray &data);

    void setLocalEchoEnabled(bool set);

    void terminalInitialisation();

protected:

    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;
    bool etat_connexion_serial;
    void updateSettings();

    Settings currentSettings;


private slots:
    void on_bouton_serial_connexion_clicked();
};

#endif // TERMINAL

