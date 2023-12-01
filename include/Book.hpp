#pragma once

#include "Item.hpp"
#include <iostream>

class Book: public Item{
    public:
        Book();
        Book(std::string isbn, std::string title,std::string author,bool available);
        //~Book();

        std::string getAuthor();
        std::string getISBN();

        void setAuthor(std::string newAuthor);
        void setISBN(std::string newISBN);

        //overloading operator to be able to compare books for vector
        bool operator==(const Book& other) const {
            return static_cast<const Item&>(*this) == static_cast<const Item&>(other) && ISBN == other.ISBN && /*title == other.title &&*/ author == other.author /*&& available == other.available*/;
        }
    private:
        std::string ISBN;
        std::string author;
};