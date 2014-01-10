#ifndef EVENTDEBUGGER_H
#define EVENTDEBUGGER_H

#include <QString>

class EventDebugger
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
