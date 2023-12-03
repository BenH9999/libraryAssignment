/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#include "DVD.hpp"

DVD::DVD(){
    genre = "";
    rating = 0.0;
}

/*
main constructor used
*/
DVD::DVD(std::string title,int id,std::string genre,double rating, bool available) : Item(title,available){
    this->id = id;
    this->genre = genre;
    this->rating = rating;
}


/*
getters
*/
int DVD::getID(){
    return this->id;
}

std::string DVD::getGenre(){
    return this->genre;
}

double DVD::getRating(){
    return this->rating;
}

/*
setters
*/
void DVD::setID(int newID){
    this->id = newID;
}

void DVD::setGenre(std::string newGenre){
    this->genre = newGenre;
}

void DVD::setRating(double newRating){
    this->rating = newRating;
}