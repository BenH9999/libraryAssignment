#pragma once

#include <iostream>

enum inventory{
    BOOK,
    DVDs
};

class Item{
    public:
        Item();
        Item(std::string title, bool available);

        std::string getTitle();
        bool getAvailable();

        void setTitle(std::string newTitle);
        void setAvailable(bool newAvailable);

        bool operator==(const Item& other) const {
            return title == other.title && available == other.available;
        }
    private:
        std::string title;
        bool available;
};