#include <QScrollBar>
#include <QtCore/QDebug>

#include "mainwindow.h"
#include "terminal.h"

QString serialCommandSend;
QString serialCommandReceived;


int etat_serial_port;
Terminal *t_instances = 0;

Terminal::Terminal(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)//QPlainTextEdit
{
    document()->setMaximumBlockCount(100);
    p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    //etat_connexion_serial = 0; //serial port not open
}

void Terminal::putData(const QByteArray &data,int dir)
{
    switch (dir){
        case 0 :
            p.setColor(QPalette::Text, Qt::green);
            setPalette(p);
            appendPlainText(QString(data));//appendPlainText
            // memorise la commande
            serialCommandSend = "a"+data.left(2) ;
            //serialCommandReceived = data;
            break;
        case 1 :
            p.setColor(QPalette::Text, Qt::green);
            setPalette(p);
            insertPlainText(QString(data));
            serialCommandReceived = serialCommandReceived+data;
            break;
    }
    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Terminal::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Terminal::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());//QPlainTextEdit
    }
}

void Terminal::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Terminal::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Terminal::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}

void Terminal::terminalInitialisation(){

}

Terminal *Terminal::instances()
{
    if(!t_instances) t_instances = new Terminal();
    return t_instances;
}

int Terminal::getEtatConnexionSerial(){
    return etat_connexion_serial;
}

void Terminal::setEtatConnexionSerial(int etat){
    etat_connexion_serial = etat;
}

void Terminal::on_bouton_serial_connexion_clicked(){
    switch (etat_serial_port){
        case 0 : emit openSerialPortTerminal();break;
        case 1 : emit closeSerialPortTerminal();break;
        case -1 : emit openSerialPortTerminal();break;
        default : break;
    }
}

Terminal::Settings Terminal::settings() const
{
    return currentSettings;
}




