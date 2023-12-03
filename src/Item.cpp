/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "Item.hpp"

Item::Item(){
    title = "";
    available = 1;
}

/*
main constructor used
*/
Item::Item(std::string title, bool available){
    this->title = title;
    this->available = available;
}

/*
getters
*/
std::string Item::getTitle() const{
    return this->title;
}

bool Item::getAvailable(){
    return this->available;
}

/*
setters
*/
void Item::setTitle(std::string newTitle){
    this->title = newTitle;
}

void Item::setAvailable(bool newAvailable){
    this->available = newAvailable;
}