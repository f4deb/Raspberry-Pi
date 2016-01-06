#include <QScrollBar>
#include <QtCore/QDebug>

#include "mainwindow.h"
#include "terminal.h"

Terminal::Terminal(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    etat_connexion_serial = false;
}

void Terminal::putData(const QByteArray &data)
{
    insertPlainText(QString(data));

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
        emit getData(e->text().toLocal8Bit());
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

void Terminal::on_bouton_serial_connexion_clicked(){
    if (etat_connexion_serial == false)
    {
        emit openSerialPortTerminal();
        etat_connexion_serial = true;
    }
    else{
        emit closeSerialPortTerminal();
        etat_connexion_serial = false;
    }
}


Terminal::Settings Terminal::settings() const
{
    return currentSettings;
}




