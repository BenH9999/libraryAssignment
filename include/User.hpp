#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Book.hpp"
#include "DVD.hpp"

class User{
    public:
        User();
        //~User();
        template <typename T> void addNewBorrowedItem(T newItem);
        template <typename T> void returnItem(int pos);
        template <typename T> std::vector<T> getBorrowedItems();
        template <typename T> void setBorrowedItems(std::vector<T> newBorrowedItems);

        bool isEmpty();

        int getID();
        std::string getName();

        void setID(int newUserID);
        void setName(std::string newName);

        bool operator==(const User& other) const {
            return userID == other.userID && name == other.name && borrowedBooks == other.borrowedBooks && borrowedDVDs == other.borrowedDVDs;
        }
    private:
        int userID;
        std::string name;
        std::vector<Book> borrowedBooks;
        std::vector<DVD> borrowedDVDs;
        template <typename T> std::pair<std::vector<T>*, int> getItemContainer();
};