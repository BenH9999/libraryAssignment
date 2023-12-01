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
    private:
        int id;
        std::string genre;
        double rating;
};