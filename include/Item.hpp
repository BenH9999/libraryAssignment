/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

#pragma once

#include <iostream>

enum InventoryType{
    BOOK,
    DVDs,
    USER
};

class Item{
    public:
        Item();
        Item(std::string title, bool available);

        std::string getTitle() const;
        bool getAvailable();

        void setTitle(std::string newTitle);
        void setAvailable(bool newAvailable);

        //overloading operator to be able to compare items for vector
        bool operator==(const Item& other) const {
            return title == other.title && available == other.available;
        }
    private:
        std::string title;
        bool available;
};