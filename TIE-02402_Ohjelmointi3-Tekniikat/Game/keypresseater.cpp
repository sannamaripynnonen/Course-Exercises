#include "keypresseater.hh"

KeyPressEater::KeyPressEater(QObject *parent) : QObject(parent)
{
}

KeyPressEater::~KeyPressEater()
{
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        emit sendKeyEvent(keyEvent);
        return true;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}
