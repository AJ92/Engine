#include "gameobject.h"
#include "Components/Interfaces/graphicscomponent.h"
#include "Components/Interfaces/locationcomponent.h"

GameObject::GameObject() :
    Object(),
    name_("Empty"),
    type_(ObjectEmpty)
{
}

GameObject::GameObject(QString name) :
    Object(),
    name_(name),
    type_(ObjectEmpty)
{
}


void GameObject::addGraphicsComponent(GraphicsComponent * component){
    graphicscomponent_ = component;
    type_ = type_ | ObjectGraphicsComponent; //binary or
}

bool GameObject::hasGraphicsComponent(){
    if((type_ & ObjectGraphicsComponent) == ObjectGraphicsComponent){ //binary and
        return true;
    }
    return false;
}

GraphicsComponent* GameObject::getGraphicsComponent(){
    return graphicscomponent_;
}



void GameObject::addLocationComponent(LocationComponent * component){
    locationcomponent_ = component;
    type_ = type_ | ObjectLocationComponent; //binary or
}

bool GameObject::hasLocationComponent(){
    if((type_ & ObjectLocationComponent) == ObjectLocationComponent){ //binary and
        return true;
    }
    return false;
}

LocationComponent* GameObject::getLocationComponent(){
    return locationcomponent_;
}




void GameObject::update(Renderer &renderer){
    if(this->hasGraphicsComponent()){
        graphicscomponent_->update(*this, renderer);
    }
    if(this->hasLocationComponent()){
        locationcomponent_->update(*this);
    }
}


QString GameObject::getName(){
    return name_;
}

void GameObject::setName(QString name){
    name_ = name;
}

QString GameObject::toString(){
    return "GameObject: " + name_;
}

int GameObject::getType(){
    return type_;
}
