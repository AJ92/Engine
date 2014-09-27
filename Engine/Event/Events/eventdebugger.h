#ifndef EVENTDEBUGGER_H
#define EVENTDEBUGGER_H

#include <QString>


class EventDebugger
{
public:
    EventDebugger(QString debugMessage);
    EventDebugger(double debugValue);
    ~EventDebugger();

    QString getDebugMessage();
    void setDebugMessage(QString debugMessage);

    double getDebugValue();
    void setDebugValue(double debugValue);

private:
    QString debugMessage;
    double debugValue;
};

#endif // EVENTDEBUGGER_H
