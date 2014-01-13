#ifndef EVENTDEBUGGER_H
#define EVENTDEBUGGER_H

#include <QString>
#include "Object/object.h"

class EventDebugger : public Object
{
public:
    EventDebugger(QString debugMessage);
    ~EventDebugger();

    QString getDebugMessage();
    void setDebugMessage(QString debugMessage);

private:
    QString debugMessage;
};

#endif // EVENTDEBUGGER_H
