#pragma once

#include "User.hpp"

class Library{
    public:
        Library();
        //~Library();

        void addNewBook(Book newBook);
        void addNewUser(User newUser);
        void deleteBook(Book bookToDelete);
        void deleteUser(User userToDelete);
        void searchBook(std::string searchTitle);
        void displayAvailableBooks();
        void displayAvailableDVDs();
        void displayAllUsers();
        void readInventory();
        void writeInventory();
        void readUsers();
        void writeUsers();
        std::string readQuotedString(std::istringstream& iss);
        std::pair<bool,Book> findBookByISBN(std::string isbn);
        std::pair<bool,User> findUserByUserID(int userID);
        std::pair<bool,DVD> findDVDByID(int dvdID);
        void borrowBook(Book newBook);
        void borrowDVD(DVD newDVD);
        void returnBorrowedBook(Book oldBook);
        void returnBorrowedDVD(DVD oldDVD);
        void syncUserChanges();
        size_t findBookIndex(int choice);
        size_t findDVDIndex(int choice);

        std::vector<Book> getBooks();
        std::vector<User> getUsers();
        std::vector<DVD> getDVDs();

        void setBooks(std::vector<Book> newBooks);
        void setUsers(std::vector<User> newUsers);
        void setDVDs(std::vector<DVD> newDVDs);
    private:
        std::vector<Book> books;
        std::vector<User> users;
        std::vector<DVD> dvds;
};

extern User currentUser;