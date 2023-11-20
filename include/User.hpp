#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Book.hpp"

class User{
    public:
        User();
        //~User();
        void addNewBorrowedBook(Book newBook);
        bool isEmpty();

        int getUserID();
        std::string getName();
        std::vector<Book> getBorrowedBooks();

        void setUserID(int newUserID);
        void setName(std::string newName);
        void setBorrowedBooks(std::vector<Book> newBorrowedBooks);

        bool operator==(const User& other) const {
            return userID == other.userID && name == other.name && borrowedBooks == other.borrowedBooks;
        }
    private:
        int userID;
        std::string name;
        std::vector<Book> borrowedBooks;
};