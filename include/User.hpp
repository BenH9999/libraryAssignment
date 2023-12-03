/* 
    Name: Ben Houghton
    Matric Number: 2498662
    Module Code: AC21008
*/

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

        template <typename T> void addNewBorrowedItem(T newItem);
        template <typename T> void returnItem(int pos);
        template <typename T> std::vector<T> getBorrowedItems();
        template <typename T> void setBorrowedItems(std::vector<T> newBorrowedItems);

        bool isEmpty();

        int getID();
        std::string getName();

        void setID(int newUserID);
        void setName(std::string newName);

        //overloading operator to be able to compare users for vector
        bool operator==(const User& other) const {
            return userID == other.userID && name == other.name && borrowedBooks == other.borrowedBooks && borrowedDVDs == other.borrowedDVDs;
        }
    private:
        int userID;
        std::string name;
        std::vector<Book> borrowedBooks;
        std::vector<DVD> borrowedDVDs;
        template <typename T> std::vector<T>* getItemContainer();
};