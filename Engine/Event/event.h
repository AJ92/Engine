#ifndef EVENT_H
#define EVENT_H

#include "Object/object.h"
#include <QString>
#include <QDebug>

class Event : public Object
{
public:

    enum Types {
        EventDebuggerMessage        = 0x00,
        EventDebuggerShow           = 0x01,
        EventDebuggerHide           = 0x02
    };

    Event(Types eventTypes);
    bool isType(Types eventTypes);
    void setString(QString string);
    QString getString();

public:
    Types types;
    QString string;
};

#endif // EVENT_H
