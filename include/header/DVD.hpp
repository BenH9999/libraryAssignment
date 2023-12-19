/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#pragma once

#include "Item.hpp"

class DVD: public Item{
    public:
        DVD();
        DVD(std::string title,int id,std::string genre,double rating, bool available);

        int getID();
        std::string getGenre();
        double getRating();

        void setID(int newID);
        void setGenre(std::string newGenre);
        void setRating(double newRating);

        //overloading operator to be able to compare DVDs for vector
        bool operator==(const DVD& other) const {
            return static_cast<const Item&>(*this) == static_cast<const Item&>(other) && id == other.id && genre == other.genre && rating == other.rating; 
        }
    private:
        int id;
        std::string genre;
        double rating;
};