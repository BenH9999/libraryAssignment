#include "DVD.hpp"

DVD::DVD(){
    genre = "";
    rating = 0.0;
}

DVD::DVD(std::string title,int id,std::string genre,double rating, bool available) : Item(title,available){
    this->id = id;
    this->genre = genre;
    this->rating = rating;
}

int DVD::getID(){
    return this->id;
}

std::string DVD::getGenre(){
    return this->genre;
}

double DVD::getRating(){
    return this->rating;
}

void DVD::setID(int newID){
    this->id = newID;
}

void DVD::setGenre(std::string newGenre){
    this->genre = newGenre;
}

void DVD::setRating(double newRating){
    this->rating = newRating;
}