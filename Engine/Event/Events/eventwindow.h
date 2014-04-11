#ifndef EVENTWINDOW_H
#define EVENTWINDOW_H

#include <QString>

class EventWindow
{
public:
    EventWindow(int sizeX, int sizeY);
    ~EventWindow();

    int getSizeX();
    void setSizeX(int sizeX);

    int getSizeY();
    void setSizeY(int sizeY);

private:
    int sizeX;
    int sizeY;
};

#endif // EVENTWINDOW_H
