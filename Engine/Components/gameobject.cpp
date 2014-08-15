#include "gameobject.h"

GameObject::GameObject() :
    name_("Empty"),
    type_(ObjectEmpty)
{
}

GameObject::GameObject(QString name) :
    name_(name),
    type_(ObjectEmpty)
{
}



//multiple object components
void GameObject::addGraphicsComponent(GraphicsComponent * graphicscomponent){
    graphicscomponent_ = graphicscomponent;
    type_ = type_ | ObjectGraphicsComponent; //binary or
}

GraphicsComponent* GameObject::getGraphicsComponent(){
    return graphicscomponent_;
}


void GameObject::update(){
    qDebug("dafuq");
    if((type_ & ObjectGraphicsComponent) == ObjectGraphicsComponent){ //binary and
        qDebug("daaaaafuq");
        graphicscomponent_->update(*this);
    }
}


QString GameObject::getName(){
    return name_;
}

void GameObject::setName(QString name){
    name_ = name;
}

QString GameObject::toString(){
    return "GameObject:" + name_;
}

int GameObject::getType(){
    return type_;
}
