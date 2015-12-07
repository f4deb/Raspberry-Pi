#ifndef TERMINAL
#define TERMINAL

#include <QPlainTextEdit>

class Terminal : public QPlainTextEdit
{
    Q_OBJECT

signals:
//    void getData(const QByteArray &data);

public:
    explicit Terminal(QWidget *parent = 0);

    void putData(const QByteArray &data);

//    void setLocalEchoEnabled(bool set);

protected:
/*
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);
*/
private:
    bool localEchoEnabled;

};

#endif // TERMINAL

