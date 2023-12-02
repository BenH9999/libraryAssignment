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
        void addNewBorrowedBook(Book newBook);
        void addNewBorrowedDVD(DVD newDVD);
        void returnBook(int pos);
        void returnDVD(int pos);
        bool isEmpty();

        int getUserID();
        std::string getName();
        std::vector<Book> getBorrowedBooks();
        std::vector<DVD> getBorrowedDVDs();

        void setUserID(int newUserID);
        void setName(std::string newName);
        void setBorrowedBooks(std::vector<Book> newBorrowedBooks);
        void setBorrowedDVDs(std::vector<DVD> addNewBorrowedDVDs);

        bool operator==(const User& other) const {
            return userID == other.userID && name == other.name && borrowedBooks == other.borrowedBooks && borrowedDVDs == other.borrowedDVDs;
        }
    private:
        int userID;
        std::string name;
        std::vector<Book> borrowedBooks;
        std::vector<DVD> borrowedDVDs;
};