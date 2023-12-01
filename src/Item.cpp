#include "Item.hpp"

Item::Item(){
    title = "";
    available = 1;
}

Item::Item(std::string title, bool available){
    this->title = title;
    this->available = available;
}

std::string Item::getTitle(){
    return this->title;
}

bool Item::getAvailable(){
    return this->available;
}

void Item::setTitle(std::string newTitle){
    this->title = newTitle;
}

void Item::setAvailable(bool newAvailable){
    this->available = newAvailable;
}