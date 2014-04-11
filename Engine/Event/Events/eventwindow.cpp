#include "eventwindow.h"

EventWindow::EventWindow(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
}

EventWindow::~EventWindow(){

}

int EventWindow::getSizeX(){
    return sizeX;
}

void EventWindow::setSizeX(int sizeX){
    this->sizeX = sizeX;
}

int EventWindow::getSizeY(){
    return sizeY;
}

void EventWindow::setSizeY(int sizeY){
    this->sizeY = sizeY;
}
