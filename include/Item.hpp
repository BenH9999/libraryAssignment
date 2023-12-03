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

        bool operator==(const Item& other) const {
            return title == other.title && available == other.available;
        }
    private:
        std::string title;
        bool available;
};